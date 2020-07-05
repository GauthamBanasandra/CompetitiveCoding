#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_247 {
using NodeID = size_t;
const auto unvisited = std::numeric_limits<size_t>::max();

struct NodeInfo {
  size_t visit_index{unvisited};
  size_t least_visit_index{0};
  bool is_explored{false};
};

class CircleFinder {
public:
  CircleFinder(
      size_t num_nodes,
      const std::vector<std::pair<std::string, std::string>> &raw_edge_list);

  std::vector<std::vector<std::string>> Find() const;

private:
  void FindSCC(NodeID node_id, size_t &current_visit_index,
               std::stack<NodeID> &visit_order,
               std::vector<NodeInfo> &nodes_info,
               std::vector<std::vector<std::string>> &components) const;

  const size_t num_nodes_;
  std::vector<std::vector<NodeID>> adj_list_;
  std::unordered_map<NodeID, std::string> rev_index_;
};

CircleFinder::CircleFinder(
    const size_t num_nodes,
    const std::vector<std::pair<std::string, std::string>> &raw_edge_list)
    : num_nodes_{num_nodes} {
  adj_list_.resize(num_nodes);

  NodeID id{0};
  std::unordered_map<std::string, NodeID> index;
  for (const auto &[u, v] : raw_edge_list) {
    if (index.find(u) == index.end()) {
      index[u] = id++;
    }
    if (index.find(v) == index.end()) {
      index[v] = id++;
    }

    const auto &u_id = index[u];
    const auto &v_id = index[v];

    rev_index_.emplace(u_id, u);
    rev_index_.emplace(v_id, v);

    adj_list_[u_id].emplace_back(v_id);
  }
}

std::vector<std::vector<std::string>> CircleFinder::Find() const {
  size_t current_visit_index{0};
  std::stack<NodeID> visit_order;
  std::vector<NodeInfo> nodes_info(num_nodes_);
  std::vector<std::vector<std::string>> components;

  for (NodeID node_id = 0; node_id < num_nodes_; ++node_id) {
    if (nodes_info[node_id].visit_index == unvisited) {
      FindSCC(node_id, current_visit_index, visit_order, nodes_info,
              components);
    }
  }
  return components;
}

void CircleFinder::FindSCC(
    const NodeID node_id, size_t &current_visit_index,
    std::stack<NodeID> &visit_order, std::vector<NodeInfo> &nodes_info,
    std::vector<std::vector<std::string>> &components) const {
  auto &node = nodes_info[node_id];
  node.visit_index = node.least_visit_index = current_visit_index++;
  node.is_explored = true;
  visit_order.push(node_id);

  for (const auto &adj_node_id : adj_list_[node_id]) {
    auto &adj_node = nodes_info[adj_node_id];
    if (adj_node.visit_index == unvisited) {
      FindSCC(adj_node_id, current_visit_index, visit_order, nodes_info,
              components);
    }
    if (adj_node.is_explored) {
      node.least_visit_index =
          std::min(node.least_visit_index, adj_node.least_visit_index);
    }
  }

  if (node.visit_index == node.least_visit_index) {
    components.resize(components.size() + 1);

    while (true) {
      auto adj_node_id = visit_order.top();
      visit_order.pop();

      nodes_info[adj_node_id].is_explored = false;
      components.back().emplace_back(rev_index_.at(adj_node_id));

      if (node_id == adj_node_id) {
        break;
      }
    }
  }
}
} // namespace uva_247

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t n{0};
  size_t m{0};
  size_t t{0};

  while (std::cin >> n >> m, n || m) {
    std::vector<std::pair<std::string, std::string>> raw_edge_list(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> raw_edge_list[i].first >> raw_edge_list[i].second;
    }

    if (t > 0) {
      std::cout << std::endl;
    }
    std::cout << "Calling circles for data set " << ++t << ":" << std::endl;

    if (m == 0) {
      continue;
    }
    for (const auto &circle : uva_247::CircleFinder(n, raw_edge_list).Find()) {
      const auto *separator = "";
      for (const auto &person : circle) {
        std::cout << separator << person;
        separator = ", ";
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
