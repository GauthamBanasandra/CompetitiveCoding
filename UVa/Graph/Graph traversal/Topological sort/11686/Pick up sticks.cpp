#include <vector>
#include <queue>
#include <iostream>

namespace uva11686
{
	class TopologicalSort
	{
	public:
		TopologicalSort(int num_nodes, const std::vector<std::pair<int, int>>& edge_list);

		std::pair<bool, std::vector<int>> GetOrder();

	private:
		const int num_nodes_;
		std::vector<int> in_degree_;
		std::vector<std::vector<int>> adj_list_;
	};

	TopologicalSort::TopologicalSort(const int num_nodes,
		const std::vector<std::pair<int, int>>& edge_list) :num_nodes_(num_nodes)
	{
		adj_list_.resize(num_nodes_ + 1);
		in_degree_.resize(num_nodes_ + 1);
		for (const auto& edge : edge_list)
		{
			adj_list_[edge.first].emplace_back(edge.second);
			++in_degree_[edge.second];
		}
	}

	std::pair<bool, std::vector<int>> TopologicalSort::GetOrder()
	{
		// Using Kahn's algorithm
		std::queue<int> order;
		for (auto i = 1; i <= num_nodes_; ++i)
		{
			if (in_degree_[i] == 0)
			{
				order.push(i);
			}
		}

		std::vector<int> sticks;
		sticks.reserve(num_nodes_);

		while (!order.empty())
		{
			const auto node = order.front();
			order.pop();
			sticks.emplace_back(node);
			for (const auto adj_node : adj_list_[node])
			{
				--in_degree_[adj_node];
				if (in_degree_[adj_node] == 0)
				{
					order.push(adj_node);
				}
			}
		}

		// The idea behind detecting a cycle is, the nodes will enter the queue only
		// when its in-degree becomes 0
		// So, if there's a cycle, no matter in whichever order we remove, the
		// in-degree of the nodes in the cycle will never become 0 and thereby,
		// it never enters the queue
		// This implies that all the nodes in the graph won't be visited, which forms
		// the check for cycle
		return std::make_pair(num_nodes_ == static_cast<int>(sticks.size()), sticks);
	}
}

int main(int argc, char* argv[])
{
	int n;
	int m;
	std::vector<std::pair<int, int>> edge_list;

	while (std::cin >> n >> m, n || m)
	{
		edge_list.resize(m);
		for (auto i = 0; i < m; ++i)
		{
			std::cin >> edge_list[i].first >> edge_list[i].second;
		}

		uva11686::TopologicalSort sorter(n, edge_list);
		const auto& [is_cycle, order] = sorter.GetOrder();
		if (!is_cycle)
		{
			std::cout << "IMPOSSIBLE" << std::endl;
		}
		else
		{
			for (const auto element : order)
			{
				std::cout << element << std::endl;
			}
		}
	}
	return 0;
}
