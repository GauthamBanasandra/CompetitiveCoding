#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

namespace uva_11504 {
using NodeId = size_t;
using EdgeList = std::vector<std::pair<NodeId, NodeId>>;
using Component = std::vector<NodeId>;

const auto unvisited = std::numeric_limits<NodeId>::max();

struct Node {
  size_t visit_index{unvisited};
  size_t least_visit_index{0};
  bool is_explored{false};
};

class KnockCounter {
public:
  KnockCounter(size_t num_nodes, const EdgeList &edge_list);

  size_t Count() const;

private:
  std::vector<Component> FindScc() const;
  void FindSccImpl(NodeId node_id, size_t &current_visit_index,
                   std::vector<Node> &nodes, std::stack<NodeId> &visit_order,
                   std::vector<Component> &components) const;

  static void Traverse(NodeId node_id,
                       const std::vector<std::unordered_set<NodeId>> &adj_list,
                       std::vector<size_t> &visited);
  std::vector<std::unordered_set<NodeId>>
  BuildDag(const std::vector<Component> &components) const;
  std::vector<NodeId>
  TopologicalSort(const std::vector<std::unordered_set<NodeId>> &dag) const;
  static void
  TopologicalSortImpl(NodeId node_id,
                      const std::vector<std::unordered_set<NodeId>> &dag,
                      std::vector<NodeId> &visited, std::vector<NodeId> &order);
  static size_t
  CountImpl(const std::vector<NodeId> &order,
            const std::vector<std::unordered_set<NodeId>> &adj_list);

  const size_t num_nodes_;
  const EdgeList &edge_list_;
  std::vector<std::vector<NodeId>> adj_list_;
};

KnockCounter::KnockCounter(const size_t num_nodes, const EdgeList &edge_list)
    : num_nodes_{num_nodes}, edge_list_{edge_list} {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list_) {
    adj_list_[u].emplace_back(v);
  }
}

size_t KnockCounter::Count() const {
  const auto components = FindScc();
  const auto dag = BuildDag(components);
  const auto topological_sort = TopologicalSort(dag);
  return CountImpl(topological_sort, dag);
}

std::vector<Component> KnockCounter::FindScc() const {
  size_t current_visit_index{0};
  std::vector<Node> nodes(num_nodes_);
  std::stack<NodeId> visit_order;
  std::vector<Component> components;
  components.reserve(num_nodes_);

  for (NodeId node_id = 0; node_id < num_nodes_; ++node_id) {
    if (nodes[node_id].visit_index == unvisited) {
      FindSccImpl(node_id, current_visit_index, nodes, visit_order, components);
    }
  }
  return components;
}

void KnockCounter::FindSccImpl(NodeId node_id, size_t &current_visit_index,
                               std::vector<Node> &nodes,
                               std::stack<NodeId> &visit_order,
                               std::vector<Component> &components) const {
  auto &node = nodes[node_id];
  node.visit_index = node.least_visit_index = current_visit_index++;
  node.is_explored = true;
  visit_order.emplace(node_id);

  for (const auto &adj_node_id : adj_list_[node_id]) {
    auto &adj_node = nodes[adj_node_id];
    if (adj_node.visit_index == unvisited) {
      FindSccImpl(adj_node_id, current_visit_index, nodes, visit_order,
                  components);
    }
    if (adj_node.is_explored) {
      node.least_visit_index =
          std::min(node.least_visit_index, adj_node.least_visit_index);
    }
  }

  if (node.visit_index == node.least_visit_index) {
    Component component;
    while (true) {
      const auto adj_node_id = visit_order.top();
      visit_order.pop();
      nodes[adj_node_id].is_explored = false;
      component.emplace_back(adj_node_id);

      if (node_id == adj_node_id) {
        break;
      }
    }
    components.emplace_back(std::move(component));
  }
}

void KnockCounter::Traverse(
    const NodeId node_id,
    const std::vector<std::unordered_set<NodeId>> &adj_list,
    std::vector<size_t> &visited) {
  visited[node_id] = 1;

  for (const auto &adj_node_id : adj_list[node_id]) {
    if (visited[adj_node_id] == unvisited) {
      Traverse(adj_node_id, adj_list, visited);
    }
  }
}

std::vector<std::unordered_set<NodeId>>
KnockCounter::BuildDag(const std::vector<Component> &components) const {
  const auto num_components = components.size();
  std::vector<NodeId> node_component(num_nodes_);
  assert(num_components <= num_nodes_);

  size_t num_nodes{0};
  for (size_t i = 0; i < num_components; ++i) {
    for (const auto &node_id : components[i]) {
      node_component[node_id] = i;
      ++num_nodes;
    }
  }
  assert(num_nodes == num_nodes_);

  std::vector<std::unordered_set<NodeId>> dag(num_components);
  for (const auto &[u, v] : edge_list_) {
    const auto &u_dag_node = node_component[u];
    const auto &v_dag_node = node_component[v];

    if (u_dag_node != v_dag_node) {
      dag[u_dag_node].insert(v_dag_node);
    }
  }
  return dag;
}

std::vector<NodeId> KnockCounter::TopologicalSort(
    const std::vector<std::unordered_set<NodeId>> &dag) const {
  const auto dag_len = dag.size();
  std::vector<NodeId> order;
  std::vector<NodeId> visited(dag_len, unvisited);
  order.reserve(dag_len);

  for (NodeId node_id = 0; node_id < dag_len; ++node_id) {
    TopologicalSortImpl(node_id, dag, visited, order);
  }

  std::reverse(order.begin(), order.end());
  return order;
}

void KnockCounter::TopologicalSortImpl(
    NodeId node_id, const std::vector<std::unordered_set<NodeId>> &dag,
    std::vector<NodeId> &visited, std::vector<NodeId> &order) {
  if (visited[node_id] == 1) {
    return;
  }

  visited[node_id] = 1;

  for (const auto &adj_node_id : dag[node_id]) {
    if (visited[adj_node_id] == unvisited) {
      TopologicalSortImpl(adj_node_id, dag, visited, order);
    }
  }

  order.emplace_back(node_id);
}

size_t KnockCounter::CountImpl(
    const std::vector<NodeId> &order,
    const std::vector<std::unordered_set<NodeId>> &adj_list) {
  assert(order.size() == adj_list.size());

  size_t knock_count{0};
  std::vector<NodeId> visited(adj_list.size(), unvisited);

  for (const auto &node_id : order) {
    if (visited[node_id] == unvisited) {
      Traverse(node_id, adj_list, visited);
      ++knock_count;
    }
  }
  return knock_count;
}
} // namespace uva_11504

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t{0};
  size_t num_nodes{0};
  size_t num_edges{0};
  uva_11504::EdgeList edge_list;

  std::cin >> t;
  while (t--) {
    std::cin >> num_nodes >> num_edges;
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
      --edge_list[i].first;
      --edge_list[i].second;
    }
    std::cout << uva_11504::KnockCounter(num_nodes, edge_list).Count()
              << std::endl;
  }

  return 0;
}
