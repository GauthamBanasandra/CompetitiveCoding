#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_10330 {
using Node = size_t;
using Capacity = int;
using EdgeList = std::vector<std::tuple<Node, Node, Capacity>>;

const auto infinity = std::numeric_limits<Capacity>::max();
const auto unvisited = -1;

class FlowNetwork {
public:
  FlowNetwork(const std::vector<Capacity> &capacities,
              const EdgeList &edge_list, const std::vector<Node> &sources,
              const std::vector<Node> &sinks);
  Capacity GetMaxFlow();

private:
  Capacity Augment(const std::vector<Node> &parent);
  std::pair<bool, std::vector<Node>> FindAugmentingPath() const;

  static Node ToIncomingNode(const Node node) {
    assert(node != 0);
    return (node - 1) * 2;
  }

  static Node ToOutgoingNode(const Node node) {
    assert(node != 0);
    return (node - 1) * 2 + 1;
  }

  const size_t num_nodes_;
  const Node source_;
  const Node sink_;
  std::vector<std::unordered_map<Node, Capacity>> adj_list_;
};

FlowNetwork::FlowNetwork(const std::vector<Capacity> &capacities,
                         const EdgeList &edge_list,
                         const std::vector<Node> &sources,
                         const std::vector<Node> &sinks)
    : num_nodes_{capacities.size() * 2 + 1 + 1}, source_{capacities.size() * 2},
      sink_{capacities.size() * 2 + 1} {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, capacity] : edge_list) {
    // We need to add to the existing capacities to handle the case where
    // multiple edges exist between the same pair of nodes
    adj_list_[ToOutgoingNode(u)][ToIncomingNode(v)] += capacity;
    adj_list_[ToOutgoingNode(v)][ToIncomingNode(u)] += 0;
  }

  for (size_t i = 0, len = capacities.size(); i < len; ++i) {
    adj_list_[ToIncomingNode(i + 1)][ToOutgoingNode(i + 1)] = capacities[i];
    adj_list_[ToOutgoingNode(i + 1)][ToIncomingNode(i + 1)] = 0;
  }

  for (const auto &source : sources) {
    adj_list_[source_][ToIncomingNode(source)] = infinity;
    adj_list_[ToIncomingNode(source)][source_] = 0;
  }

  for (const auto &sink : sinks) {
    adj_list_[ToOutgoingNode(sink)][sink_] = infinity;
    adj_list_[sink_][ToOutgoingNode(sink)] = 0;
  }
}

Capacity FlowNetwork::GetMaxFlow() {
  auto max_flow = 0, flow = 0;
  do {
    auto [is_reachable, bfs_spanning_tree] = FindAugmentingPath();
    if (!is_reachable) {
      return max_flow;
    }
    flow = Augment(bfs_spanning_tree);
    max_flow += flow;
  } while (flow != 0);
  assert(false);
  return max_flow;
}

Capacity FlowNetwork::Augment(const std::vector<Node> &parent) {
  auto min_capacity = infinity;
  for (auto node = sink_; node != source_; node = parent[node]) {
    min_capacity = std::min(min_capacity, adj_list_[parent[node]][node]);
  }
  for (auto node = sink_; node != source_; node = parent[node]) {
    adj_list_[parent[node]][node] -= min_capacity;
    adj_list_[node][parent[node]] += min_capacity;
  }
  return min_capacity;
}

std::pair<bool, std::vector<Node>> FlowNetwork::FindAugmentingPath() const {
  std::vector<Node> parent(num_nodes_, std::numeric_limits<Node>::max());
  std::vector<int> visited(num_nodes_, unvisited);
  std::queue<Node> order;

  visited[source_] = 1;
  order.emplace(source_);

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();
    if (node == sink_) {
      return std::make_pair(true, std::move(parent));
    }

    for (const auto &[adj_node, capacity] : adj_list_[node]) {
      if (capacity > 0 && visited[adj_node] == unvisited) {
        parent[adj_node] = node;
        order.emplace(adj_node);
        visited[adj_node] = 1;
      }
    }
  }
  return std::make_pair(false, std::move(parent));
}
} // namespace uva_10330

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_edges, num_sources, num_sinks;
  std::vector<uva_10330::Capacity> capacities;
  uva_10330::EdgeList edge_list;
  std::vector<uva_10330::Node> sources;
  std::vector<uva_10330::Node> sinks;

  while (std::cin >> num_nodes, !std::cin.eof()) {
    capacities.resize(num_nodes);
    for (size_t i = 0; i < num_nodes; ++i) {
      std::cin >> capacities[i];
    }

    std::cin >> num_edges;
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cin >> num_sources >> num_sinks;
    sources.resize(num_sources);
    sinks.resize(num_sinks);
    for (size_t i = 0; i < num_sources; ++i) {
      std::cin >> sources[i];
    }
    for (size_t i = 0; i < num_sinks; ++i) {
      std::cin >> sinks[i];
    }

    std::cout << uva_10330::FlowNetwork(capacities, edge_list, sources, sinks)
                     .GetMaxFlow()
              << std::endl;
  }
  return 0;
}
