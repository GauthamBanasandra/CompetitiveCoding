#include <algorithm>
#include <cassert>
#include <functional>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_117 {
using NodeId = char;
using Cost = size_t;

const auto infinity = std::numeric_limits<Cost>::max();

class PathFinder {
public:
  explicit PathFinder(const std::vector<std::string> &edges);

  Cost FindMinimumEulerian() const;

private:
  std::vector<NodeId> GetNodesWithOddDegree() const;
  std::unordered_map<NodeId, Cost> InitAndGetMinCost() const;

  size_t graph_cost_{0};
  std::unordered_map<NodeId, size_t> in_degree_;
  std::unordered_map<NodeId, std::vector<std::pair<NodeId, Cost>>> adj_list_;
};

PathFinder::PathFinder(const std::vector<std::string> &edges) {
  for (const auto &edge : edges) {
    adj_list_[edge.front()].emplace_back(edge.back(), edge.size());
    adj_list_[edge.back()].emplace_back(edge.front(), edge.size());

    ++in_degree_[edge.front()];
    ++in_degree_[edge.back()];

    graph_cost_ += edge.size();
  }
}

Cost PathFinder::FindMinimumEulerian() const {
  auto odd_degree_node_ids = GetNodesWithOddDegree();
  if (odd_degree_node_ids.empty()) {
    return graph_cost_;
  }
  assert(odd_degree_node_ids.size() == 2);

  const auto &source_node = odd_degree_node_ids.front();
  const auto &destination_node = odd_degree_node_ids.back();

  auto min_cost = InitAndGetMinCost();
  std::priority_queue<std::pair<Cost, NodeId>,
                      std::vector<std::pair<Cost, NodeId>>, std::greater<>>
      order;

  order.emplace(0, source_node);
  min_cost[source_node] = 0;

  while (!order.empty()) {
    auto [current_cost, node] = order.top();
    order.pop();

    if (current_cost > min_cost[node]) {
      continue;
    }

    for (const auto &[adj_node, adj_node_cost] : adj_list_.at(node)) {
      auto cost = min_cost[node] + adj_node_cost;
      if (cost < min_cost[adj_node]) {
        min_cost[adj_node] = cost;
        order.emplace(cost, adj_node);
      }
    }
  }

  return graph_cost_ + min_cost[destination_node];
}

std::vector<NodeId> PathFinder::GetNodesWithOddDegree() const {
  std::vector<NodeId> node_ids;
  node_ids.reserve(adj_list_.size());
  for (const auto &[node_id, in_degree] : in_degree_) {
    if ((in_degree & 1) == 1) {
      node_ids.emplace_back(node_id);
    }
  }
  return node_ids;
}

std::unordered_map<NodeId, Cost> PathFinder::InitAndGetMinCost() const {
  std::unordered_map<NodeId, Cost> min_cost;
  for (const auto &[node_id, _] : adj_list_) {
    min_cost[node_id] = infinity;
  }
  return min_cost;
}
} // namespace uva_117

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string line;
  std::vector<std::string> edges;

  while (std::cin >> line, !std::cin.eof()) {
    if (line == "deadend") {
      std::cout << uva_117::PathFinder(edges).FindMinimumEulerian()
                << std::endl;
      edges.clear();
    } else {
      edges.emplace_back(line);
    }
  }

  return 0;
}
