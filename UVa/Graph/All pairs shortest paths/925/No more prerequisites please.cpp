// WIP

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using Node = size_t;
using AdjacencyMatrix = std::vector<std::vector<int>>;

class Navigator {
public:
  Navigator(size_t num_nodes, const std::vector<std::string> &nodes,
            std::vector<std::pair<std::string, std::vector<std::string>>>
                &prerequisites_list);

  void LinkTransitiveClosures();

private:
  const size_t num_nodes_;
  std::unordered_map<std::string, Node> node_idx_;
  std::vector<std::pair<std::string, std::vector<std::string>>>
      &prerequisites_list_;
  AdjacencyMatrix adj_matrix_;
};

Navigator::Navigator(
    const size_t num_nodes, const std::vector<std::string> &nodes,
    std::vector<std::pair<std::string, std::vector<std::string>>>
        &prerequisites_list)
    : num_nodes_{num_nodes}, prerequisites_list_{prerequisites_list} {
  for (const auto &node : nodes) {
    assert(node_idx_.find(node) == node_idx_.end());
    ++node_idx_[node];
  }

  adj_matrix_.resize(num_nodes, std::vector<int>(num_nodes));
  for (const auto &[v, u_nodes] : prerequisites_list_) {
    for (const auto &u : u_nodes) {
      adj_matrix_[node_idx_[u]][node_idx_[v]] = 1;
    }
  }
}

void Navigator::LinkTransitiveClosures() {
  for (Node k = 0; k < num_nodes_; ++k) {
    for (Node i = 0; i < num_nodes_; ++i) {
      for (Node j = 0; j < num_nodes_; ++j) {
        adj_matrix_[i][j] |= adj_matrix_[i][k] & adj_matrix_[k][j];
      }
    }
  }

  for (auto &[node, prerequisites] : prerequisites_list_) {
    auto len = prerequisites.size();
    std::vector<int> is_eliminated(len);
    for (size_t i = 0; i < len; ++i) {
      for (size_t j = 0; j < len; ++j) {
      }
    }
  }
}

int main(int argc, char *argv[]) { return 0; }
