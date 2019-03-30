// WA

#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cassert>

struct Node
{
	Node() = default;
	Node(const long component, const long rank) :
		is_visited(true), component(component), rank(rank) {}

	bool is_visited{ false };
	long component{ 0 };
	long rank{ 0 };
};

class Traversal
{
public:
	explicit Traversal(long num_nodes);

	long GetMaxForwardIndex() const;

private:
	long BFS(long i_start, const long i_component, std::vector<Node>&
		visited, std::unordered_map<long, long>& component_size) const;

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
	auto num_components = 1l;
	std::vector<Node> visited(num_nodes_ + 1);
	std::unordered_map<long, long> component_size;

	for (auto i = 1l; i <= num_nodes_; ++i)
	{
		if (visited[i].is_visited)
		{
			continue;
		}

		const auto num_visited = BFS(i, num_components, visited, component_size);
		if (num_visited > max_num_visited)
		{
			max_num_visited = num_visited;
			i_max = i;
		}
		component_size[num_components] = num_visited;
		++num_components;
	}
	return i_max;
}

long Traversal::BFS(const long i_start, const long i_component,
	std::vector<Node>& visited, std::unordered_map<long, long>& component_size) const
{
	auto rank = 1l;
	std::queue<long> order;
	std::vector<long> component{ i_start };
	std::vector<long> revisited;
	visited[i_start] = { i_component, rank };
	order.push(i_start);

	while (!order.empty())
	{
		const auto node = order.front();
		order.pop();

		auto find_it = adj_list_.find(node);
		assert(find_it != adj_list_.end());

		for (const auto adj_node : find_it->second)
		{
			if (visited[adj_node].is_visited)
			{
				revisited.emplace_back(adj_node);
				continue;
			}

			++rank;
			visited[adj_node] = { i_component, rank };
			order.push(adj_node);
			component.emplace_back(adj_node);
		}
	}

	auto num_visited = rank;
	for (const auto &node : revisited)
	{
		if (visited[node].component != i_component)
		{
			num_visited += component_size[visited[node].component] - visited[node].rank + 1;
		}
		else
		{
			auto it = std::find(component.begin(), component.end(), node);
			assert(it != component.end());
			for (const auto cycle_rank = *it; it != component.end(); ++it)
			{
				visited[*it].rank = cycle_rank;
			}
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
