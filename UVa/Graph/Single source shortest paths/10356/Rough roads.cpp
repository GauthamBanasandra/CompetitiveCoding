#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace uva_10356 {
using Node = size_t;
using Cost = int;

const auto infinity = std::numeric_limits<Cost>::max();

class RouteGuide {
public:
  RouteGuide(size_t num_nodes,
             const std::vector<std::tuple<size_t, size_t, int>> &edge_list);

  Cost GetShortestPath() const;

  enum Mode {
    kWalk,
    kCycle,
    Count // Not a Mode
  };

private:
  const size_t num_nodes_;
  const Node source_{0};
  const Node destination_;
  std::vector<std::vector<std::pair<Node, Cost>>> adj_list_;
};

RouteGuide::RouteGuide(
    const size_t num_nodes,
    const std::vector<std::tuple<Node, Node, Cost>> &edge_list)
    : num_nodes_{num_nodes}, destination_{num_nodes_ - 1} {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list) {
    adj_list_[u].emplace_back(v, cost);
    adj_list_[v].emplace_back(u, cost);
  }
}

struct Comparator {
  bool operator()(const std::tuple<Cost, Node, RouteGuide::Mode> &a,
                  const std::tuple<Cost, Node, RouteGuide::Mode> &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

Cost RouteGuide::GetShortestPath() const {
  // Keep track of also the mode(by walking or cycling) by which the destination
  // node was reached
  std::vector<std::vector<Cost>> min_cost(
      num_nodes_, std::vector<Cost>(Mode::Count, infinity));
  std::priority_queue<std::tuple<Cost, Node, Mode>,
                      std::vector<std::tuple<Cost, Node, Mode>>, Comparator>
      order;

  min_cost[source_][Mode::kCycle] = 0;
  order.emplace(0, source_, Mode::kCycle);

  while (!order.empty()) {
    auto [current_cost, node, mode] = order.top();
    order.pop();

    if (current_cost > min_cost[node][mode]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost] : adj_list_[node]) {
      auto cost = min_cost[node][mode] + adj_cost;
      if (cost < min_cost[adj_node][1 - mode]) {
        min_cost[adj_node][1 - mode] = cost;
        order.emplace(cost, adj_node, static_cast<Mode>(1 - mode));
      }
    }
  }
  return min_cost[destination_][Mode::kCycle];
}
} // namespace uva_10356

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes = 0, num_edges = 0, t = 0;

  while (std::cin >> num_nodes >> num_edges, !std::cin.eof()) {
    std::vector<std::tuple<size_t, size_t, int>> edge_list;
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cout << "Set #" << ++t << std::endl;
    const auto min_cost =
        uva_10356::RouteGuide(num_nodes, edge_list).GetShortestPath();
    if (min_cost == uva_10356::infinity) {
      std::cout << '?' << std::endl;
    } else {
      std::cout << min_cost << std::endl;
    }
  }
  return 0;
}
