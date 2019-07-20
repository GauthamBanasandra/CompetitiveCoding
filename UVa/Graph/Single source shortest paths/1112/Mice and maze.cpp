#include <functional>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace uva_1112 {
const auto infinity = std::numeric_limits<int>::max();

class Maze {
public:
  Maze(const std::vector<std::tuple<int, int, int>> &edge_list, int destination,
       int count_down, size_t num_nodes);

  int CountMiceExited() const;

private:
  int GetDistanceFrom(int start_node) const;

  const int destination_;
  const int count_down_;
  const size_t num_nodes_;
  std::vector<std::vector<std::pair<int, int>>> adj_list_;
};

Maze::Maze(const std::vector<std::tuple<int, int, int>> &edge_list,
           const int destination, const int count_down, const size_t num_nodes)
    : destination_(destination), count_down_(count_down),
      num_nodes_(num_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list) {
    adj_list_[u].emplace_back(v, cost);
  }
}

int Maze::CountMiceExited() const {
  auto num_exited = 0;
  for (auto i = 1; i < static_cast<int>(num_nodes_); ++i) {
    num_exited += GetDistanceFrom(i) <= count_down_ ? 1 : 0;
  }
  return num_exited;
}

int Maze::GetDistanceFrom(const int start_node) const {
  std::vector<int> min_cost(num_nodes_, infinity);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      order;
  order.emplace(0, start_node);
  min_cost[start_node] = 0;

  while (!order.empty()) {
    const auto [current_cost, node] = order.top();
    order.pop();

    if (current_cost > min_cost[node]) {
      continue;
    }

    for (const auto [adj_node, adj_node_cost] : adj_list_[node]) {
      const auto cost = min_cost[node] + adj_node_cost;
      if (cost < min_cost[adj_node]) {
        min_cost[adj_node] = cost;
        order.emplace(cost, adj_node);
      }
    }
  }
  return min_cost[destination_];
}
} // namespace uva_1112

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t = 0, num_nodes = 0, m = 0, c = 0;
  auto destination = 0, count_down = 0, u = 0, v = 0, cost = 0;

  std::cin >> t;
  while (t--) {
    std::cin >> num_nodes >> destination >> count_down >> m;
    std::vector<std::tuple<int, int, int>> edge_list;
    edge_list.reserve(m);
    ++num_nodes;

    for (size_t i = 0; i < m; ++i) {
      std::cin >> u >> v >> cost;
      edge_list.emplace_back(u, v, cost);
    }

    if (c++ > 0) {
      std::cout << std::endl;
    }
    std::cout << uva_1112::Maze(edge_list, destination, count_down, num_nodes)
                     .CountMiceExited()
              << std::endl;
  }
  return 0;
}
