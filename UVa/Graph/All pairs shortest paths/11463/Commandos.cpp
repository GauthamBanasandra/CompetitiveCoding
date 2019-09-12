#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

namespace uva_11463 {
using Cost = int;
using Node = size_t;
template <typename T> using AdjacencyMatrix = std::vector<std::vector<T>>;
using EdgeList = std::vector<std::pair<Node, Node>>;

const auto infinity = std::numeric_limits<Cost>::max();

Cost GetOperationTime(const size_t num_nodes, const EdgeList &edge_list,
                      const Node source, const Node destination) {
  AdjacencyMatrix<Cost> adj_matrix(num_nodes,
                                   std::vector<Cost>(num_nodes, infinity));

  for (const auto &[u, v] : edge_list) {
    adj_matrix[u][v] = adj_matrix[v][u] = 1;
  }

  for (Node i = 0; i < num_nodes; ++i) {
    adj_matrix[i][i] = 0;
  }

  for (Node k = 0; k < num_nodes; ++k) {
    for (Node i = 0; i < num_nodes; ++i) {
      for (Node j = 0; j < num_nodes; ++j) {
        if (adj_matrix[i][k] == infinity || adj_matrix[k][j] == infinity) {
          continue;
        }
        adj_matrix[i][j] =
            std::min(adj_matrix[i][j], adj_matrix[i][k] + adj_matrix[k][j]);
      }
    }
  }

  auto operation_cost = 0;
  for (Node i = 0; i < num_nodes; ++i) {
    if (adj_matrix[source][i] == infinity ||
        adj_matrix[destination][i] == infinity) {
      continue;
    }

    // Measure the shortest distance from the farthest point from source and
    // destination combined
    operation_cost = std::max(operation_cost, adj_matrix[source][i] +
                                                  adj_matrix[destination][i]);
  }
  return operation_cost;
}
} // namespace uva_11463

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t;
  size_t num_nodes, num_edges;
  uva_11463::EdgeList edge_list;
  uva_11463::Node source, destination;

  std::cin >> t;
  for (uva_11463::Node i = 1; i <= t; ++i) {
    std::cin >> num_nodes >> num_edges;
    edge_list.resize(num_edges);
    for (size_t j = 0; j < num_edges; ++j) {
      std::cin >> edge_list[j].first >> edge_list[j].second;
    }
    std::cin >> source >> destination;
    std::cout << "Case " << i << ": "
              << uva_11463::GetOperationTime(num_nodes, edge_list, source,
                                             destination)
              << std::endl;
  }
}
