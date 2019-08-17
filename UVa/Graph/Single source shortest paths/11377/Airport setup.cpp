#include <functional>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

namespace uva_11377 {
const auto infinity = std::numeric_limits<int>::max();

class Planner {
public:
  Planner(size_t num_nodes, const std::unordered_set<size_t> &special_nodes,
          const std::vector<std::pair<size_t, size_t>> &edge_list);

  int GetMinNumAirports(size_t source, size_t destination);

private:
  const size_t num_nodes_;
  const std::unordered_set<size_t> &special_nodes_;
  std::vector<std::vector<size_t>> adj_list_;
};

Planner::Planner(const size_t num_nodes,
                 const std::unordered_set<size_t> &special_nodes,
                 const std::vector<std::pair<size_t, size_t>> &edge_list)
    : num_nodes_(num_nodes + 1), special_nodes_(special_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list) {
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);
  }
}

int Planner::GetMinNumAirports(size_t source, const size_t destination) {
  if (source == destination) {
    return 0;
  }

  std::vector<int> min_cost(num_nodes_, infinity);
  std::priority_queue<std::pair<int, size_t>,
                      std::vector<std::pair<int, size_t>>, std::greater<>>
      order;

  min_cost[source] =
      special_nodes_.find(source) == special_nodes_.end() ? 1 : 0;
  order.emplace(min_cost[source], source);

  while (!order.empty()) {
    const auto [current_cost, node] = order.top();
    order.pop();

    if (current_cost > min_cost[node]) {
      continue;
    }

    for (const auto adj_node : adj_list_[node]) {
      auto cost =
          min_cost[node] +
          (special_nodes_.find(adj_node) == special_nodes_.end() ? 1 : 0);
      if (cost < min_cost[adj_node]) {
        min_cost[adj_node] = cost;
        order.emplace(cost, adj_node);
      }
    }
  }
  return min_cost[destination] == infinity ? -1 : min_cost[destination];
}
} // namespace uva_11377

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t x = 0, n = 0, m = 0, k = 0, q = 0, source = 0, destination = 0,
         city = 0;
  std::vector<std::pair<size_t, size_t>> edge_list;

  std::cin >> x;

  for (size_t t = 1; t <= x; ++t) {
    std::cin >> n >> m >> k;
    std::unordered_set<size_t> special_nodes;

    for (size_t i = 0; i < k; ++i) {
      std::cin >> city;
      special_nodes.insert(city);
    }

    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    uva_11377::Planner planner(n, special_nodes, edge_list);

    std::cout << "Case " << t << ':' << std::endl;
    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
      std::cin >> source >> destination;
      std::cout << planner.GetMinNumAirports(source, destination) << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
