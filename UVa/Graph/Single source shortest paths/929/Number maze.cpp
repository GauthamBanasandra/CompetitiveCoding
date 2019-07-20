#include <functional>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace uva_929 {
const auto infinity = std::numeric_limits<int>::max();
using Matrix = std::vector<std::vector<int>>;

class Maze {
public:
  Maze(const Matrix &cost, int num_rows, int num_columns);

  int GetMinimumCost();

private:
  bool IsOutside(const int x, const int y) const {
    return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
  }

  const int num_rows_;
  const int num_columns_;
  const Matrix &cost_;
  Matrix min_cost_;

  static std::vector<std::pair<int, int>> directions_;
};

std::vector<std::pair<int, int>> Maze::directions_;

Maze::Maze(const Matrix &cost, const int num_rows, const int num_columns)
    : num_rows_(num_rows), num_columns_(num_columns), cost_(cost) {
  min_cost_.resize(num_rows_, std::vector<int>(num_columns_, infinity));

  if (directions_.empty()) {
    directions_ = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  }
}

int Maze::GetMinimumCost() {
  std::priority_queue<std::pair<int, std::pair<int, int>>,
                      std::vector<std::pair<int, std::pair<int, int>>>,
                      std::greater<>>
      order;
  order.emplace(std::piecewise_construct, std::forward_as_tuple(0),
                std::forward_as_tuple(0, 0));
  min_cost_[0][0] = 0;

  while (!order.empty()) {
    const auto [current_cost, node] = order.top();
    const auto [x, y] = node;
    order.pop();

    if (current_cost > min_cost_[x][y]) {
      continue;
    }

    for (const auto [dx, dy] : directions_) {
      const auto next_x = x + dx;
      const auto next_y = y + dy;

      if (IsOutside(next_x, next_y)) {
        continue;
      }

      const auto cost = min_cost_[x][y] + cost_[next_x][next_y];
      if (cost < min_cost_[next_x][next_y]) {
        min_cost_[next_x][next_y] = cost;
        order.emplace(std::piecewise_construct, std::forward_as_tuple(cost),
                      std::forward_as_tuple(next_x, next_y));
      }
    }
  }
  return min_cost_[num_rows_ - 1][num_columns_ - 1] + cost_[0][0];
}
} // namespace uva_929

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  auto num_rows = 0, num_columns = 0, t = 0;
  uva_929::Matrix cost;

  std::cin >> t;
  while (t--) {
    std::cin >> num_rows >> num_columns;
    cost.resize(num_rows);
    for (auto i = 0; i < num_rows; ++i) {
      cost[i].resize(num_columns);
      for (auto j = 0; j < num_columns; ++j) {
        std::cin >> cost[i][j];
      }
    }

    std::cout << uva_929::Maze(cost, num_rows, num_columns).GetMinimumCost()
              << std::endl;
  }
  return 0;
}
