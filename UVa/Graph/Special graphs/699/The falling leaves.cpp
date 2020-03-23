#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>

namespace uva_699 {
struct Node {
  Node(const int value) : value{value} {}

  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
  int value;
};

class Tree {
public:
  Tree() : root_{Build()} {}

  std::map<int, int> Count() const;

private:
  std::unique_ptr<Node> Build() const;
  void Count(const std::unique_ptr<Node> &node, int heap_index,
             std::map<int, int> &counts) const;

  std::unique_ptr<Node> root_;
};

std::map<int, int> Tree::Count() const {
  std::map<int, int> counts;
  Count(root_, 0, counts);
  return counts;
}

std::unique_ptr<Node> Tree::Build() const {
  auto node_value{0};
  std::cin >> node_value;
  if (node_value == -1 || std::cin.eof()) {
    return nullptr;
  }

  auto node = std::make_unique<Node>(node_value);
  node->left = Build();
  node->right = Build();
  return node;
}

void Tree::Count(const std::unique_ptr<Node> &node, const int heap_index,
                 std::map<int, int> &counts) const {
  if (node == nullptr) {
    return;
  }

  counts[heap_index] += node->value;
  Count(node->left, heap_index - 1, counts);
  Count(node->right, heap_index + 1, counts);
}
} // namespace uva_699

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t = 0;
  while (!std::cin.eof()) {
    auto heap_counts = uva_699::Tree().Count();
    if (!heap_counts.empty()) {
      std::cout << "Case " << ++t << ":" << std::endl;
      auto separator = "";
      for (const auto &[_, count] : heap_counts) {
        std::cout << separator << count;
        separator = " ";
      }
      std::cout << std::endl << std::endl;
    }
  }
  return 0;
}
