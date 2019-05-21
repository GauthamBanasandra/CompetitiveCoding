#include <vector>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};


class BinarySearchTree
{
public:
	explicit BinarySearchTree(const std::vector<int>& numbers) :numbers_(numbers) {}

	TreeNode* Build() const;

private:
	void Build(int i, int j, TreeNode*& root) const;

	const std::vector<int>& numbers_;
};

TreeNode* BinarySearchTree::Build() const
{
	TreeNode* root = nullptr;
	Build(0, static_cast<int>(numbers_.size()) - 1, root);
	return root;
}

void BinarySearchTree::Build(const int i, const int j, TreeNode*& root) const
{
	if (i > j)
	{
		return;
	}

	const auto index = (j - i) / 2 + i;
	root = new TreeNode(numbers_[index]);
	Build(i, index - 1, root->left);
	Build(index + 1, j, root->right);
}

class Solution {
public:
	static TreeNode* sortedArrayToBST(
		std::vector<int>& nums);
};

TreeNode* Solution::sortedArrayToBST(std::vector<int> & nums)
{
	return BinarySearchTree(nums).Build();
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ -10,-3,0,5,9 };
	Solution::sortedArrayToBST(numbers);
	return 0;
}
