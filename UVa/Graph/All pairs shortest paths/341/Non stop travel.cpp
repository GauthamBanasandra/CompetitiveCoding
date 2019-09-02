#include <ios>
#include <iostream>
#include <limits>
#include <vector>

namespace uva_341 {
using Node = size_t;
using Cost = int;
template <typename T> using AdjacencyMatrix = std::vector<std::vector<T>>;
using AdjacencyList = std::vector<std::vector<std::pair<Node, Cost>>>;

const auto infinity = std::numeric_limits<Cost>::max();

class Navigator {
public:
  Navigator(size_t num_nodes, const AdjacencyList &adj_list);

  std::pair<std::vector<Node>, Cost> GetMinPathWithCost(Node u, Node v);

private:
  static void GetPath(Node u, Node v, const AdjacencyMatrix<Node> &parent,
                      std::vector<Node> &path);

  size_t num_nodes_;
  AdjacencyMatrix<Cost> adj_matrix_;
};

Navigator::Navigator(const size_t num_nodes, const AdjacencyList &adj_list)
    : num_nodes_(num_nodes + 1) {
  adj_matrix_.resize(num_nodes_, std::vector<Cost>(num_nodes_, infinity));
  for (Node u = 1; u < num_nodes_; ++u) {
    for (const auto &[v, cost] : adj_list[u - 1]) {
      adj_matrix_[u][v] = cost;
    }
  }
}

std::pair<std::vector<Node>, Cost> Navigator::GetMinPathWithCost(const Node u,
                                                                 const Node v) {
  AdjacencyMatrix<Node> parent(num_nodes_);
  for (size_t i = 1; i < num_nodes_; ++i) {
    parent[i].resize(num_nodes_, i);
  }

  for (Node k = 1; k < num_nodes_; ++k) {
    for (Node i = 1; i < num_nodes_; ++i) {
      for (Node j = 1; j < num_nodes_; ++j) {
        const auto cost =
            adj_matrix_[i][k] == infinity || adj_matrix_[k][j] == infinity
                ? infinity
                : adj_matrix_[i][k] + adj_matrix_[k][j];
        if (cost < adj_matrix_[i][j]) {
          adj_matrix_[i][j] = cost;
          parent[i][j] = parent[k][j];
        }
      }
    }
  }

  std::vector<Node> path;
  path.reserve(num_nodes_);
  GetPath(u, v, parent, path);
  return {path, adj_matrix_[u][v]};
}

void Navigator::GetPath(const Node u, Node v,
                        const AdjacencyMatrix<Node> &parent,
                        std::vector<Node> &path) {
  if (u != v) {
    GetPath(u, parent[u][v], parent, path);
  }
  path.emplace_back(v);
}
} // namespace uva_341

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_edges, t = 0;
  uva_341::Node u, v;
  uva_341::AdjacencyList adj_list;

  while (std::cin >> num_nodes, num_nodes != 0) {
    adj_list.resize(num_nodes);
    for (size_t i = 0; i < num_nodes; ++i) {
      std::cin >> num_edges;
      adj_list[i].resize(num_edges);
      for (size_t j = 0; j < num_edges; ++j) {
        std::cin >> adj_list[i][j].first >> adj_list[i][j].second;
      }
    }
    std::cin >> u >> v;

    std::cout << "Case " << ++t << ": Path =";
    auto [path, cost] =
        uva_341::Navigator(num_nodes, adj_list).GetMinPathWithCost(u, v);
    for (const auto &node : path) {
      std::cout << ' ' << node;
    }
    std::cout << "; " << cost << " second delay" << std::endl;
  }
  return 0;
}
