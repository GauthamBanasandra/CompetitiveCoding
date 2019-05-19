#include <vector>

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

	std::vector<std::vector<int>> GetLevelOrder() const;

private:
	static void Traverse(const TreeNode* node, std::size_t i_level,
		std::vector<std::vector<int>>& level_order);

	const TreeNode* root_;
};

std::vector<std::vector<int>> Tree::GetLevelOrder() const
{
	std::vector<std::vector<int>> level_order;
	if (root_ == nullptr)
	{
		return level_order;
	}

	Traverse(root_, 0, level_order);
	return level_order;
}

void Tree::Traverse(const TreeNode* node, const std::size_t i_level,
	std::vector<std::vector<int>>& level_order)
{
	if (level_order.size() < i_level + 1)
	{
		level_order.resize(i_level + 1);
	}

	level_order[i_level].emplace_back(node->val);
	if (node->left != nullptr)
	{
		Traverse(node->left, i_level + 1, level_order);
	}
	if (node->right != nullptr)
	{
		Traverse(node->right, i_level + 1, level_order);
	}
}

class Solution
{
public:
	static std::vector<std::vector<int>> levelOrder(
		TreeNode* root);
};

std::vector<std::vector<int>> Solution::levelOrder(
	TreeNode * root)
{
	return Tree(root).GetLevelOrder();
}

int main(int argc, char* argv[])
{
	return 0;
}
