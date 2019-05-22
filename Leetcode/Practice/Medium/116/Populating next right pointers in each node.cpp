class Node
{
public:
	int val{};
	Node* left{};
	Node* right{};
	Node* next{};

	Node() = default;

	Node(int _val, Node* _left, Node* _right,
		Node* _next);
};

Node::Node(const int _val, Node* _left, Node* _right,
	Node* _next)
{
	val = _val;
	left = _left;
	right = _right;
	next = _next;
}

class BinaryTree
{
public:
	explicit BinaryTree(Node* root) :root_(root) {}

	Node* Link() const;

private:
	static void Link(Node* node);

	Node* root_;
};

Node* BinaryTree::Link() const
{
	Link(root_);
	return root_;
}

void BinaryTree::Link(Node* node)
{
	if (node == nullptr || node->left == nullptr && node->right == nullptr)
	{
		return;
	}

	node->left->next = node->right;
	if (node->next != nullptr)
	{
		node->right->next = node->next->left;
	}
	Link(node->left);
	Link(node->right);
}

class Solution
{
public:
	static Node* connect(Node* root);
};

Node* Solution::connect(Node* root)
{
	return BinaryTree(root).Link();
}

int main(int argc, char* argv[])
{
	return 0;
}
