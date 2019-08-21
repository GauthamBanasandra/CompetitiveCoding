// WA

#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using Node = size_t;
using Cost = int;

const auto infinity = std::numeric_limits<Cost>::max();

class Selector {
public:
  Selector(size_t num_nodes, const std::vector<Cost> &business,
           const std::vector<std::pair<Node, Node>> &edge_list);

  Cost GetMinTotalCost(Node destination);

private:
  const size_t num_nodes_;
  std::vector<std::tuple<Node, Node, Cost>> edge_list_;
};

Selector::Selector(const size_t num_nodes, const std::vector<Cost> &business,
                   const std::vector<std::pair<Node, Node>> &edge_list)
    : num_nodes_(num_nodes + 1) {
  edge_list_.resize(edge_list.size());
  std::transform(edge_list.begin(), edge_list.end(), edge_list_.begin(),
                 [&business](const std::pair<Node, Node> &edge)
                     -> std::tuple<Node, Node, Cost> {
                   auto [u, v] = edge;
                   const auto value = business[v - 1] - business[u - 1];
                   return {u, v, value * value * value};
                 });
}

Cost Selector::GetMinTotalCost(const Node destination) {
  std::vector<Cost> min_cost(num_nodes_, infinity);
  min_cost[1] = 0;
  for (size_t i = 0; i < num_nodes_ - 1; ++i) {
    for (const auto &[u, v, cost] : edge_list_) {
      min_cost[v] = min_cost[u] == infinity
                        ? cost
                        : std::min(min_cost[v], min_cost[u] + cost);
    }
  }
  return min_cost[destination];
}

int main(int argc, char *argv[]) {
  size_t n, m, q, t = 0;
  Node destination;
  std::vector<Cost> business;
  std::vector<std::pair<Node, Node>> edge_list;

  while (std::cin >> n, !std::cin.eof()) {
    business.resize(n);
    for (size_t i = 0; i < n; ++i) {
      std::cin >> business[i];
    }

    std::cin >> m;
    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    Selector selector(n, business, edge_list);
    std::cout << "Set #" << ++t << std::endl;
    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
      std::cin >> destination;
      const auto min_cost = selector.GetMinTotalCost(destination);
      if (min_cost < 3 || min_cost == infinity) {
        std::cout << '?' << std::endl;
      } else {
        std::cout << min_cost << std::endl;
      }
    }
  }
  return 0;
}
