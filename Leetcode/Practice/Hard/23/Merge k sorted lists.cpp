#include <vector>
#include <queue>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* Merge(const std::vector<ListNode*>& lists)
{
	// Min priority queue
	// Note that I don't have to override operator< for std::pair
	// because std::priority_queue works natively with std::pair
	// It uses the first element of the std::pair as the key to sort
	// However, std::priority_queue is a max heap by default and
	// since we need a min heap, we need to mention the container i.e. std::vector
	// and also provide the operator we want to use i.e. std::greater
	// Note that I don't have to override anything with std::pair
	std::priority_queue<std::pair<int, ListNode*>,
		std::vector<std::pair<int, ListNode*>>, std::greater<>> order;
	ListNode* head = nullptr;
	ListNode* tail = nullptr;

	const auto push_back = [&head, &tail](ListNode * node)->void
	{
		if (head == nullptr && tail == nullptr)
		{
			head = tail = node;
			tail->next = nullptr;
			return;
		}

		tail->next = node;
		tail = node;
		tail->next = nullptr;
	};

	for (const auto& list : lists)
	{
		if (list != nullptr)
		{
			order.emplace(list->val, list);
		}
	}

	while (!order.empty())
	{
		const auto top = order.top();
		order.pop();
		auto next = top.second->next;
		push_back(top.second);
		if (next != nullptr)
		{
			order.emplace(next->val, next);
		}
	}
	return head;
}

class Solution
{
public:
	static ListNode* mergeKLists(std::vector<ListNode*>& lists);
};

ListNode* Solution::mergeKLists(std::vector<ListNode*>& lists)
{
	return Merge(lists);
}

int main(int argc, char* argv[])
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
	pq.emplace(1, 10);
	pq.emplace(2, 20);
	pq.emplace(3, 30);
	return 0;
}
