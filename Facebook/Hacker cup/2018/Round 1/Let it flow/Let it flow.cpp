//
// Created by gautham on 21/7/18.
//

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <ios>
#include <cassert>

using ll = long long;

enum PipeConfiguration {
  kA, kB, kC, kD
};

enum WaterDirection {
  kLeftRight, kRightLeft, kUpDown, kDownUp
};

struct Cell {
  Cell() : x(0), y(0) {}

  Cell(int x, int y) : x(x), y(y) {}

  int x;
  int y;
};

struct Consequence {
  Consequence() : water_direction(kLeftRight) {}

  Consequence(const Cell &cell, WaterDirection water_direction) : cell(cell), water_direction(water_direction) {}

  Cell cell;
  WaterDirection water_direction;
};

class Layout {
 public:
  Layout(int num_rows, int num_columns, std::vector<std::string> &layout)
      : num_rows_(num_rows), num_columns_(num_columns), layout_(layout) {}

  bool IsFeasible(const Cell &cell);
  bool IsDestinationCell(const Cell &cell);
  bool IsInside(const Cell &cell);
  void Mark(const Cell &cell);
  void UnMark(const Cell &cell);

  int num_rows_;
  int num_columns_;

 private:
  std::vector<std::string> &layout_;
};

bool Layout::IsFeasible(const Cell &cell) {
  return IsInside(cell) && (layout_[cell.x][cell.y] == '.');
}

void Layout::Mark(const Cell &cell) {
  assert(IsFeasible(cell) && (layout_[cell.x][cell.y] != '#'));
  layout_[cell.x][cell.y] = 'x';
}

void Layout::UnMark(const Cell &cell) {
  assert(IsInside(cell) && (layout_[cell.x][cell.y] == 'x'));
  layout_[cell.x][cell.y] = '.';
}

bool Layout::IsDestinationCell(const Cell &cell) {
  return (cell.x == num_rows_ - 1) && (cell.y == num_columns_);
}

bool Layout::IsInside(const Cell &cell) {
  return (0 <= cell.x && cell.x < num_rows_) && (0 <= cell.y && cell.y < num_columns_);
}

class Plumbing {
 public:
  explicit Plumbing(Layout &layout) : layout_(layout) {}

  ll Install();

 private:
  ll Add(ll a, ll b);
  ll Hash(const Cell &cell, PipeConfiguration pipe_config);
  void Install(Cell &cell, WaterDirection water_direction, ll &count, std::unordered_map<ll, ll> &memory);
  std::vector<PipeConfiguration> GetPipeConfigurations(WaterDirection water_direction);
  Consequence GetConsequence(WaterDirection water_direction, PipeConfiguration pipe_config, Cell &cell);

  Layout &layout_;
};

void Plumbing::Install(Cell &cell,
                       WaterDirection water_direction,
                       ll &count,
                       std::unordered_map<ll, ll> &memory) {
  if (layout_.IsDestinationCell(cell)) {
    count = Add(count, 1);
    return;
  }

  if (!layout_.IsFeasible(cell)) {
    return;
  }

  for (const auto &pipe_config : GetPipeConfigurations(water_direction)) {
    auto key = Hash(cell, pipe_config);
    auto find_it = memory.find(key);
    if (find_it != memory.end()) {
      count = Add(count, find_it->second);
      continue;
    }

    auto consequence = GetConsequence(water_direction, pipe_config, cell);

    layout_.Mark(cell);

    ll local_count = 0;
    Install(consequence.cell, consequence.water_direction, local_count, memory);
    local_count = Add(local_count, 0);

    memory[key] = local_count;
    count = Add(count, local_count);

    layout_.UnMark(cell);
  }
}

std::vector<PipeConfiguration> Plumbing::GetPipeConfigurations(WaterDirection water_direction) {
  switch (water_direction) {
    case kLeftRight: return {PipeConfiguration::kC, PipeConfiguration::kD};
    case kRightLeft:return {PipeConfiguration::kA, PipeConfiguration::kB};
    case kUpDown:return {PipeConfiguration::kA, PipeConfiguration::kD};
    case kDownUp:return {PipeConfiguration::kB, PipeConfiguration::kC};
  }
}

Consequence Plumbing::GetConsequence(WaterDirection water_direction, PipeConfiguration pipe_config, Cell &cell) {
  switch (water_direction) {
    case kLeftRight:
      if (pipe_config == PipeConfiguration::kC) {
        return {{cell.x + 1, cell.y}, WaterDirection::kUpDown};
      }
      if (pipe_config == PipeConfiguration::kD) {
        return {{cell.x - 1, cell.y}, WaterDirection::kDownUp};
      }
      assert(false);

    case kRightLeft:
      if (pipe_config == PipeConfiguration::kA) {
        return {{cell.x - 1, cell.y}, WaterDirection::kDownUp};
      }
      if (pipe_config == PipeConfiguration::kB) {
        return {{cell.x + 1, cell.y}, WaterDirection::kUpDown};
      }
      assert(false);

    case kUpDown:
      if (pipe_config == PipeConfiguration::kA) {
        return {{cell.x, cell.y + 1}, WaterDirection::kLeftRight};
      }
      if (pipe_config == PipeConfiguration::kD) {
        return {{cell.x, cell.y - 1}, WaterDirection::kRightLeft};
      }
      assert(false);

    case kDownUp:
      if (pipe_config == PipeConfiguration::kB) {
        return {{cell.x, cell.y + 1}, WaterDirection::kLeftRight};
      }
      if (pipe_config == PipeConfiguration::kC) {
        return {{cell.x, cell.y - 1}, WaterDirection::kRightLeft};
      }
      assert(false);
  }
}

ll Plumbing::Install() {
  ll count = 0;
  Cell top_left;
  std::unordered_map<ll, ll> memory;

  Install(top_left, kLeftRight, count, memory);
  return count;
}

ll Plumbing::Hash(const Cell &cell, PipeConfiguration pipe_config) {
  assert(layout_.IsInside(cell));

  auto hash = cell.x * 100 + cell.y * 10000;
  switch (pipe_config) {
    case kA:return hash + 1;
    case kB:return hash + 2;
    case kC:return hash + 3;
    case kD:return hash + 4;
  }
}

ll Plumbing::Add(ll a, ll b) {
  ll c = a + b;
  return c >= 1000000007 ? c % 1000000007 : c;
}

int main() {
  std::ios::sync_with_stdio(false);

  int t, num_rows = 3, num_columns = -1;
  std::vector<std::string> raw_layout(static_cast<std::size_t >(num_rows));

  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    std::cin >> num_columns;
    for (int j = 0; j < num_rows; ++j) {
      std::cin >> raw_layout[j];
    }

    Layout layout(num_rows, num_columns, raw_layout);
    std::cout << "Case #" << i << ": " << Plumbing(layout).Install() << std::endl;
  }

  return 0;
}