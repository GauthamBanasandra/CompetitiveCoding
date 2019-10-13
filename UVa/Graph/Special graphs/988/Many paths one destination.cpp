#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>

namespace uva_988 {
using Node = size_t;
using Count = int;

class Scheduler {
public:
  Scheduler(size_t num_nodes, std::vector<std::vector<Node>> &adj_list);

  Count CountPaths() const;

private:
  std::vector<Node> TopologicalSort() const;
  void TopologicalSort(Node node, std::vector<int> &visited,
                       std::vector<Node> &order) const;

  const size_t num_nodes_;
  const Node source_{0};
  const Node destination_;
  std::vector<std::vector<Node>> &adj_list_;
};

Scheduler::Scheduler(const size_t num_nodes,
                     std::vector<std::vector<Node>> &adj_list)
    : num_nodes_{num_nodes + 1}, destination_{num_nodes}, adj_list_{adj_list} {
  for (auto &nodes : adj_list_) {
    if (nodes.empty()) {
      nodes.emplace_back(destination_);
    }
  }
  adj_list_.emplace_back(std::vector<Node>());
}

Count Scheduler::CountPaths() const {
  std::vector<Count> num_paths(num_nodes_);
  num_paths.front() = 1;
  for (const auto &u : TopologicalSort()) {
    for (const auto &v : adj_list_[u]) {
      num_paths[v] += num_paths[u];
    }
  }
  return num_paths[destination_];
}

std::vector<Node> Scheduler::TopologicalSort() const {
  std::vector<int> visited(num_nodes_);
  std::vector<Node> order;
  order.reserve(num_nodes_);
  TopologicalSort(source_, visited, order);
  std::reverse(order.begin(), order.end());
  return order;
}

void Scheduler::TopologicalSort(Node node, std::vector<int> &visited,
                                std::vector<Node> &order) const {
  if (visited[node] == 1) {
    return;
  }
  visited[node] = 1;

  for (const auto &adj_node : adj_list_[node]) {
    TopologicalSort(adj_node, visited, order);
  }
  order.emplace_back(node);
}
} // namespace uva_988

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_adj_nodes, c = 0;
  std::vector<std::vector<uva_988::Node>> adj_list;

  while (std::cin >> num_nodes, !std::cin.eof()) {
    adj_list.resize(num_nodes);
    for (size_t i = 0; i < num_nodes; ++i) {
      std::cin >> num_adj_nodes;
      adj_list[i].resize(num_adj_nodes);
      for (size_t j = 0; j < num_adj_nodes; ++j) {
        std::cin >> adj_list[i][j];
      }
    }

    if (c++ > 0) {
      std::cout << std::endl;
    }
    std::cout << uva_988::Scheduler(num_nodes, adj_list).CountPaths()
              << std::endl;
  }
  return 0;
}
