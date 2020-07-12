#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace uva_10731 {
using NodeId = char;
const auto unvisited = std::numeric_limits<size_t>::max();
const size_t num_activities = 5;

struct Node {
  size_t visit_index{unvisited};
  size_t least_visit_index{0};
  bool is_explored{false};
};

struct ActivityResponsePair {
  std::vector<NodeId> activities;
  NodeId response{'\0'};

  ActivityResponsePair() { activities.resize(num_activities); }
};

class ContradictionFinder {
public:
  explicit ContradictionFinder(
      const std::vector<ActivityResponsePair> &responses);
  std::unordered_map<NodeId, Node> GetNodes() const;

  std::vector<std::vector<char>> Find() const;

private:
  static size_t
  GetNodeCount(const std::vector<ActivityResponsePair> &responses);

  void FindScc(NodeId node_id, size_t &current_visit_index,
               std::unordered_map<NodeId, Node> &nodes,
               std::stack<NodeId> &visit_order,
               std::vector<std::vector<NodeId>> &components_out) const;

  std::unordered_map<NodeId, std::unordered_set<NodeId>> adj_list_;
};

ContradictionFinder::ContradictionFinder(
    const std::vector<ActivityResponsePair> &responses) {
  for (const auto &response : responses) {
    for (const auto &activity : response.activities) {
      if (adj_list_.find(activity) == adj_list_.end()) {
        adj_list_[activity] = {};
      }
      if (response.response != activity) {
        adj_list_[response.response].insert(activity);
      }
    }
  }
}

std::unordered_map<NodeId, Node> ContradictionFinder::GetNodes() const {
  std::unordered_map<NodeId, Node> nodes;
  for (const auto &[node, _] : adj_list_) {
    nodes[node] = {};
  }
  return nodes;
}

std::vector<std::vector<char>> ContradictionFinder::Find() const {
  size_t current_visit_index{0};
  auto nodes = GetNodes();
  std::stack<NodeId> visit_order;
  std::vector<std::vector<NodeId>> components;
  components.reserve(adj_list_.size());

  for (const auto &[node_id, _] : adj_list_) {
    if (nodes.at(node_id).visit_index == unvisited) {
      FindScc(node_id, current_visit_index, nodes, visit_order, components);
    }
  }

  for (auto &component : components) {
    std::sort(component.begin(), component.end());
  }
  std::sort(components.begin(), components.end());
  return components;
}

size_t ContradictionFinder::GetNodeCount(
    const std::vector<ActivityResponsePair> &responses) {
  std::unordered_set<NodeId> node_ids;
  for (const auto &response : responses) {
    node_ids.insert(response.activities.begin(), response.activities.end());
  }
  return node_ids.size();
}

void ContradictionFinder::FindScc(
    const NodeId node_id, size_t &current_visit_index,
    std::unordered_map<NodeId, Node> &nodes, std::stack<NodeId> &visit_order,
    std::vector<std::vector<NodeId>> &components_out) const {
  auto &node = nodes.at(node_id);
  node.visit_index = node.least_visit_index = current_visit_index++;
  node.is_explored = true;
  visit_order.emplace(node_id);

  for (const auto &adj_node_id : adj_list_.at(node_id)) {
    auto &adj_node = nodes.at(adj_node_id);
    if (adj_node.visit_index == unvisited) {
      FindScc(adj_node_id, current_visit_index, nodes, visit_order,
              components_out);
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
      component.emplace_back(adj_node_id);
      nodes.at(adj_node_id).is_explored = false;

      if (node_id == adj_node_id) {
        break;
      }
    }
    components_out.emplace_back(std::move(component));
  }
}
} // namespace uva_10731

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  char c;
  size_t n{0};
  size_t t{0};
  std::vector<uva_10731::ActivityResponsePair> responses;

  while (std::cin >> n, n != 0) {
    responses.resize(n);
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < uva_10731::num_activities; ++j) {
        std::cin >> c;
        responses[i].activities[j] = c;
      }
      std::cin >> c;
      responses[i].response = c;
    }

    if (t++ > 0) {
      std::cout << std::endl;
    }

    for (const auto &set : uva_10731::ContradictionFinder(responses).Find()) {
      const auto *separator = "";
      for (const auto &element : set) {
        std::cout << separator << element;
        separator = " ";
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
