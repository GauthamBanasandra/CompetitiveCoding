#include <queue>
#include <iostream>

namespace week_135
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		TreeNode* bstToGst(TreeNode* root) {
			values_.push(0);
			SumNodes(root);
			ModifyNodes(root);
			return root;
		}

	private:
		void SumNodes(TreeNode* node);
		void ModifyNodes(TreeNode* node);

		std::queue<int> values_;
		int sum_{ 0 };
	};

	void Solution::SumNodes(TreeNode* node)
	{
		if (node->left != nullptr)
		{
			SumNodes(node->left);
		}
		sum_ += node->val;
		values_.push(node->val);
		if (node->right != nullptr)
		{
			SumNodes(node->right);
		}
	}

	void Solution::ModifyNodes(TreeNode* node)
	{
		if (node->left != nullptr)
		{
			ModifyNodes(node->left);
		}
		const auto value = values_.front();
		node->val = sum_ - value;
		sum_ -= value;
		values_.pop();
		if (node->right != nullptr)
		{
			ModifyNodes(node->right);
		}
	}
}

int main(int argc, char* argv[])
{
	return 0;
}
