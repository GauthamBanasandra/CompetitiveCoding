#include <cassert>
#include <deque>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

namespace uva_11624 {
using ll = long long;
using Matrix = std::vector<std::string>;

class Graph {
public:
  Graph(int num_rows, int num_columns, Matrix &grid);

  std::pair<bool, ll> GetSteps();

private:
  [[nodiscard]] bool IsOutside(const int x, const int y) const {
    return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
  }

  enum class Type { kJoe, kFire, kWall, kEmpty };

  static std::vector<std::pair<int, int>> directions_;

  int num_rows_;
  int num_columns_;
  std::vector<std::vector<std::pair<Type, int>>> grid_;
  std::deque<std::pair<int, int>> order_;
};

std::vector<std::pair<int, int>> Graph::directions_;

Graph::Graph(const int num_rows, const int num_columns, Matrix &grid)
    : num_rows_(num_rows), num_columns_(num_columns) {
  grid_.resize(num_rows_);
  for (auto i = 0; i < num_rows_; ++i) {
    auto &row = grid_[i];
    row.reserve(num_columns_);
    for (auto j = 0; j < num_columns_; ++j) {
      const auto item = grid[i][j];
      switch (item) {
      case '#':
        row.emplace_back(Type::kWall, 0);
        break;

      case 'F':
        row.emplace_back(Type::kFire, 0);
        break;

      case 'J':
        row.emplace_back(Type::kJoe, 0);
        break;

      case '.':
        row.emplace_back(Type::kEmpty, 0);
        break;

      default:
        assert(false);
      }

      // We initialize the order_ with all the positions of Joe and Fire
      // We then process the items enqueued and track them in turn
      if (grid[i][j] == 'F') {
        order_.emplace_back(i, j);
      } else if (grid[i][j] == 'J') {
        // Must process Joe first (not mentioned in the problem though)
        order_.emplace_front(i, j);
      }
    }
  }
  if (directions_.empty()) {
    directions_ = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  }
}

std::pair<bool, ll> Graph::GetSteps() {
  ll joe_steps = 0;
  while (!order_.empty()) {
    auto [x, y] = order_.front();
    order_.pop_front();

    auto &[type, visit] = grid_[x][y];
    if (type == Type::kJoe) {
      for (const auto &direction : directions_) {
        const auto next_x = x + direction.first;
        const auto next_y = y + direction.second;

        if (IsOutside(next_x, next_y)) {
          return {true, visit + 1};
        }
        if (grid_[next_x][next_y].first != Type::kEmpty) {
          continue;
        }
        grid_[next_x][next_y] = {Type::kJoe, visit + 1};
        order_.emplace_back(next_x, next_y);
      }
    } else if (type == Type::kFire) {
      for (const auto &direction : directions_) {
        const auto next_x = x + direction.first;
        const auto next_y = y + direction.second;

        if (IsOutside(next_x, next_y) ||
            grid_[next_x][next_y].first == Type::kWall ||
            grid_[next_x][next_y].first == Type::kFire) {
          continue;
        }
        grid_[next_x][next_y] = {Type::kFire, visit + 1};
        order_.emplace_back(next_x, next_y);
      }
    }
  }
  return {false, -1};
}
} // namespace uva_11624

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t = 0;
  auto num_rows = 0, num_columns = 0;
  uva_11624::Matrix grid;

  std::cin >> t;
  while (t--) {
    std::cin >> num_rows >> num_columns;
    grid.resize(num_rows);
    for (auto i = 0; i < num_rows; ++i) {
      std::cin >> grid[i];
    }
    auto [is_possible, num_steps] =
        uva_11624::Graph(num_rows, num_columns, grid).GetSteps();
    if (!is_possible) {
      std::cout << "IMPOSSIBLE" << std::endl;
    } else {
      std::cout << num_steps << std::endl;
    }
  }
  return 0;
}
