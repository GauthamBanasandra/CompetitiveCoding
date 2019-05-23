#include <algorithm>
#include <limits>

const auto neg_infinity = std::numeric_limits<int>::min();

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
public:
	explicit BinaryTree(TreeNode* root) : root_(root) {}

	int MaxSumPath() const;

private:
	std::pair<int, int> Next(const TreeNode* node) const;

	const TreeNode* root_;
};

int BinaryTree::MaxSumPath() const
{
	const auto sum = Next(root_);
	return std::max(sum.first, sum.second);
}

// The first item of std::pair shouldn't be combined
// The second item of std::pair could be combined
std::pair<int, int> BinaryTree::Next(const TreeNode* node) const
{
	if (node->left == nullptr && node->right == nullptr)
	{
		return{ neg_infinity, node->val };
	}

	if (node->left != nullptr && node->right == nullptr)
	{
		const auto left = Next(node->left);
		const auto max_independent = std::max(left.first, left.second);
		const auto max_combination = std::max(left.second + node->val, node->val);
		return{ max_independent, max_combination };
	}

	if (node->left == nullptr && node->right != nullptr)
	{
		const auto right = Next(node->right);
		const auto max_independent = std::max(right.first, right.second);
		const auto max_combination = std::max(right.second + node->val, node->val);
		return{ max_independent, max_combination };
	}

	const auto left = Next(node->left);
	const auto right = Next(node->right);

	// Max independent is max(left, right, left + current + right)
	auto max_independent = std::max(left.first, left.second);
	max_independent = std::max(max_independent, right.first);
	max_independent = std::max(max_independent, right.second);
	max_independent = std::max(max_independent, left.second + right.second + node->val);

	// Max combination is max(left + current, right + current, current)
	auto max_combination = std::max(left.second + node->val, right.second + node->val);
	max_combination = std::max(max_combination, node->val);
	return{ max_independent, max_combination };
}

class Solution
{
public:
	static int maxPathSum(TreeNode* root);
};

int Solution::maxPathSum(TreeNode* root)
{
	return BinaryTree(root).MaxSumPath();
}

int main(int argc, char* argv[])
{
	return 0;
}
