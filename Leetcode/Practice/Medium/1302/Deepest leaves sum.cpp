#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  int deepestLeavesSum(TreeNode *root);

private:
  static void Next(TreeNode *node, size_t depth, std::vector<int> &depth_sum);
};

int Solution::deepestLeavesSum(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  std::vector<int> depth_sum;
  Next(root, 0, depth_sum);
  return depth_sum.back();
}

void Solution::Next(TreeNode *node, const size_t depth,
                    std::vector<int> &depth_sum) {
  if (node == nullptr) {
    return;
  }

  if (depth_sum.size() <= depth) {
    depth_sum.emplace_back(0);
  }
  depth_sum[depth] += node->val;
  Next(node->left, depth + 1, depth_sum);
  Next(node->right, depth + 1, depth_sum);
}

int main(int argc, char *argv[]) { return 0; }
