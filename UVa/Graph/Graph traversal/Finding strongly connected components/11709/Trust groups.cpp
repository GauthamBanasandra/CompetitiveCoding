#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_11709 {
using NodeId = size_t;
const auto unvisited = std::numeric_limits<NodeId>::max();

struct Node {
  size_t visit_index{unvisited};
  size_t least_visit_index{0};
  bool is_explored{false};
};

class TrustGroup {
public:
  TrustGroup(
      const std::vector<std::string> &node_names,
      const std::vector<std::pair<std::string, std::string>> &edge_list_names);

  size_t Count() const;

private:
  void FindScc(NodeId node_id, size_t &current_visit_index,
               std::vector<Node> &nodes, std::stack<NodeId> &visit_order,
               std::vector<std::vector<NodeId>> &components) const;

  const size_t num_nodes_;
  std::vector<std::vector<NodeId>> adj_list_;
};

TrustGroup::TrustGroup(
    const std::vector<std::string> &node_names,
    const std::vector<std::pair<std::string, std::string>> &edge_list_names)
    : num_nodes_{node_names.size()} {
  NodeId node_id{0};
  std::unordered_map<std::string, NodeId> node_name_id;
  for (const auto &node_name : node_names) {
    node_name_id[node_name] = node_id++;
  }

  adj_list_.resize(num_nodes_);
  for (const auto &[u_name, v_name] : edge_list_names) {
    const auto u = node_name_id.at(u_name);
    auto v = node_name_id.at(v_name);
    adj_list_[u].emplace_back(v);
  }
}

size_t TrustGroup::Count() const {
  size_t current_visit_index{0};
  std::vector<Node> nodes(num_nodes_);
  std::stack<NodeId> visit_order;
  std::vector<std::vector<NodeId>> components;

  for (NodeId node_id = 0; node_id < num_nodes_; ++node_id) {
    if (nodes[node_id].visit_index == unvisited) {
      FindScc(node_id, current_visit_index, nodes, visit_order, components);
    }
  }
  return components.size();
}

void TrustGroup::FindScc(const NodeId node_id, size_t &current_visit_index,
                         std::vector<Node> &nodes,
                         std::stack<NodeId> &visit_order,
                         std::vector<std::vector<NodeId>> &components) const {
  auto &node = nodes[node_id];
  node.least_visit_index = node.visit_index = current_visit_index++;
  node.is_explored = true;
  visit_order.emplace(node_id);

  for (const auto &adj_node_id : adj_list_[node_id]) {
    auto &adj_node = nodes[adj_node_id];
    if (adj_node.visit_index == unvisited) {
      FindScc(adj_node_id, current_visit_index, nodes, visit_order, components);
    }
    if (adj_node.is_explored) {
      node.least_visit_index =
          std::min(node.least_visit_index, adj_node.least_visit_index);
    }
  }

  if (node.visit_index == node.least_visit_index) {
    std::vector<NodeId> component;
    while (true) {
      const auto adj_node_id = visit_order.top();
      visit_order.pop();

      nodes[adj_node_id].is_explored = false;
      component.emplace_back(adj_node_id);

      if (node_id == adj_node_id) {
        break;
      }
    }
    components.emplace_back(component);
  }
}
} // namespace uva_11709

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t p{0};
  size_t t{0};
  std::string line;
  std::vector<std::string> node_names;
  std::vector<std::pair<std::string, std::string>> edge_list_names;

  while (true) {
    std::getline(std::cin, line);
    std::istringstream p_t_tokenizer(line);
    p_t_tokenizer >> p >> t;
    if (p == 0 && t == 0) {
      break;
    }

    node_names.resize(p);
    for (size_t i = 0; i < p; ++i) {
      std::getline(std::cin, node_names[i]);
    }

    edge_list_names.resize(t);
    for (size_t i = 0; i < 2 * t; ++i) {
      std::getline(std::cin, i & 1 ? edge_list_names[i >> 1].second
                                   : edge_list_names[i >> 1].first);
    }

    std::cout << uva_11709::TrustGroup(node_names, edge_list_names).Count()
              << std::endl;
  }

  return 0;
}
