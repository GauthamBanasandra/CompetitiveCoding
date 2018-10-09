#include <unordered_map>
#include <iostream>
#include <cassert>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(const int x) : val(x), next(nullptr) {}
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) const;
	static void Print(ListNode* head);

private:
	ListNode* RemoveNthFromEnd(ListNode* head, int n) const;
};

ListNode* Solution::removeNthFromEnd(ListNode* head, const int n) const
{
	return RemoveNthFromEnd(head, n);
}

ListNode* Solution::RemoveNthFromEnd(ListNode* head, const int n) const
{
	std::unordered_map<int, ListNode*> index;

	auto i = 0;
	for (auto p = head; p != nullptr; p = p->next)
	{
		index[++i] = p;
	}

	const auto size = static_cast<int>(index.size());
	assert(size >= n);
	const auto i_previous = size - n;

	ListNode* to_del = nullptr;
	if (i_previous == 0)
	{
		to_del = head;
		head = head->next;
	}
	else
	{
		const auto previous = index[i_previous];
		to_del = previous->next;
		previous->next = to_del->next;
	}

	delete to_del;
	return head;
}

void Solution::Print(ListNode* head)
{
	for (auto p = head; p != nullptr; p = p->next)
	{
		std::cout << p->val << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	const auto a = new ListNode(1),
		b = new ListNode(2),
		c = new ListNode(3),
		d = new ListNode(4),
		e = new ListNode(5);

	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;

	std::cout << "Before deleting:" << std::endl;
	Solution::Print(a);

	std::cout << "After deleting:" << std::endl;
	Solution::Print(Solution().removeNthFromEnd(a, 15));
	return 0;
}
