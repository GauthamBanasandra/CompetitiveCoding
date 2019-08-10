// WA

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using PQItem = std::tuple<int, size_t, size_t>;
const auto infinity = std::numeric_limits<int>::max();

class RouteGuide {
public:
  RouteGuide(size_t num_nodes,
             const std::vector<std::tuple<size_t, size_t, int>> &edge_list);

  int GetShortestPathLen() const;

private:
  const size_t num_nodes_;
  std::vector<std::vector<std::pair<size_t, int>>> adj_list_;
};

RouteGuide::RouteGuide(
    const size_t num_nodes,
    const std::vector<std::tuple<size_t, size_t, int>> &edge_list)
    : num_nodes_(num_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list) {
    adj_list_[u].emplace_back(v, cost);
    adj_list_[v].emplace_back(u, cost);
  }
}

struct Comparator {
  bool operator()(const PQItem &a, const PQItem &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

int RouteGuide::GetShortestPathLen() const {
  std::priority_queue<PQItem, std::vector<PQItem>, Comparator> order;
  std::vector<int> min_cost(num_nodes_, infinity);
  auto min_cost_even_hops = infinity;
  order.emplace(0, 0, 0);
  min_cost[0] = 0;

  while (!order.empty()) {
    const auto [current_cost, node, hops] = order.top();
    order.pop();

    if (current_cost > min_cost[node]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost] : adj_list_[node]) {
      const auto cost = min_cost[node] + adj_cost;
      if (cost < min_cost[adj_node]) {
        order.emplace(cost, adj_node, hops + 1);
        min_cost[adj_node] = cost;
      }
      min_cost_even_hops = adj_node == num_nodes_ - 1 && ((hops + 1) & 1) == 0
                               ? std::min(min_cost_even_hops, cost)
                               : min_cost_even_hops;
    }
  }
  return min_cost_even_hops;
}

int main(int argc, char *argv[]) {
  size_t num_nodes = 0, num_edges = 0, u = 0, v = 0, t = 0;
  auto cost = 0;

  while (std::cin >> num_nodes >> num_edges, !std::cin.eof()) {
    std::vector<std::tuple<size_t, size_t, int>> edge_list;
    edge_list.reserve(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> u >> v >> cost;
      edge_list.emplace_back(u, v, cost);
    }

    std::cout << "Set #" << ++t << std::endl;
    const auto min_cost = RouteGuide(num_nodes, edge_list).GetShortestPathLen();
    if (min_cost == infinity) {
      std::cout << '?' << std::endl;
    } else {
      std::cout << min_cost << std::endl;
    }
  }
  return 0;
}
