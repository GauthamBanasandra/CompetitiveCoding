#include <cassert>
#include <ios>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>

namespace uva_536 {
struct Node {
  explicit Node(const char value) : value{value} {}

  char value{'\0'};
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
};

class Tree {
public:
  Tree(const std::string &preorder, const std::string &inorder);

  std::string PostOrder() const;

private:
  std::unique_ptr<Node> Build(size_t &i, int left, int right) const;
  static void PostOrder(const std::unique_ptr<Node> &node,
                        std::string &postorder);

  const std::string &preorder_;
  const std::string &inorder_;
  std::unordered_map<char, int> position_;
};

Tree::Tree(const std::string &preorder, const std::string &inorder)
    : preorder_{preorder}, inorder_{inorder} {
  assert(preorder_.size() == inorder_.size());
  assert(!preorder_.empty());

  auto pos{0};
  for (const auto &c : inorder_) {
    position_[c] = pos++;
  }
  assert(position_.size() == inorder_.size());
}

std::string Tree::PostOrder() const {
  size_t i{0};
  const auto root = Build(i, 0, static_cast<int>(preorder_.size()) - 1);

  std::string postorder;
  postorder.reserve(preorder_.size());
  PostOrder(root, postorder);
  return postorder;
}

std::unique_ptr<Node> Tree::Build(size_t &i, const int left,
                                  const int right) const {
  if (i >= preorder_.size() || right - left < 0) {
    return nullptr;
  }
  if (left == right) {
    return std::make_unique<Node>(inorder_[left]);
  }

  auto current_char = preorder_[i];
  auto node = std::make_unique<Node>(current_char);
  node->left = Build(++i, left, position_.at(current_char) - 1);
  i = node->left == nullptr ? i - 1 : i;

  node->right = Build(++i, position_.at(current_char) + 1, right);
  i = node->right == nullptr ? i - 1 : i;
  return node;
}

void Tree::PostOrder(const std::unique_ptr<Node> &node,
                     std::string &postorder) {
  if (node == nullptr) {
    return;
  }
  PostOrder(node->left, postorder);
  PostOrder(node->right, postorder);
  postorder.push_back(node->value);
}
} // namespace uva_536

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string preorder;
  std::string inorder;

  while (std::cin >> preorder >> inorder, !std::cin.eof()) {
    std::cout << uva_536::Tree(preorder, inorder).PostOrder() << std::endl;
  }
  return 0;
}
