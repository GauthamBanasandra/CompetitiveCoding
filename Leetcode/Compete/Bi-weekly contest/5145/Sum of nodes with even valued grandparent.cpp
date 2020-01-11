struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int sumEvenGrandparent(TreeNode *root);

private:
  static int GetSum(TreeNode *node, bool is_parent_even);
};

int Solution::sumEvenGrandparent(TreeNode *root) { return GetSum(root, false); }

int Solution::GetSum(TreeNode *node, const bool is_parent_even) {
  if (node == nullptr) {
    return 0;
  }

  auto sum = 0;
  if (is_parent_even) {
    sum += node->left != nullptr ? node->left->val : 0;
    sum += node->right != nullptr ? node->right->val : 0;
  }

  const auto am_i_even = node->val % 2 == 0;
  sum += GetSum(node->left, am_i_even);
  sum += GetSum(node->right, am_i_even);
  return sum;
}

int main(int argc, char *argv[]) { return 0; }
