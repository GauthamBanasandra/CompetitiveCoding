#include <vector>
#include <algorithm>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

class Tree
{
public:
	explicit Tree(TreeNode* root) :root_(root) {}

	std::vector<std::vector<int>> GetZigZagLevelOrder() const;

private:
	static void Traverse(const TreeNode* node, std::size_t i_level,
		std::vector<std::vector<int>>& level_order);

	const TreeNode* root_;
};

std::vector<std::vector<int>> Tree::GetZigZagLevelOrder() const
{
	std::vector<std::vector<int>> level_order;
	Traverse(root_, 0, level_order);
	for (std::size_t i = 0, len = level_order.size(); i < len; ++i)
	{
		if ((i & 1) == 1)
		{
			std::reverse(level_order[i].begin(), level_order[i].end());
		}
	}
	return level_order;
}

void Tree::Traverse(const TreeNode* node, const std::size_t i_level,
	std::vector<std::vector<int>>& level_order)
{
	if (node == nullptr)
	{
		return;
	}

	if (level_order.size() < i_level + 1)
	{
		level_order.resize(i_level + 1);
	}

	level_order[i_level].emplace_back(node->val);
	Traverse(node->left, i_level + 1, level_order);
	Traverse(node->right, i_level + 1, level_order);
}

class Solution
{
public:
	static std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root);
};

std::vector<std::vector<int>> Solution::zigzagLevelOrder(TreeNode * root)
{
	return Tree(root).GetZigZagLevelOrder();
}

int main(int argc, char* argv[])
{
	return 0;
}
