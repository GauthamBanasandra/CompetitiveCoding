// WIP

#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using Cost = int;
using Node = size_t;
template <typename T> using AdjacencyMatrix = std::vector<std::vector<T>>;
using AdjacencyList = std::vector<std::tuple<Node, Node, Cost>>;

const auto infinity = std::numeric_limits<Cost>::max();

class Navigator {
public:
  Navigator(size_t num_nodes, const AdjacencyList &edge_list, Node src1,
            Node dst1, Node src2, Node dst2);

private:
  std::vector<Node> ComputeMinDistances(Node src, Node dst);
  static void GetPath(Node u, Node v, std::vector<Node> &path,
                      const AdjacencyMatrix<Node> &parent);

  const size_t num_nodes_;
  const Node src1_, dst1_;
  const Node src2_, dst2_;

  AdjacencyMatrix<Cost> adj_matrix_;
};

Navigator::Navigator(const size_t num_nodes, const AdjacencyList &edge_list,
                     const Node src1, const Node dst1, const Node src2,
                     const Node dst2)
    : num_nodes_(num_nodes + 1), src1_(src1), dst1_(dst1), src2_(src2),
      dst2_(dst2) {
  adj_matrix_.resize(num_nodes_, std::vector<Cost>(num_nodes_, infinity));
  for (const auto &[u, v, cost] : edge_list) {
    adj_matrix_[u][v] = adj_matrix_[v][u] = cost;
  }

  for (Node i = 1; i < num_nodes_; ++i) {
    adj_matrix_[i][i] = 0;
  }
}

std::vector<Node> Navigator::ComputeMinDistances(Node src, Node dst) {
  AdjacencyMatrix<Node> parent(num_nodes_);
  for (Node i = 1; i < num_nodes_; ++i) {
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
  GetPath(src, dst, path, parent);
  return path;
}

void Navigator::GetPath(Node u, Node v, std::vector<Node> &path,
                        const AdjacencyMatrix<Node> &parent) {
  if (u != v) {
    GetPath(u, parent[u][v], path, parent);
  }
  path.emplace_back(v);
}

int main(int argc, char *argv[]) { return 0; }
