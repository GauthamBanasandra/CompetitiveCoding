#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <stack>
#include <tuple>
#include <vector>

namespace uva_11838 {
using NodeId = size_t;
using EdgeList = std::vector<std::tuple<NodeId, NodeId, int>>;
const auto unvisited = std::numeric_limits<NodeId>::max();

struct Node {
  size_t visit_index{unvisited};
  size_t least_visit_index{0};
  bool is_explored{false};
};

class ConnectednessFinder {
public:
  ConnectednessFinder(size_t num_nodes, const EdgeList &edge_list);

  size_t Find() const;

private:
  void FindScc(NodeId node_id, size_t &current_visit_index,
               std::vector<Node> &nodes, std::stack<NodeId> &visit_order,
               std::vector<std::vector<NodeId>> &components) const;

  const size_t num_nodes_;
  std::vector<std::vector<NodeId>> adj_list_;
};

ConnectednessFinder::ConnectednessFinder(const size_t num_nodes,
                                         const EdgeList &edge_list)
    : num_nodes_{num_nodes} {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, is_bidirectional] : edge_list) {
    assert(is_bidirectional == 1 || is_bidirectional == 2);

    adj_list_[u - 1].emplace_back(v - 1);
    if (is_bidirectional == 2) {
      adj_list_[v - 1].emplace_back(u - 1);
    }
  }
}

size_t ConnectednessFinder::Find() const {
  size_t current_visit_index{0};
  std::vector<Node> nodes(num_nodes_);
  std::stack<NodeId> visit_order;
  std::vector<std::vector<NodeId>> components;

  for (NodeId node_id = 0; node_id < num_nodes_; ++node_id) {
    if (nodes[node_id].visit_index == unvisited) {
      FindScc(node_id, current_visit_index, nodes, visit_order, components);
    }
  }

  return components.size() == 1 ? 1 : 0;
}

void ConnectednessFinder::FindScc(
    NodeId node_id, size_t &current_visit_index, std::vector<Node> &nodes,
    std::stack<NodeId> &visit_order,
    std::vector<std::vector<NodeId>> &components) const {
  auto &node = nodes[node_id];
  node.visit_index = node.least_visit_index = current_visit_index++;
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
} // namespace uva_11838

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes{0};
  size_t num_edges{0};
  uva_11838::EdgeList edge_list;

  while (std::cin >> num_nodes >> num_edges, num_nodes || num_edges) {
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cout << uva_11838::ConnectednessFinder(num_nodes, edge_list).Find()
              << std::endl;
  }
  return 0;
}
