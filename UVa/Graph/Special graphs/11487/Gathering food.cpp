// WIP

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

class Explorer {
public:
  Explorer(std::vector<std::string> &graph, size_t n);

  std::pair<int, int> GetShortestDistance();

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
  if (!directions_.empty()) {
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

int main(int argc, char *argv[]) { return 0; }
