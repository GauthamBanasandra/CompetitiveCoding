// WIP

#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using Node = size_t;
using Cost = int;

const auto unvisited = -1;
const auto infinity = std::numeric_limits<Cost>::max();

class Traversal {
public:
  Traversal(size_t num_nodes,
            const std::vector<std::pair<Cost, std::vector<Node>>> &nodes);

  bool IsPossible();

private:
  void MarkUnreachableNodes(Node node);
  bool IsReachable(Node node);

  const size_t num_nodes_;
  const Node source_{0};
  const Node destination_;
  std::vector<std::tuple<Node, Node, Cost>> edge_list_;
  std::vector<std::vector<std::pair<Node, Cost>>> adj_list_;
  std::vector<int> visited_;
  std::vector<Cost> min_cost_;
};

Traversal::Traversal(
    const size_t num_nodes,
    const std::vector<std::pair<Cost, std::vector<Node>>> &nodes)
    : num_nodes_{num_nodes}, destination_{num_nodes - 1} {
  visited_.resize(num_nodes_, unvisited);
  min_cost_.resize(num_nodes_, infinity);
  adj_list_.resize(num_nodes_);

  for (Node node = 0; node < num_nodes_; ++node) {
    const auto &[cost, adj_nodes] = nodes[node];
    for (const auto &adj_node_offset : adj_nodes) {
      auto adj_node = adj_node_offset - 1;
      edge_list_.emplace_back(node, adj_node, nodes[adj_node].first);
      edge_list_.emplace_back(adj_node, node, nodes[node].first);

      adj_list_[node].emplace_back(adj_node, nodes[adj_node].first);
      adj_list_[adj_node].emplace_back(node, nodes[node].first);
    }
  }
}

bool Traversal::IsPossible() {
  min_cost_[source_] = 0;
  for (size_t i = 0; i < num_nodes_ - 1; ++i) {
    for (const auto &[u, v, cost] : edge_list_) {
      min_cost_[v] = min_cost_[u] == infinity
                         ? cost
                         : std::min(min_cost_[v], min_cost_[u] + cost);
    }
  }

  for (const auto &[u, v, cost] : edge_list_) {
    if (min_cost_[u] == infinity) {
      MarkUnreachableNodes(u);
    } else if (min_cost_[v] > min_cost_[u] + cost) {
      MarkUnreachableNodes(v);
    }
  }

  visited_.assign(num_nodes_, unvisited);
  return IsReachable(source_);
}

void Traversal::MarkUnreachableNodes(const Node node) {
  if (visited_[node] != unvisited) {
    return;
  }

  visited_[node] = 1;
  min_cost_[node] = infinity;

  for (const auto &[adj_node, cost] : adj_list_[node]) {
    if (visited_[adj_node] == unvisited) {
      MarkUnreachableNodes(adj_node);
    }
  }
}

bool Traversal::IsReachable(const Node node) {
  if (visited_[node] != unvisited || min_cost_[node] == infinity) {
    return false;
  }

  if (node == destination_) {
    return true;
  }

  visited_[node] = 1;

  for (const auto &[adj_node, cost] : adj_list_[node]) {
    if (IsReachable(adj_node)) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  int num_nodes;
  size_t num_adj_nodes;
  std::vector<std::pair<Cost, std::vector<Node>>> nodes;

  while (std::cin >> num_nodes, num_nodes != -1) {
    nodes.resize(num_nodes);
    for (auto i = 0; i < num_nodes; ++i) {
      auto &[cost, adj_nodes] = nodes[i];
      std::cin >> cost >> num_adj_nodes;

      adj_nodes.resize(num_adj_nodes);
      for (size_t j = 0; j < num_adj_nodes; ++j) {
        std::cin >> adj_nodes[j];
      }
    }

    std::cout << (Traversal(num_nodes, nodes).IsPossible() ? "winnable"
                                                           : "hopeless")
              << std::endl;
  }
  return 0;
}
