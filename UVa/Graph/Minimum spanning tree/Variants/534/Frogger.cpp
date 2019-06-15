#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

namespace ds {
class ufds {
public:
  explicit ufds(std::size_t size);
  std::size_t find_set(std::size_t i);
  bool is_same_set(std::size_t i, std::size_t j);
  void union_set(std::size_t i, std::size_t j);

  std::size_t size;
  std::vector<std::size_t> parent_index;
  std::vector<std::size_t> rank;
};

inline ufds::ufds(const std::size_t size) : size(size) {
  rank.assign(size, 0);
  parent_index.resize(size);
  for (std::size_t i = 0; i < size; ++i) {
    parent_index[i] = i;
  }
}

inline std::size_t ufds::find_set(const std::size_t i) {
  if (parent_index[i] == i) {
    return i;
  }

  parent_index[i] = find_set(parent_index[i]);
  return parent_index[i];
}

inline bool ufds::is_same_set(const std::size_t i, const std::size_t j) {
  return find_set(i) == find_set(j);
}

inline void ufds::union_set(const std::size_t i, const std::size_t j) {
  if (!is_same_set(i, j)) {
    const auto parent_i = find_set(i);
    const auto parent_j = find_set(j);
    if (rank[parent_i] > rank[parent_j]) {
      parent_index[parent_j] = parent_i;
    } else {
      parent_index[parent_i] = parent_j;
      if (rank[parent_i] == rank[parent_j]) {
        ++rank[parent_j];
      }
    }
  }
}
} // namespace ds

namespace uva_534 {
using Point = std::pair<int, int>;
using Edge = std::pair<std::size_t, std::size_t>;

class Frogger {
public:
  Frogger(std::size_t num_nodes, const std::vector<Point> &points);

  double GetFroggerDistance();

private:
  bool
  DFS(std::size_t start_node, const std::size_t end_node,
      const std::vector<std::vector<std::pair<std::size_t, int>>> &adj_list,
      int max_distance, int &frogger_distance);

  const std::size_t num_nodes_;
  const std::vector<Point> &points_;
  std::vector<std::pair<Edge, int>> edge_list_;

  std::vector<int> visited_;
};

Frogger::Frogger(const std::size_t num_nodes, const std::vector<Point> &points)
    : num_nodes_(num_nodes), points_(points) {
  visited_.resize(num_nodes);
  edge_list_.reserve(num_nodes_ * (num_nodes_ - 1));
  for (std::size_t i = 0; i < num_nodes_; ++i) {
    for (auto j = i + 1; j < num_nodes_; ++j) {
      const auto &p1 = points_[i];
      const auto &p2 = points_[j];
      edge_list_.emplace_back(
          std::piecewise_construct, std::forward_as_tuple(i, j),
          std::forward_as_tuple((p1.first - p2.first) * (p1.first - p2.first) +
                                (p1.second - p2.second) *
                                    (p1.second - p2.second)));
    }
  }

  std::sort(edge_list_.begin(), edge_list_.end(),
            [](const std::pair<Edge, int> &e1, const std::pair<Edge, int> &e2)
                -> bool { return e1.second < e2.second; });
}

double Frogger::GetFroggerDistance() {
  ds::ufds set(num_nodes_);
  std::vector<std::vector<std::pair<std::size_t, int>>> adj_list(num_nodes_);

  for (const auto &edge : edge_list_) {
    auto &[u, v] = edge.first;
    const auto &cost = edge.second;
    if (!set.is_same_set(u, v)) {
      adj_list[u].emplace_back(v, cost);
      adj_list[v].emplace_back(u, cost);
      set.union_set(u, v);
    }
  }

  auto frogger_distance = -1;
  assert(DFS(0, 1, adj_list, 0, frogger_distance));
  assert(frogger_distance != -1);
  return std::sqrt(frogger_distance);
}

// Pay attention to this implementation of DFS
// It is implemented in such a way that it accounts for the max_distance only on
// the path that leads from start_node to end_node
bool Frogger::DFS(
    const std::size_t start_node, const std::size_t end_node,
    const std::vector<std::vector<std::pair<std::size_t, int>>> &adj_list,
    const int max_distance, int &frogger_distance) {
  if (start_node == end_node) {
    frogger_distance = max_distance;
    return true;
  }

  visited_[start_node] = 1;
  for (const auto &next : adj_list[start_node]) {
    auto &[adj_node, cost] = next;
    if (visited_[adj_node] == 1) {
      continue;
    }
    if (DFS(adj_node, end_node, adj_list, std::max(max_distance, cost),
            frogger_distance)) {
      return true;
    }
  }
  return false;
}
} // namespace uva_534

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  auto t = 1;
  std::size_t num_nodes;
  std::vector<uva_534::Point> points;

  while (std::cin >> num_nodes, num_nodes != 0) {
    points.resize(num_nodes);
    for (std::size_t i = 0; i < num_nodes; ++i) {
      std::cin >> points[i].first >> points[i].second;
    }

    std::cout << "Scenario #" << t++ << std::endl;
    std::cout << std::fixed << std::setprecision(3) << "Frog Distance = "
              << uva_534::Frogger(num_nodes, points).GetFroggerDistance()
              << std::endl
              << std::endl;
  }
  return 0;
}
