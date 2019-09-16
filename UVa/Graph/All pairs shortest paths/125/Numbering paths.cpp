// WIP

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using Node = size_t;
using AdjacencyMatrix = std::vector<std::vector<int>>;
using EdgeList = std::vector<std::pair<Node, Node>>;

const auto infinity = std::numeric_limits<int>::max();

class Navigator {
public:
  Navigator(size_t num_nodes, const EdgeList &edge_list);

  AdjacencyMatrix GetAllPathCount();

private:
  void Normalize();

  const size_t num_nodes_;
  AdjacencyMatrix adj_matrix_;
};

Navigator::Navigator(const size_t num_nodes, const EdgeList &edge_list)
    : num_nodes_(num_nodes) {
  adj_matrix_.resize(num_nodes_, std::vector<int>(num_nodes_));
  for (const auto &[u, v] : edge_list) {
    adj_matrix_[u][v] = 1;
  }
}

AdjacencyMatrix Navigator::GetAllPathCount() {
  auto transitivity = adj_matrix_;
  for (Node k = 0; k < num_nodes_; ++k) {
    for (Node i = 0; i < num_nodes_; ++i) {
      for (Node j = 0; j < num_nodes_; ++j) {
        transitivity[i][j] |= transitivity[i][k] & transitivity[k][j];
      }
    }
  }

  for (Node i = 0; i < num_nodes_; ++i) {
    for (Node j = 0; j < num_nodes_; ++j) {
      if (transitivity[i][j] == 0) {
        continue;
      }
      for (Node k = 0; k < num_nodes_; ++k) {
        if (transitivity[i][k] != 0 && transitivity[k][j] != 0) {
          ++adj_matrix_[i][j];
        }
      }
    }
  }
  return adj_matrix_;
}

void Navigator::Normalize() {
  for (auto &row : adj_matrix_) {
    for (auto &count : row) {
      count = count == infinity ? 0 : count;
    }
  }
}

int main(int argc, char *argv[]) {
  size_t num_edges;
  EdgeList edge_list;
  auto t = 0;

  while (std::cin >> num_edges, !std::cin.eof()) {
    edge_list.resize(num_edges);
    size_t num_nodes = 0;
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
      num_nodes = std::max(num_nodes,
                           std::max(edge_list[i].first, edge_list[i].second));
    }
    ++num_nodes;
    std::cout << "matrix for city " << t++ << std::endl;
    auto matrix = Navigator(num_nodes, edge_list).GetAllPathCount();
    for (const auto &row : matrix) {
      auto separator = "";
      for (const auto &count : row) {
        std::cout << separator << count;
        separator = " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
