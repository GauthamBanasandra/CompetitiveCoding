#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cassert>

class Traversal
{
public:
	explicit Traversal(long num_nodes);

	long GetMaxForwardIndex() const;

private:
	long BFS(long i_start, std::vector<short>& overall_visited) const;

	const long num_nodes_;
	std::unordered_map<long, std::vector<long>> adj_list_;
};

Traversal::Traversal(const long num_nodes) :num_nodes_(num_nodes)
{
	long node;
	long adj_node;
	for (auto i = 0l; i < num_nodes_; ++i)
	{
		std::cin >> node >> adj_node;
		adj_list_[node].emplace_back(adj_node);
	}
}

long Traversal::GetMaxForwardIndex() const
{
	auto max_num_visited = 0l;
	auto i_max = 0l;
	std::vector<short> visited(num_nodes_ + 1);

	for (auto i = 1l; i <= num_nodes_; ++i)
	{
		if (visited[i] == 1)
		{
			continue;
		}

		const auto num_visited = BFS(i, visited);
		if (num_visited > max_num_visited)
		{
			max_num_visited = num_visited;
			i_max = i;
		}
	}
	return i_max;
}

long Traversal::BFS(const long i_start, std::vector<short>& overall_visited) const
{
	auto num_visited = 1l;
	std::unordered_set<long> visited{ i_start };
	std::queue<long> order;

	overall_visited[i_start] = 1;
	order.push(i_start);

	while (!order.empty())
	{
		const auto node = order.front();
		order.pop();

		auto find_it = adj_list_.find(node);
		assert(find_it != adj_list_.end());

		for (const auto adj_node : find_it->second)
		{
			if (visited.find(adj_node) != visited.end())
			{
				continue;
			}

			visited.insert(adj_node);
			overall_visited[adj_node] = 1;
			++num_visited;
			order.push(adj_node);
		}
	}
	return num_visited;
}

int main(int argc, char* argv[])
{
	int t;
	long num_nodes;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> num_nodes;
		Traversal traversal(num_nodes);
		std::cout << "Case " << i << ": " << traversal.GetMaxForwardIndex() << std::endl;
	}
	return 0;
}
