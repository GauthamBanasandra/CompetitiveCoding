#include <algorithm>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int Next(const TreeNode* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	const auto left = Next(node->left);
	const auto right = Next(node->right);
	return std::max(left, right) + 1;
}

class Solution
{
public:
	static int maxDepth(TreeNode* root);
};

int Solution::maxDepth(TreeNode* root)
{
	return Next(root);
}

int main(int argc, char* argv[])
{
	return 0;
}
