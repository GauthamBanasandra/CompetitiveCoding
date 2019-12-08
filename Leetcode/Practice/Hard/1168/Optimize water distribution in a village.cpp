#include <algorithm>
#include <iostream>
#include <numeric>
#include <ostream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lc_1168 {
class Ufds {
public:
  explicit Ufds(const size_t num_nodes);

  size_t FindSet(size_t i);
  bool IsSameSet(const size_t i, const size_t j) {
    return FindSet(i) == FindSet(j);
  }

  void UnionSet(size_t i, size_t j);

private:
  std::vector<size_t> parent_;
  std::vector<size_t> rank_;
};

Ufds::Ufds(const size_t num_nodes) {
  rank_.resize(num_nodes);
  parent_.resize(num_nodes);
  std::iota(parent_.begin(), parent_.end(), 0);
}

size_t Ufds::FindSet(const size_t i) {
  if (i == parent_[i]) {
    return i;
  }
  return parent_[i] = FindSet(parent_[i]);
}

void Ufds::UnionSet(const size_t i, const size_t j) {
  if (IsSameSet(i, j)) {
    return;
  }

  const auto parent_i = FindSet(i);
  const auto parent_j = FindSet(j);

  if (rank_[parent_i] > rank_[parent_j]) {
    parent_[parent_j] = parent_i;
  } else {
    parent_[parent_i] = parent_j;
    if (rank_[parent_i] == rank_[parent_j]) {
      ++rank_[parent_j];
    }
  }
}

class Graph {
public:
  Graph(size_t num_nodes, const std::vector<int> &nodes,
        const std::vector<std::vector<int>> &edge_list);

  int MinConnectionCost();

private:
  const size_t num_nodes_;
  const std::vector<int> &nodes_;
  std::vector<std::tuple<int, int, int>> edge_list_;
  std::unordered_map<size_t, int> component_cost_;
};

Graph::Graph(const size_t num_nodes, const std::vector<int> &nodes,
             const std::vector<std::vector<int>> &edge_list)
    : num_nodes_{num_nodes}, nodes_{nodes} {
  edge_list_.reserve(edge_list.size());
  for (const auto &edge : edge_list) {
    edge_list_.emplace_back(edge[0] - 1, edge[1] - 1, edge[2]);
  }
  std::sort(edge_list_.begin(), edge_list_.end(),
            [](const std::tuple<int, int, int> &a,
               const std::tuple<int, int, int> &b) -> bool {
              return std::get<2>(a) < std::get<2>(b);
            });
  for (size_t i = 0; i < num_nodes_; ++i) {
    component_cost_[i] = nodes_[i];
  }
}

int Graph::MinConnectionCost() {
  auto total_cost = 0;
  Ufds ufds(num_nodes_);
  for (const auto &[u, v, edge_cost] : edge_list_) {
    if (ufds.IsSameSet(u, v)) {
      continue;
    }
    const auto u_root = ufds.FindSet(u);
    const auto v_root = ufds.FindSet(v);
    const auto min_node_cost =
        std::min(component_cost_.at(u_root), component_cost_.at(v_root));
    if (edge_cost + min_node_cost <
        component_cost_[u_root] + component_cost_[v_root]) {
      ufds.UnionSet(u, v);
      component_cost_.erase(u_root);
      component_cost_.erase(v_root);
      component_cost_[ufds.FindSet(u)] = min_node_cost;
      total_cost += edge_cost;
    }
  }
  for (const auto &[_, cost] : component_cost_) {
    total_cost += cost;
  }
  return total_cost;
}
} // namespace lc_1168

class Solution {
public:
  int minCostToSupplyWater(int n, std::vector<int> &wells,
                           std::vector<std::vector<int>> &pipes);
};

int Solution::minCostToSupplyWater(int n, std::vector<int> &wells,
                                   std::vector<std::vector<int>> &pipes) {
  return lc_1168::Graph(n, wells, pipes).MinConnectionCost();
}

int main(int argc, char *argv[]) {
  auto n = 3;
  std::vector<int> wells{1, 2, 2};
  std::vector<std::vector<int>> pipes{{1, 2, 1}, {2, 3, 1}};
  std::cout << Solution().minCostToSupplyWater(n, wells, pipes) << std::endl;
  return 0;
}
