#include <algorithm>
#include <iostream>

namespace lc_543 {
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

using namespace std;

class Solution {
public:
  int diameterOfBinaryTree(TreeNode *root);

private:
  int height(TreeNode *node);

  bool is_height_init_{false};
};

int Solution::height(TreeNode *node) {
  if (node == nullptr) {
    return 0;
  }
  if (node->left == nullptr && node->right == nullptr) {
    return node->val = 0;
  }

  node->val = max(height(node->left), height(node->right)) + 1;
  return node->val;
}

int Solution::diameterOfBinaryTree(TreeNode *node) {
  if (node == nullptr) {
    return 0;
  }

  if (!is_height_init_) {
    is_height_init_ = true;
    height(node);
  }

  auto diameter = node->left == nullptr ? 0 : node->left->val + 1;
  diameter += node->right == nullptr ? 0 : node->right->val + 1;

  return max(diameter, max(diameterOfBinaryTree(node->left),
                           diameterOfBinaryTree(node->right)));
}
} // namespace lc_543

int main(int argc, char *argv[]) {
  using namespace lc_543;

  auto root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);

  cout << Solution().diameterOfBinaryTree(root) << endl;
  return 0;
}
