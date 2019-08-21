#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

namespace uva_558 {
using Node = size_t;
using Cost = int;

const auto infinity = std::numeric_limits<Cost>::max();

bool IsPossible(const size_t num_nodes,
                const std::vector<std::tuple<Node, Node, Cost>> &edge_list) {
  std::vector<Cost> min_cost(num_nodes, infinity);
  min_cost[0] = 0;
  for (size_t i = 0; i < num_nodes - 1; ++i) {
    for (const auto &[u, v, cost] : edge_list) {
      min_cost[v] = min_cost[u] == infinity
                        ? cost
                        : std::min(min_cost[v], min_cost[u] + cost);
    }
  }

  auto has_neg_cycle = false;
  for (const auto &[u, v, cost] : edge_list) {
    if (min_cost[u] == infinity) {
      continue;
    }

    if (min_cost[v] > min_cost[u] + cost) {
      has_neg_cycle = true;
      break;
    }
  }
  return has_neg_cycle;
}
} // namespace uva_558

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t c, n, m;
  std::vector<std::tuple<uva_558::Node, uva_558::Node, uva_558::Cost>>
      edge_list;

  std::cin >> c;
  while (c--) {
    std::cin >> n >> m;
    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cout << (uva_558::IsPossible(n, edge_list) ? "possible"
                                                    : "not possible")
              << std::endl;
  }
  return 0;
}
