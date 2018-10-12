#include <iostream>

struct ListNode
{
	ListNode(const int x) : val(x), next(nullptr) {}

	int val;
	ListNode *next;
};

class Solution
{
public:
	static ListNode* swapPairs(ListNode* head);
	static void Print(const ListNode* head);

private:
	static ListNode* SwapPairs(ListNode* head);
};

ListNode* Solution::swapPairs(ListNode* head)
{
	return SwapPairs(head);
}

void Solution::Print(const ListNode* head)
{
	for (auto p = head; p != nullptr; p = p->next)
	{
		std::cout << p->val << " ";
	}
	std::cout << std::endl;
}

ListNode* Solution::SwapPairs(ListNode* head)
{
	for (auto p = head, previous = head; p != nullptr; p = p->next)
	{
		const auto t = p->next;
		if (t == nullptr)
		{
			return head;
		}

		p->next = t->next;
		t->next = p;
		if (p == head)
		{
			head = t;
		}
		else
		{
			previous->next = t;
		}
		previous = p;
	}
	return head;
}

int main(int argc, char* argv[])
{
	const auto a = new ListNode(1),
		b = new ListNode(2),
		c = new ListNode(3),
		d = new ListNode(4),
		e = new ListNode(5),
		f = new ListNode(6);

	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = f;

	std::cout << "Before swapping:" << std::endl;
	Solution::Print(a);

	std::cout << "After swapping:" << std::endl;
	Solution::Print(Solution::swapPairs(a));
	return 0;
}