// TLE

#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace uva_11367 {
const auto infinity = std::numeric_limits<int>::max();

class Planner {
public:
  Planner(const std::vector<int> &fuel_cost,
          const std::vector<std::tuple<size_t, size_t, int>> &edge_list,
          size_t num_nodes, int max_capacity);

  int GetMinCost(int capacity, size_t source, size_t destination) const;

private:
  const size_t num_nodes_;
  std::vector<std::vector<int>> fuel_needed_;
  std::vector<std::vector<std::vector<std::tuple<size_t, int, int>>>> adj_list_;
};

Planner::Planner(const std::vector<int> &fuel_cost,
                 const std::vector<std::tuple<size_t, size_t, int>> &edge_list,
                 const size_t num_nodes, const int max_capacity)
    : num_nodes_(num_nodes) {
  adj_list_.resize(
      num_nodes_,
      std::vector<std::vector<std::tuple<size_t, int, int>>>(max_capacity + 1));
  fuel_needed_.resize(num_nodes_, std::vector<int>(num_nodes_));

  for (const auto &[u, v, fuel_needed] : edge_list) {
    fuel_needed_[u][v] = fuel_needed_[v][u] = fuel_needed;

    for (auto src_fuel_level = 0; src_fuel_level <= max_capacity;
         ++src_fuel_level) {
      for (auto dst_fuel_level = 0; dst_fuel_level <= max_capacity;
           ++dst_fuel_level) {
        const auto fill = fuel_needed + dst_fuel_level - src_fuel_level;
        if (fill < 0 || src_fuel_level + fill > max_capacity) {
          continue;
        }
        adj_list_[u][src_fuel_level].emplace_back(v, dst_fuel_level,
                                                  fill * fuel_cost[u]);
        adj_list_[v][src_fuel_level].emplace_back(u, dst_fuel_level,
                                                  fill * fuel_cost[v]);
      }
    }
  }
}

struct Comparator {
  bool operator()(const std::tuple<int, size_t, int> &a,
                  const std::tuple<int, size_t, int> &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

int Planner::GetMinCost(const int capacity, const size_t source,
                        const size_t destination) const {
  std::vector<std::vector<int>> min_cost(
      num_nodes_, std::vector<int>(capacity + 1, infinity));
  std::priority_queue<std::tuple<int, size_t, int>,
                      std::vector<std::tuple<int, size_t, int>>, Comparator>
      order;
  min_cost[source][0] = 0;
  order.emplace(0, source, 0);

  while (!order.empty()) {
    const auto [current_cost, node, fuel_level] = order.top();
    order.pop();

    if (current_cost > min_cost[node][fuel_level]) {
      continue;
    }

    for (const auto &[adj_node, adj_fuel_level, adj_cost] :
         adj_list_[node][fuel_level]) {
      const auto fill =
          fuel_needed_[node][adj_node] + adj_fuel_level - fuel_level;
      if (fill < 0 || fuel_level + fill > capacity) {
        continue;
      }

      const auto cost = min_cost[node][fuel_level] + adj_cost;
      if (cost < min_cost[adj_node][adj_fuel_level]) {
        min_cost[adj_node][adj_fuel_level] = cost;
        order.emplace(cost, adj_node, adj_fuel_level);
      }
    }
  }
  return *std::min_element(min_cost[destination].begin(),
                           min_cost[destination].end());
}
} // namespace uva_11367

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  auto c = 0;
  size_t n = 0, m = 0, q = 0, u = 0, v = 0;
  std::vector<int> fuel_cost;
  std::vector<std::tuple<size_t, size_t, int>> edge_list;
  std::vector<std::tuple<int, size_t, size_t>> queries;

  while (std::cin >> n >> m, !std::cin.eof()) {
    fuel_cost.resize(n);
    for (size_t i = 0; i < n; ++i) {
      std::cin >> fuel_cost[i];
    }

    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> u >> v >> c;
      edge_list[i] = {u, v, c};
    }

    std::cin >> q;
    queries.resize(q);
    auto max_c = 0;
    for (size_t i = 0; i < q; ++i) {
      std::cin >> c >> u >> v;
      queries[i] = {c, u, v};
      max_c = std::max(max_c, c);
    }

    uva_11367::Planner planner(fuel_cost, edge_list, n, max_c);
    for (const auto &[capacity, source, destination] : queries) {
      const auto min_cost = planner.GetMinCost(capacity, source, destination);
      if (min_cost == uva_11367::infinity) {
        std::cout << "impossible" << std::endl;
      } else {
        std::cout << min_cost << std::endl;
      }
    }
  }
  return 0;
}
