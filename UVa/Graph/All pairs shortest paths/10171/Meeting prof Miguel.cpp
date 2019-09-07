#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

namespace uva_10171 {
using Cost = int;
using Node = size_t;
template <typename T> using AdjacencyMatrix = std::vector<std::vector<T>>;

const auto infinity{std::numeric_limits<Cost>::max()};
const size_t num_nodes{26};
enum class Direction { kUnidirectional, kBidirectional };

class Navigator {
public:
  Navigator(
      const std::vector<std::tuple<Direction, Node, Node, Cost>> &edge_list);

  std::vector<Cost> GetMinCost(Node source);

private:
  AdjacencyMatrix<Cost> adj_matrix_;
};

Navigator::Navigator(
    const std::vector<std::tuple<Direction, Node, Node, Cost>> &edge_list) {
  adj_matrix_.resize(num_nodes, std::vector<Cost>(num_nodes, infinity));
  for (Node i = 0; i < num_nodes; ++i) {
    adj_matrix_[i][i] = 0;
  }

  for (const auto &[direction, u, v, cost] : edge_list) {
    adj_matrix_[u][v] = std::min(adj_matrix_[u][v], cost);
    if (direction == Direction::kBidirectional) {
      adj_matrix_[v][u] = std::min(adj_matrix_[v][u], cost);
    }
  }
}

std::vector<Cost> Navigator::GetMinCost(const Node source) {
  for (Node k = 0; k < num_nodes; ++k) {
    for (Node i = 0; i < num_nodes; ++i) {
      for (Node j = 0; j < num_nodes; ++j) {
        auto cost =
            adj_matrix_[i][k] == infinity || adj_matrix_[k][j] == infinity
                ? infinity
                : adj_matrix_[i][k] + adj_matrix_[k][j];
        adj_matrix_[i][j] = std::min(adj_matrix_[i][j], cost);
      }
    }
  }
  return adj_matrix_[source];
}

std::tuple<bool, Cost, std::vector<Node>>
GetCombinedMinCost(const std::vector<Cost> &young,
                   const std::vector<Cost> &mature) {
  auto min_cost = infinity;
  std::vector<Node> nodes;

  for (size_t i = 0; i < num_nodes; ++i) {
    if (young[i] == infinity || mature[i] == infinity) {
      continue;
    }

    const auto cost = young[i] + mature[i];
    if (cost < min_cost) {
      min_cost = cost;
      nodes.clear();
      nodes.emplace_back(i);
    } else if (cost == min_cost) {
      nodes.emplace_back(i);
    }
  }

  if (min_cost == infinity) {
    return {false, min_cost, nodes};
  }
  return {true, min_cost, nodes};
}

Direction GetDirection(const char direction) {
  if (!(direction == 'U' || direction == 'B')) {
    assert(false);
  }

  if (direction == 'U') {
    return Direction::kUnidirectional;
  }
  return Direction::kBidirectional;
}

Node GetNode(const char node) {
  if (node < 'A' || node > 'Z') {
    assert(false);
  }
  return static_cast<Node>(node) - 'A';
}
} // namespace uva_10171

int main(int argc, char *argv[]) {
  using namespace uva_10171;
  std::ios::sync_with_stdio(false);

  size_t n;
  Cost cost;
  char direction, u, v, person, source_1, source_2;

  while (std::cin >> n, n != 0) {
    std::vector<std::tuple<Direction, Node, Node, Cost>> edge_list_young,
        edge_list_mature;

    for (size_t i = 0; i < n; ++i) {
      std::cin >> person >> direction >> u >> v >> cost;
      if (person == 'Y') {
        edge_list_young.emplace_back(GetDirection(direction), GetNode(u),
                                     GetNode(v), cost);
      } else if (person == 'M') {
        edge_list_mature.emplace_back(GetDirection(direction), GetNode(u),
                                      GetNode(v), cost);
      } else {
        assert(false);
      }
    }

    std::cin >> source_1 >> source_2;

    Navigator navigator_young(edge_list_young);
    Navigator navigator_mature(edge_list_mature);
    auto [is_possible, min_cost, nodes] =
        GetCombinedMinCost(navigator_young.GetMinCost(GetNode(source_1)),
                           navigator_mature.GetMinCost(GetNode(source_2)));
    if (is_possible) {
      std::cout << min_cost;
      for (const auto node : nodes) {
        std::cout << " " << static_cast<char>(node + 'A');
      }
      std::cout << std::endl;
    } else {
      std::cout << "You will never meet." << std::endl;
    }
  }
  return 0;
}
