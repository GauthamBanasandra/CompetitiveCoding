// WA

#include <iostream>
#include <map>
#include <numeric>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace uva_11487 {
class Explorer {
public:
  Explorer(std::vector<std::string> &graph, size_t n);

  std::tuple<bool, size_t, size_t> GetShortestDistance();

private:
  void Explore(int p, int q, char fill, char expected,
               std::vector<std::map<size_t, size_t>> &distances,
               size_t distance_idx, size_t count);

  bool IsOutside(int x, int y) const {
    return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
  }
  bool IsValid(int x, int y, char fill, char expected) const;

  std::vector<std::string> &graph_;
  std::vector<std::pair<int, int>> positions_;
  const int num_rows_;
  const int num_columns_;

  static std::vector<std::pair<int, int>> directions_;
};

std::vector<std::pair<int, int>> Explorer::directions_;

Explorer::Explorer(std::vector<std::string> &graph, size_t n)
    : graph_{graph}, num_rows_{static_cast<int>(n)}, num_columns_{
                                                         static_cast<int>(n)} {
  if (directions_.empty()) {
    directions_ = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  }

  for (auto i = 0; i < num_rows_; i++) {
    for (auto j = 0; j < num_columns_; j++) {
      if (graph_[i][j] >= 'A' && graph_[i][j] <= 'Z') {
        auto value = graph_[i][j] - 'A';
        if (positions_.size() <= value) {
          positions_.resize(value + 1);
        }
        positions_[value] = {i, j};
      }
    }
  }
}

std::tuple<bool, size_t, size_t> Explorer::GetShortestDistance() {
  auto len = positions_.size();
  if (len == 1) {
    return {true, 0, 0};
  }

  std::vector<std::map<size_t, size_t>> distances(len);
  for (size_t i = 1; i < len; ++i) {
    auto index = i - 1;
    for (const auto &[x, y] : directions_) {
      Explore(positions_[index].first + x, positions_[index].second + y,
              'a' + index, 'A' + i, distances, index, 1);
    }
  }

  distances.pop_back();
  auto is_possible = true;
  auto sum = std::accumulate(
      distances.begin(), distances.end(), static_cast<size_t>(0),
      [&is_possible](const size_t &sum,
                     const std::map<size_t, size_t> &m) -> size_t {
        if (m.empty()) {
          is_possible = false;
          return 0;
        }
        return m.begin()->first + sum;
      });
  auto product = std::accumulate(
      distances.begin(), distances.end(), static_cast<size_t>(1),
      [](const size_t &product, const std::map<size_t, size_t> &m) -> size_t {
        if (m.empty()) {
          return 0;
        }
        return m.begin()->second * product;
      });
  return {is_possible, sum, product};
}

void Explorer::Explore(int p, int q, char fill, char expected,
                       std::vector<std::map<size_t, size_t>> &distances,
                       size_t distance_idx, size_t count) {
  if (IsOutside(p, q) || !IsValid(p, q, fill, expected)) {
    return;
  }

  if (graph_[p][q] == expected) {
    ++distances[distance_idx][count];
    return;
  }

  graph_[p][q] = fill;
  for (const auto &[x, y] : directions_) {
    Explore(p + x, q + y, fill, expected, distances, distance_idx, count + 1);
  }
}

bool Explorer::IsValid(int x, int y, char fill, char expected) const {
  if (graph_[x][y] == '.') {
    return true;
  }
  if (graph_[x][y] == '#' || graph_[x][y] == fill) {
    return false;
  }
  if (graph_[x][y] >= 'A' && graph_[x][y] <= 'Z' && graph_[x][y] != expected) {
    return false;
  }
  return true;
}
} // namespace uva_11487

int main(int argc, char *argv[]) {
  size_t n, c = 0;
  std::vector<std::string> grid;

  while (std::cin >> n, n != 0) {
    ++c;
    grid.resize(n);
    for (size_t i = 0; i < n; ++i) {
      std::cin >> grid[i];
    }

    auto [is_possible, shortest_path_len, shortest_path_count] =
        uva_11487::Explorer(grid, n).GetShortestDistance();
    if (!is_possible) {
      std::cout << "Case " << c << ": Impossible" << std::endl;
    } else {
      std::cout << "Case " << c << ": " << shortest_path_len << " "
                << shortest_path_count << std::endl;
    }
  }
  return 0;
}
