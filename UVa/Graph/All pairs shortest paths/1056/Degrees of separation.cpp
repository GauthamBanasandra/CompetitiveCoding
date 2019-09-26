#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_1056 {
using Node = size_t;
const auto infinity = std::numeric_limits<int>::max();

class Navigator {
public:
  Navigator(size_t num_nodes,
            const std::vector<std::pair<std::string, std::string>> &edge_list);

  int GetMinimaxPathLen();

private:
  const size_t num_nodes_;
  std::vector<std::vector<int>> adj_matrix_;
};

Navigator::Navigator(
    const size_t num_nodes,
    const std::vector<std::pair<std::string, std::string>> &edge_list)
    : num_nodes_(num_nodes) {
  Node index = 0;
  std::unordered_map<std::string, Node> node_idx;

  const auto get_or_create_index =
      [&index, &node_idx](const std::string &node) -> Node {
    if (node_idx.find(node) == node_idx.end()) {
      node_idx[node] = index++;
    }
    return node_idx[node];
  };

  adj_matrix_.resize(num_nodes_, std::vector<int>(num_nodes_, infinity));
  for (const auto &[u_node, v_node] : edge_list) {
    const auto u = get_or_create_index(u_node);
    const auto v = get_or_create_index(v_node);
    adj_matrix_[u][v] = adj_matrix_[v][u] = 1;
  }

  for (Node i = 0; i < num_nodes_; ++i) {
    adj_matrix_[i][i] = 0;
  }
}

int Navigator::GetMinimaxPathLen() {
  for (Node k = 0; k < num_nodes_; ++k) {
    for (Node i = 0; i < num_nodes_; ++i) {
      for (Node j = 0; j < num_nodes_; ++j) {
        const auto cost =
            adj_matrix_[i][k] == infinity || adj_matrix_[k][j] == infinity
                ? infinity
                : adj_matrix_[i][k] + adj_matrix_[k][j];
        if (cost < adj_matrix_[i][j]) {
          adj_matrix_[i][j] = cost;
        }
      }
    }
  }

  auto max_hops = 0;
  for (Node i = 0; i < num_nodes_; ++i) {
    for (Node j = 0; j < num_nodes_; ++j) {
      if (adj_matrix_[i][j] == infinity) {
        return infinity;
      }
      max_hops = std::max(max_hops, adj_matrix_[i][j]);
    }
  }
  return max_hops;
}
} // namespace uva_1056

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_edges, t = 0;
  std::vector<std::pair<std::string, std::string>> edge_list;

  while (std::cin >> num_nodes >> num_edges, num_nodes || num_edges) {
    edge_list.resize(num_edges);
    for (size_t i = 0; i < num_edges; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    std::cout << "Network " << ++t << ": ";
    const auto path_len =
        uva_1056::Navigator(num_nodes, edge_list).GetMinimaxPathLen();
    if (path_len == uva_1056::infinity) {
      std::cout << "DISCONNECTED" << std::endl;
    } else {
      std::cout << path_len << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
