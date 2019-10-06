#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_10480 {
using Node = size_t;
using Capacity = long long;

const auto infinity = std::numeric_limits<Capacity>::max();
const auto unvisited = -1;

class FlowNetwork {
public:
  FlowNetwork(size_t num_nodes,
              const std::vector<std::tuple<Node, Node, Capacity>> &edge_list);

  std::vector<std::pair<Node, Node>> FindBridges();

private:
  Capacity Augment(const std::vector<Node> &parent);
  std::pair<bool, std::vector<Node>> FindAugmentingPath() const;
  void FindMaxFlow();
  std::vector<int> FindReachableNodes(Node source) const;

  const size_t num_nodes_;
  const Node source_{0};
  const Node sink_{1};
  std::vector<std::unordered_map<Node, Capacity>> adj_list_;
};

FlowNetwork::FlowNetwork(
    const size_t num_nodes,
    const std::vector<std::tuple<Node, Node, Capacity>> &edge_list)
    : num_nodes_{num_nodes} {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, capacity] : edge_list) {
    adj_list_[u - 1][v - 1] = adj_list_[v - 1][u - 1] = capacity;
  }
}

std::vector<std::pair<Node, Node>> FlowNetwork::FindBridges() {
  FindMaxFlow();
  auto src_component = FindReachableNodes(source_);

  std::vector<std::pair<Node, Node>> bridges;
  for (Node node = 0; node < num_nodes_; ++node) {
    if (src_component[node] == unvisited) {
      continue;
    }

    for (const auto &[adj_node, capacity] : adj_list_[node]) {
      if (src_component[adj_node] == unvisited) {
        bridges.emplace_back(node + 1, adj_node + 1);
      }
    }
  }
  return bridges;
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
        visited[adj_node] = 1;
        order.emplace(adj_node);
      }
    }
  }
  return std::make_pair(false, std::move(parent));
}

void FlowNetwork::FindMaxFlow() {
  Capacity max_flow = 0, flow = 0;
  do {
    auto [is_reachable, bfs_spanning_tree] = FindAugmentingPath();
    if (!is_reachable) {
      return;
    }
    flow = Augment(bfs_spanning_tree);
    max_flow += flow;
  } while (flow != 0);
}

std::vector<int> FlowNetwork::FindReachableNodes(Node source) const {
  std::vector<int> visited(num_nodes_, unvisited);
  std::queue<Node> order;

  visited[source] = 1;
  order.emplace(source);

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    for (const auto &[adj_node, capacity] : adj_list_[node]) {
      // capacity > 0 here is very important, otherwise, BFS will just return
      // all the nodes that are reachable from source. I had missed this the
      // first time
      if (capacity > 0 && visited[adj_node] == unvisited) {
        order.emplace(adj_node);
        visited[adj_node] = 1;
      }
    }
  }
  return visited;
}
} // namespace uva_10480

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_edges;
  std::vector<std::tuple<uva_10480::Node, uva_10480::Node, uva_10480::Capacity>>
      edge_list;

  while (std::cin >> num_nodes >> num_edges, num_nodes || num_edges) {
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    for (const auto &[u, v] :
         uva_10480::FlowNetwork(num_nodes, edge_list).FindBridges()) {
      std::cout << u << " " << v << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
