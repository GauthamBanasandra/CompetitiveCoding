//
// Created by Gautham Banasandra on 19/09/18.
//

#include <vector>
#include <algorithm>
#include <iostream>

struct TreeNode {
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

  int val;
  TreeNode *left;
  TreeNode *right;
};

class Solution {
 public:
  TreeNode *constructMaximumBinaryTree(const std::vector<int> &nums) const;

 private:
  TreeNode *Construct(const std::vector<int> &nums, long i_left, long i_right) const;
};

TreeNode *Solution::constructMaximumBinaryTree(const std::vector<int> &nums) const {
  return Construct(nums, 0, static_cast<long>(nums.size()) - 1);
}

TreeNode *Solution::Construct(const std::vector<int> &nums, long i_left, long i_right) const {
  if (i_left > i_right) {
    return nullptr;
  }

  auto ui_left = static_cast<std::size_t>(i_left);
  auto ui_right = static_cast<std::size_t>(i_right);

  if (i_left == i_right) {
    return new TreeNode(nums[ui_left]);
  }

  auto max_it = std::max_element(nums.begin() + ui_left, nums.begin() + ui_right + 1);
  auto i_max = std::distance(nums.begin(), max_it);

  auto node = new TreeNode(*max_it);
  node->left = Construct(nums, i_left, i_max - 1);
  node->right = Construct(nums, i_max + 1, i_right);
  return node;
}

int main() {
  std::vector<int> nums{3, 2, 1, 6, 0, 5};

  auto tree = Solution().constructMaximumBinaryTree(nums);
  std::cout << tree->val << std::endl;
  return 0;
}