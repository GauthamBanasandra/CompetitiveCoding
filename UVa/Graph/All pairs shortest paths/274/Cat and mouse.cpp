#include <algorithm>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

namespace uva_274 {
using Node = size_t;
using AdjacencyMatrix = std::vector<std::vector<int>>;
using EdgeList = std::vector<std::pair<Node, Node>>;

class Navigator {
public:
  Navigator(size_t num_nodes, Node cat_src, Node mouse_src,
            const EdgeList &cat_edge_list, const EdgeList &mouse_edge_list);

  std::pair<bool, bool> GetResult();

private:
  void InitializeAdjacencyMatrix(AdjacencyMatrix &adj_matrix,
                                 const EdgeList &edge_list) const;
  void ConnectTransitiveRoutes(AdjacencyMatrix &adj_matrix) const;
  std::unordered_set<Node> GetReachableNodes(const AdjacencyMatrix &adj_matrix,
                                             const Node source) const;
  static bool IsPossibleToMeet(const std::unordered_set<Node> &cat_reachable,
                               const std::unordered_set<Node> &mouse_reachable);
  bool IsMouseCyclePossible(const std::unordered_set<Node> &cat_reachable);

  const size_t num_nodes_;
  const Node cat_src_;
  const Node mouse_src_;
  AdjacencyMatrix cat_adj_matrix_;
  AdjacencyMatrix mouse_adj_matrix_;
};

Navigator::Navigator(const size_t num_nodes, const Node cat_src,
                     const Node mouse_src, const EdgeList &cat_edge_list,
                     const EdgeList &mouse_edge_list)
    : num_nodes_(num_nodes + 1), cat_src_(cat_src), mouse_src_(mouse_src) {
  InitializeAdjacencyMatrix(cat_adj_matrix_, cat_edge_list);
  InitializeAdjacencyMatrix(mouse_adj_matrix_, mouse_edge_list);
}

std::pair<bool, bool> Navigator::GetResult() {
  ConnectTransitiveRoutes(cat_adj_matrix_);
  auto mouse_transitive_paths = mouse_adj_matrix_;
  ConnectTransitiveRoutes(mouse_transitive_paths);

  const auto cat_reachable = GetReachableNodes(cat_adj_matrix_, cat_src_);
  const auto mouse_reachable =
      GetReachableNodes(mouse_transitive_paths, mouse_src_);
  return {IsPossibleToMeet(cat_reachable, mouse_reachable),
          IsMouseCyclePossible(cat_reachable)};
}

void Navigator::InitializeAdjacencyMatrix(AdjacencyMatrix &adj_matrix,
                                          const EdgeList &edge_list) const {
  adj_matrix.resize(num_nodes_, std::vector<int>(num_nodes_));
  for (const auto &[u, v] : edge_list) {
    adj_matrix[u][v] = 1;
  }
}

void Navigator::ConnectTransitiveRoutes(AdjacencyMatrix &adj_matrix) const {
  for (Node k = 1; k < num_nodes_; ++k) {
    for (Node i = 1; i < num_nodes_; ++i) {
      for (Node j = 1; j < num_nodes_; ++j) {
        adj_matrix[i][j] |= adj_matrix[i][k] & adj_matrix[k][j];
      }
    }
  }
}

std::unordered_set<Node>
Navigator::GetReachableNodes(const AdjacencyMatrix &adj_matrix,
                             const Node source) const {
  std::unordered_set<Node> reachable;
  for (Node i = 1; i < num_nodes_; ++i) {
    if (adj_matrix[source][i] == 1) {
      reachable.insert(i);
    }
  }
  reachable.insert(source);
  return reachable;
}

bool Navigator::IsPossibleToMeet(
    const std::unordered_set<Node> &cat_reachable,
    const std::unordered_set<Node> &mouse_reachable) {
  for (const auto node : mouse_reachable) {
    if (cat_reachable.find(node) != cat_reachable.end()) {
      return true;
    }
  }
  return false;
}

bool Navigator::IsMouseCyclePossible(
    const std::unordered_set<Node> &cat_reachable) {
  // What we want to do here is to find the longest cycle starting and ending at
  // mouse's home node, while avoiding those nodes that are reachable by the
  // cat. Then we check if such a cycle exists and its length is at least 2
  // We do this by setting mouse's home node to a low value and run Floyd
  // Warshall
  // We don't need to tweak Floyd Warshall to achieve this. By the
  // nature of Floyd Warshall algorithm, it will optimize every path and
  // therefore it will try to find the longest possible path (cycle) to go from
  // mouse_src to mouse_src
  mouse_adj_matrix_[mouse_src_][mouse_src_] = 0;
  for (Node k = 1; k < num_nodes_; ++k) {
    for (Node i = 1; i < num_nodes_; ++i) {
      for (Node j = 1; j < num_nodes_; ++j) {
        // We need to check if either the intermediate vertex k or the
        // destination vertex j are reachable by cat and avoid going there.
        if (cat_reachable.find(j) != cat_reachable.end() ||
            cat_reachable.find(k) != cat_reachable.end() ||
            // Also, we need to avoid if the intermediate vertex k is the same
            // as mouse's home node
            k == mouse_src_ ||
            // And also avoid paths were either i->k or k->j is missing
            mouse_adj_matrix_[i][k] == 0 || mouse_adj_matrix_[k][j] == 0) {
          continue;
        }
        mouse_adj_matrix_[i][j] =
            std::max(mouse_adj_matrix_[i][j],
                     mouse_adj_matrix_[i][k] + mouse_adj_matrix_[k][j]);
      }
    }
  }
  return mouse_adj_matrix_[mouse_src_][mouse_src_] >= 2;
}
} // namespace uva_274

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  int u, v;
  size_t t, num_nodes;
  uva_274::Node cat_src, mouse_src;
  std::string line;

  std::getline(std::cin, line);
  std::istringstream t_tokenizer(line);
  t_tokenizer >> t;
  std::getline(std::cin, line);

  for (size_t i = 0; i < t; ++i) {
    std::getline(std::cin, line);
    std::istringstream ncm_tokenizer(line);
    ncm_tokenizer >> num_nodes >> cat_src >> mouse_src;

    uva_274::EdgeList cat_edge_list, mouse_edge_list;
    auto cat = true;
    while (std::getline(std::cin, line), !line.empty()) {
      std::istringstream uv_tokenizer(line);
      uv_tokenizer >> u >> v;
      if (cat) {
        if (u == -1 && v == -1) {
          cat = false;
          continue;
        }
        cat_edge_list.emplace_back(u, v);
      } else {
        mouse_edge_list.emplace_back(u, v);
      }
    }

    auto result = uva_274::Navigator(num_nodes, cat_src, mouse_src,
                                     cat_edge_list, mouse_edge_list)
                      .GetResult();
    if (i > 0) {
      std::cout << std::endl;
    }
    std::cout << (result.first ? 'Y' : 'N') << " "
              << (result.second ? 'Y' : 'N') << std::endl;
  }
  return 0;
}
