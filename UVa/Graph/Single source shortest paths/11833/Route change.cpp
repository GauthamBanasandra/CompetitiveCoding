#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace uva_11833 {
using Node = size_t;
using Cost = int;

const auto infinity = std::numeric_limits<Cost>::max();

class RouteGuide {
public:
  RouteGuide(size_t num_nodes,
             const std::vector<std::tuple<Node, Node, Cost>> &edge_list,
             Node destination, Node source);

  Cost GetShortestPath() const;

  enum RouteType {
    kRegular,
    kService,
    Count // Not a RouteType
  };

private:
  RouteType GetRouteType(const Node node) const {
    return node <= destination_ ? RouteType::kService : RouteType::kRegular;
  }

  const size_t num_nodes_;
  const Node source_;
  const Node destination_;
  std::vector<std::vector<std::pair<Node, Cost>>> adj_list_;
};

RouteGuide::RouteGuide(
    const size_t num_nodes,
    const std::vector<std::tuple<Node, Node, Cost>> &edge_list,
    const Node destination, const Node source)
    : num_nodes_{num_nodes}, source_{source}, destination_{destination} {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list) {
    adj_list_[u].emplace_back(v, cost);
    adj_list_[v].emplace_back(u, cost);
  }
}

struct Comparator {
  bool
  operator()(const std::tuple<Cost, Node, RouteGuide::RouteType> &a,
             const std::tuple<Cost, Node, RouteGuide::RouteType> &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

Cost RouteGuide::GetShortestPath() const {
  std::vector<std::vector<Cost>> min_cost(
      num_nodes_, std::vector<Cost>(RouteType::Count, infinity));
  std::priority_queue<std::tuple<Cost, Node, RouteType>,
                      std::vector<std::tuple<Cost, Node, RouteType>>,
                      Comparator>
      order;

  min_cost[source_][RouteType::kRegular] = 0;
  order.emplace(0, source_, RouteType::kRegular);

  while (!order.empty()) {
    auto [current_cost, node, type] = order.top();
    order.pop();

    if (current_cost > min_cost[node][type]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost] : adj_list_[node]) {
      auto cost = min_cost[node][type] + adj_cost;
      const auto adj_type = GetRouteType(adj_node);

      if (type == RouteType::kService &&
          (adj_type != RouteType::kService || node + 1 != adj_node)) {
        continue;
      }

      if (cost < min_cost[adj_node][adj_type]) {
        min_cost[adj_node][adj_type] = cost;
        order.emplace(cost, adj_node, adj_type);
      }
    }
  }
  return min_cost[destination_][RouteType::kService];
}
} // namespace uva_11833

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t n, m;
  uva_11833::Node c, k;
  std::vector<std::tuple<uva_11833::Node, uva_11833::Node, uva_11833::Cost>>
      edge_list;

  while (std::cin >> n >> m >> c >> k, n || m || c || k) {
    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cout << uva_11833::RouteGuide(n, edge_list, c - 1, k).GetShortestPath()
              << std::endl;
  }
  return 0;
}
