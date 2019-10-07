#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_452 {
using Node = size_t;
using Cost = int;

class Scheduler {
public:
  explicit Scheduler(
      const std::vector<std::tuple<char, Cost, std::string>> &graph);

  Cost FindLongestPathCost() const;

private:
  std::vector<Node> TopologicalSort() const;
  void TopologicalSortImpl(Node node, std::vector<Node> &order,
                           std::vector<int> &visited) const;

  size_t num_nodes_{0};
  Node source_{0};
  std::vector<Cost> node_cost_;
  std::vector<std::vector<Node>> adj_list_;
};

Scheduler::Scheduler(
    const std::vector<std::tuple<char, Cost, std::string>> &graph) {
  std::unordered_map<char, Node> node_idx;
  std::unordered_map<Node, Cost> node_cost;
  Node index{0};
  const auto add_node = [&node_idx, &index](const char name) -> void {
    if (node_idx.find(name) == node_idx.end()) {
      node_idx[name] = index++;
    }
  };
  for (const auto &[v_name, cost, u_names] : graph) {
    add_node(v_name);
    node_cost[node_idx[v_name]] = cost;
    std::for_each(u_names.begin(), u_names.end(), add_node);
  }

  num_nodes_ = node_idx.size();
  node_cost_.resize(num_nodes_);
  for (const auto &[node, cost] : node_cost) {
    node_cost_[node] = cost;
  }

  assert(std::get<2>(graph.front()).empty());
  source_ = node_idx[std::get<0>(graph.front())];

  adj_list_.resize(num_nodes_);
  for (const auto &[v_name, _, u_names] : graph) {
    const auto v = node_idx[v_name];
    for (const auto &u_name : u_names) {
      const auto u = node_idx[u_name];
      adj_list_[u].emplace_back(v);
    }
  }
}

Cost Scheduler::FindLongestPathCost() const {
  std::vector<Cost> max_cost(num_nodes_);
  max_cost[source_] = node_cost_[source_];
  for (const auto &node : TopologicalSort()) {
    for (const auto &adj_node : adj_list_[node]) {
      max_cost[adj_node] =
          std::max(max_cost[adj_node], max_cost[node] + node_cost_[adj_node]);
    }
  }
  return *std::max_element(max_cost.begin(), max_cost.end());
}

std::vector<Node> Scheduler::TopologicalSort() const {
  std::vector<int> visited(num_nodes_);
  std::vector<Node> order;
  order.reserve(num_nodes_);

  TopologicalSortImpl(source_, order, visited);
  std::reverse(order.begin(), order.end());
  return order;
}

void Scheduler::TopologicalSortImpl(Node node, std::vector<Node> &order,
                                    std::vector<int> &visited) const {
  if (visited[node] != 0) {
    return;
  }
  visited[node] = 1;

  for (const auto &adj_node : adj_list_[node]) {
    TopologicalSortImpl(adj_node, order, visited);
  }
  order.emplace_back(node);
}
} // namespace uva_452

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  char node;
  uva_452::Cost cost;
  std::string adj_nodes;
  size_t t;
  std::string line;
  std::getline(std::cin, line);
  std::istringstream t_tokenizer(line);
  t_tokenizer >> t;
  std::getline(std::cin, line);

  for (size_t c = 0; c < t; ++c) {
    std::vector<std::tuple<char, uva_452::Cost, std::string>> graph;
    // Had gone wrong here initially
    // To handle the case with multiple initial nodes, we will connect all
    // initial nodes to a dummy node with cost 0
    graph.emplace_back('\0', 0, "");
    while (std::getline(std::cin, line), !line.empty()) {
      std::istringstream graph_tokenizer(line);
      adj_nodes.clear();
      graph_tokenizer >> node >> cost >> adj_nodes;
      if (adj_nodes.empty()) {
        adj_nodes.push_back('\0');
      }
      graph.emplace_back(node, cost, adj_nodes);
    }

    if (c > 0) {
      std::cout << std::endl;
    }
    std::cout << uva_452::Scheduler(graph).FindLongestPathCost() << std::endl;
  }
  return 0;
}
