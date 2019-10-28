#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

namespace round_87 {
using Node = size_t;

class Graph {
public:
  explicit Graph(const std::vector<int> &parent);

  [[nodiscard]] int Height() const { return Height(source_) - 1; }

private:
  [[nodiscard]] int Height(Node node) const;

  const size_t num_nodes_;
  const Node source_;
  std::vector<std::vector<size_t>> adj_list_;
};

Graph::Graph(const std::vector<int> &parent)
    : num_nodes_(parent.size() + 1), source_(parent.size()) {
  adj_list_.resize(num_nodes_);
  for (Node i = 0, len = parent.size(); i < len; ++i) {
    adj_list_[parent[i] == -1 ? source_ : static_cast<Node>(parent[i]) - 1]
        .emplace_back(i);
  }
}

int Graph::Height(const Node node) const {
  auto max_height = 0;
  for (const auto &adj_node : adj_list_[node]) {
    max_height = std::max(max_height, Height(adj_node));
  }
  return max_height + 1;
}
} // namespace round_87

int main(int argc, char *argv[]) {
  size_t num_nodes;
  std::cin >> num_nodes;

  std::vector<int> parent(num_nodes);
  for (size_t i = 0; i < num_nodes; ++i) {
    std::cin >> parent[i];
  }

  std::cout << round_87::Graph(parent).Height() << std::endl;
  return 0;
}
