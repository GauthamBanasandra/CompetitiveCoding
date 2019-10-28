#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace round_368 {
using Node = size_t;
using Cost = long;
using EdgeList = std::vector<std::tuple<Node, Node, Cost>>;

const auto infinity = std::numeric_limits<Cost>::max();

Cost GetMinCost(const EdgeList &edge_list,
                const std::unordered_set<Node> &storage) {
  auto min_cost = infinity;
  for (const auto &[u, v, cost] : edge_list) {
    if ((storage.find(u) == storage.end() &&
         storage.find(v) != storage.end()) ||
        (storage.find(u) != storage.end() &&
         storage.find(v) == storage.end())) {
      min_cost = std::min(min_cost, cost);
    }
  }
  return min_cost == infinity ? -1 : min_cost;
}
} // namespace round_368

int main(int argc, char *argv[]) {
  size_t num_cities;
  size_t num_roads;
  size_t num_storage;

  std::cin >> num_cities >> num_roads >> num_storage;
  round_368::EdgeList edge_list(num_roads);
  for (size_t i = 0; i < num_roads; ++i) {
    std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
        std::get<2>(edge_list[i]);
  }

  round_368::Node storage_node;
  std::unordered_set<round_368::Node> storage;
  for (size_t i = 0; i < num_storage; ++i) {
    std::cin >> storage_node;
    storage.insert(storage_node);
  }

  std::cout << round_368::GetMinCost(edge_list, storage) << std::endl;
  return 0;
}
