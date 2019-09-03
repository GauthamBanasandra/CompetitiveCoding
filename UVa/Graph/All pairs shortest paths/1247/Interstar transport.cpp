#include <ios>
#include <iostream>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

namespace uva_1247 {
using Cost = int;
using Node = size_t;
template <typename T> using AdjacencyMatrix = std::vector<std::vector<T>>;
using EdgeList = std::vector<std::tuple<Node, Node, Cost>>;

const auto infinity = std::numeric_limits<Cost>::max();

class Navigator {
public:
  Navigator(size_t num_nodes, const EdgeList &edge_list);

  std::vector<Node> GetMinCostRoute(Node source, Node destination) const;

private:
  void GetPath(Node u, Node v, std::vector<Node> &path) const;

  const size_t num_nodes_;
  AdjacencyMatrix<std::pair<Cost, size_t>> adj_matrix_;
  AdjacencyMatrix<Node> parent_;
};

Navigator::Navigator(const size_t num_nodes, const EdgeList &edge_list)
    : num_nodes_(num_nodes) {
  adj_matrix_.assign(num_nodes_, std::vector<std::pair<Cost, size_t>>(
                                     num_nodes_, {infinity, 0}));
  for (const auto &[u, v, cost] : edge_list) {
    adj_matrix_[u][v] = {cost, 1};
    adj_matrix_[v][u] = {cost, 1};
  }
  for (Node i = 0; i < num_nodes_; ++i) {
    adj_matrix_[i][i] = {0, 0};
  }

  parent_.resize(num_nodes_);
  for (Node i = 0; i < num_nodes_; ++i) {
    parent_[i].resize(num_nodes_);
    for (Node j = 0; j < num_nodes_; ++j) {
      parent_[i][j] = i;
    }
  }

  for (Node k = 0; k < num_nodes_; ++k) {
    for (Node i = 0; i < num_nodes_; ++i) {
      for (Node j = 0; j < num_nodes_; ++j) {
        auto [src_intermediate_cost, src_intermediate_hops] = adj_matrix_[i][k];
        auto [intermediate_dst_cost, intermediate_dst_hops] = adj_matrix_[k][j];
        auto [src_dst_cost, src_dst_hops] = adj_matrix_[i][j];

        auto cost = src_intermediate_cost == infinity ||
                            intermediate_dst_cost == infinity
                        ? infinity
                        : src_intermediate_cost + intermediate_dst_cost;
        // As long as the cost i->k-> is less than cost i->j
        if (cost < src_dst_cost ||
            // Or if both the costs are equal, then we break the tie by choosing
            // the lesser hop count from i->k and i->j
            cost == src_dst_cost && src_intermediate_hops < src_dst_hops) {
          // Note here that we take the lesser hop count of (i->k, i->j)
          // rather than (k->j, i->j) because we are "going to" the
          // intermediate node k. Thus, we need to consider the hop count of
          // reaching k (i->k) rather than departing from k (k->j)
          adj_matrix_[i][j] = {cost, intermediate_dst_hops + 1};
          parent_[i][j] = parent_[k][j];
        }
      }
    }
  }
}

std::vector<Node> Navigator::GetMinCostRoute(const Node source,
                                             const Node destination) const {
  std::vector<Node> path;
  path.reserve(num_nodes_);

  GetPath(source, destination, path);
  return path;
}

void Navigator::GetPath(const Node u, Node v, std::vector<Node> &path) const {
  if (u != v) {
    GetPath(u, parent_[u][v], path);
  }
  path.emplace_back(v);
}
} // namespace uva_1247

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_edges, q;
  char u, v;
  uva_1247::Cost cost;
  uva_1247::EdgeList edge_list;

  while (std::cin >> num_nodes >> num_edges, !std::cin.eof()) {
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> u >> v >> cost;
      edge_list[i] = {u - 'A', v - 'A', cost};
    }

    uva_1247::Navigator navigator(num_nodes, edge_list);

    std::cin >> q;
    while (q--) {
      std::cin >> u >> v;
      auto separator = "";
      for (auto node : navigator.GetMinCostRoute(u - 'A', v - 'A')) {
        std::cout << separator << static_cast<char>(node + 'A');
        separator = " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
