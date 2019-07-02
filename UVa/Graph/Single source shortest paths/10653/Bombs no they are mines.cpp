// WIP

#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using Pos = std::pair<int, int>;

class Robot {
public:
  Robot(int num_rows, int num_columns, const std::vector<Pos> &mines, Pos start,
        Pos end);

  int GetShortestPathLength();

private:
  bool IsOutside(const int x, const int y) const {
    return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
  }

  const int num_rows_;
  const int num_columns_;
  const Pos start_;
  const Pos end_;
  std::vector<std::vector<int>> graph_;

  const int mine_{-1};
  const int unvisited_{0};
  static std::vector<Pos> directions_;
};

std::vector<Pos> Robot::directions_;

Robot::Robot(const int num_rows, const int num_columns,
             const std::vector<Pos> &mines, Pos start, Pos end)
    : num_rows_(num_rows), num_columns_(num_columns), start_(std::move(start)),
      end_(std::move(end)) {
  graph_.resize(num_rows_, std::vector<int>(num_columns_));
  for (const auto &[x, y] : mines) {
    graph_[x][y] = mine_;
  }

  if (directions_.empty()) {
    directions_ = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  }
}

int Robot::GetShortestPathLength() {
  std::queue<Pos> order;
  order.push(start_);
  graph_[start_.first][start_.second] = 1;

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    if (node == end_) {
      return graph_[end_.first][end_.second];
    }

    for (const auto &[x, y] : directions_) {
      const auto next_x = node.first + x;
      const auto next_y = node.second + y;
      if (IsOutside(next_x, next_y) || graph_[next_x][next_y] == mine_ ||
          graph_[next_x][next_y] != unvisited_) {
        continue;
      }
      graph_[next_x][next_y] = graph_[node.first][node.second] + 1;
      order.emplace(next_x, next_y);
    }
  }
  assert(false);
  return graph_[end_.first][end_.second];
}

int main(int argc, char *argv[]) {
  int num_rows, num_columns;
  std::vector<Pos> mines;
  Pos start, end;
  size_t mines_num_rows;
}
