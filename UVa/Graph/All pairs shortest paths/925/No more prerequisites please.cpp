#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_925 {
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
  Node index = 0;
  for (const auto &node : nodes) {
    assert(node_idx_.find(node) == node_idx_.end());
    node_idx_[node] = index++;
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
    const auto len = prerequisites.size();
    std::sort(prerequisites.begin(), prerequisites.end());

    std::vector<int> is_eliminated(len);
    for (size_t i = 0; i < len; ++i) {
      if (is_eliminated[i] == 1) {
        continue;
      }
      for (size_t j = 0; j < len; ++j) {
        if (is_eliminated[j] == 0 && adj_matrix_[node_idx_[prerequisites[j]]]
                                                [node_idx_[prerequisites[i]]] ==
                                         1) {
          is_eliminated[j] = 1;
        }
      }
    }
    for (size_t i = 0; i < len; ++i) {
      if (is_eliminated[i] == 0) {
        prerequisites.emplace_back(prerequisites[i]);
      }
    }
    prerequisites.erase(prerequisites.begin(), prerequisites.begin() + len);
  }

  std::sort(
      prerequisites_list_.begin(), prerequisites_list_.end(),
      [](const std::pair<std::string, std::vector<std::string>> &a,
         const std::pair<std::string, std::vector<std::string>> &b) -> bool {
        return a.first < b.first;
      });
}
} // namespace uva_925

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t, num_nodes, prerequisites_list_len, num_prerequisites;
  std::vector<std::string> nodes;
  std::vector<std::pair<std::string, std::vector<std::string>>>
      prerequisites_list;

  std::cin >> t;
  while (t--) {
    std::cin >> num_nodes;
    nodes.resize(num_nodes);
    for (size_t i = 0; i < num_nodes; ++i) {
      std::cin >> nodes[i];
    }
    std::cin >> prerequisites_list_len;
    prerequisites_list.resize(prerequisites_list_len);
    for (size_t i = 0; i < prerequisites_list_len; ++i) {
      std::cin >> prerequisites_list[i].first;
      std::cin >> num_prerequisites;
      prerequisites_list[i].second.resize(num_prerequisites);
      for (size_t j = 0; j < num_prerequisites; ++j) {
        std::cin >> prerequisites_list[i].second[j];
      }
    }

    uva_925::Navigator(num_nodes, nodes, prerequisites_list)
        .LinkTransitiveClosures();

    for (const auto &[node, prerequisites] : prerequisites_list) {
      std::cout << node << " " << prerequisites.size();
      for (const auto &prerequisite : prerequisites) {
        std::cout << " " << prerequisite;
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
