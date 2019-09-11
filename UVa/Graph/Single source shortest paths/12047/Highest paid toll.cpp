#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace uva_12047 {
using Node = size_t;
using Cost = int;
using EdgeList = std::vector<std::tuple<Node, Node, Cost>>;
using AdjacencyList = std::vector<std::vector<std::pair<Node, Cost>>>;

const auto infinity = std::numeric_limits<Cost>::max();

class Navigator {
public:
  Navigator(size_t num_nodes, EdgeList &edge_list, Node source,
            Node destination, Cost cost_limit);

  Cost GetMaxEdgeCost() const;

private:
  std::vector<Cost> GetMinDistanceFrom(Node source,
                                       const AdjacencyList &adj_list) const;

  const size_t num_nodes_;
  EdgeList &edge_list_;
  const Node source_;
  const Node destination_;
  const Cost cost_limit_;
  // We store 2 adjacency lists
  // adj_list_ is adjacency list as per the given graph (u -> v)
  AdjacencyList adj_list_;
  // adj_list_inverse_ is the adjacency list where all the edges are
  // reversed (v -> u)
  AdjacencyList adj_list_inverse_;
};

Navigator::Navigator(const size_t num_nodes, EdgeList &edge_list,
                     const Node source, const Node destination,
                     const Cost cost_limit)
    : num_nodes_{num_nodes + 1}, edge_list_{edge_list}, source_{source},
      destination_{destination}, cost_limit_{cost_limit} {
  adj_list_.resize(num_nodes_);
  adj_list_inverse_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list_) {
    adj_list_[u].emplace_back(v, cost);
    adj_list_inverse_[v].emplace_back(u, cost);
  }
}

Cost Navigator::GetMaxEdgeCost() const {
  // Run Dijkstra from source_, so we know the minimum cost from source_ to all
  // nodes
  auto from_source = GetMinDistanceFrom(source_, adj_list_);

  // We also want to know the minimum cost to all nodes from destination
  // Since the graph is a directed graph, we need to run Dijkstra from
  // destination_ on adj_list_inverse_
  auto from_destination = GetMinDistanceFrom(destination_, adj_list_inverse_);

  auto max_cost = -1;
  for (const auto &[u, v, cost] : edge_list_) {
    if (from_source[u] == infinity || from_destination[v] == infinity ||
        // This line is the crux of this solution
        // For each edge(u, v), we know the minimum cost from source_ -> u and
        // the minimum cost from v -> destination_
        // Therefore, we can get the cost of the path from source_ to
        // destination_ where the current edge is included in the path
        // "with the best minimum possible cost"
        from_source[u] + cost + from_destination[v] > cost_limit_) {
      continue;
    }
    max_cost = std::max(max_cost, cost);
  }
  return max_cost;
}

std::vector<Cost>
Navigator::GetMinDistanceFrom(Node source,
                              const AdjacencyList &adj_list) const {
  std::vector<Cost> min_cost(num_nodes_, infinity);
  std::priority_queue<std::pair<Cost, Node>, std::vector<std::pair<Cost, Node>>,
                      std::greater<>>
      order;
  min_cost[source] = 0;
  order.emplace(0, source);

  while (!order.empty()) {
    auto [current_cost, node] = order.top();
    order.pop();

    if (current_cost > min_cost[node]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost] : adj_list[node]) {
      auto cost = min_cost[node] + adj_cost;
      if (cost < min_cost[adj_node]) {
        min_cost[adj_node] = cost;
        order.emplace(cost, adj_node);
      }
    }
  }
  return min_cost;
}
} // namespace uva_12047

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t tc, n, m;
  uva_12047::Node s, t;
  uva_12047::Cost p;
  uva_12047::EdgeList edge_list;

  std::cin >> tc;
  while (tc--) {
    std::cin >> n >> m >> s >> t >> p;
    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cout << uva_12047::Navigator(n, edge_list, s, t, p).GetMaxEdgeCost()
              << std::endl;
  }
  return 0;
}
