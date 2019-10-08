// WIP

#include <algorithm>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

using Node = size_t;
using Cost = long long;

class Scheduler {
public:
  Scheduler(const std::vector<std::vector<Cost>> &grid, size_t max_steps);

  Cost GetMaxCost() const;

private:
  std::vector<Node> TopologicalSort() const;
  void TopologicalSortImpl(Node node, std::vector<int> &visited,
                           std::vector<Node> &order) const;

  static Node GetNode(const size_t i, const size_t j, const size_t n) {
    return i * n + j;
  }

  const size_t num_nodes_;
  const Cost initial_cost_;
  std::vector<std::vector<std::pair<Node, Cost>>> adj_list_;
};

Scheduler::Scheduler(const std::vector<std::vector<Cost>> &grid,
                     const size_t max_steps)
    : num_nodes_(grid.size() * grid.size()),
      initial_cost_(grid.front().front()) {
  adj_list_.resize(num_nodes_);
  for (size_t i = 0, len = grid.size(); i < len; ++i) {
    for (size_t j = 0; j < len; ++j) {
      const auto u = GetNode(i, j, len);
      for (size_t k = 1; k <= max_steps; ++k) {
        if (j + k < len && grid[i][j] < grid[i][j + k]) {
          adj_list_[u].emplace_back(GetNode(i, j + k, len), grid[i][j + k]);
        }
        if (i + k < len && grid[i][j] < grid[i + k][j]) {
          adj_list_[u].emplace_back(GetNode(i + k, j, len), grid[i + k][j]);
        }
      }
    }
  }
}

Cost Scheduler::GetMaxCost() const {
  std::vector<Cost> max_cost(num_nodes_);
  max_cost.front() = initial_cost_;
  auto order = TopologicalSort();
  for (const auto &node : order) {
    for (const auto &[adj_node, adj_cost] : adj_list_[node]) {
      max_cost[adj_node] =
          std::max(max_cost[adj_node], max_cost[node] + adj_cost);
    }
  }
  return *std::max_element(max_cost.begin(), max_cost.end());
}

std::vector<Node> Scheduler::TopologicalSort() const {
  std::vector<int> visited(num_nodes_);
  std::vector<Node> order;
  order.reserve(num_nodes_);
  TopologicalSortImpl(0, visited, order);
  std::reverse(order.begin(), order.end());
  return order;
}

void Scheduler::TopologicalSortImpl(Node node, std::vector<int> &visited,
                                    std::vector<Node> &order) const {
  if (visited[node] == 1) {
    return;
  }
  visited[node] = 1;

  for (const auto &[adj_node, _] : adj_list_[node]) {
    TopologicalSortImpl(adj_node, visited, order);
  }
  order.emplace_back(node);
}

int main(int argc, char *argv[]) {
  size_t t, num_nodes, max_steps;
  std::vector<std::vector<Cost>> grid;

  std::cin >> t;
  for (size_t c = 0; c < t; ++c) {
    std::cin >> num_nodes >> max_steps;
    grid.resize(num_nodes);
    for (size_t i = 0; i < num_nodes; ++i) {
      grid[i].resize(num_nodes);
      for (size_t j = 0; j < num_nodes; ++j) {
        std::cin >> grid[i][j];
      }
    }

    if (c > 0) {
      std::cout << std::endl;
    }
    std::cout << Scheduler(grid, max_steps).GetMaxCost() << std::endl;
  }
  return 0;
}
