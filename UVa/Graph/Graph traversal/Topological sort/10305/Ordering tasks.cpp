#include <vector>
#include <algorithm>
#include <iostream>

namespace uva10305
{
	class TopoSort
	{
	public:
		explicit TopoSort(const std::vector<std::pair<int, int>>& edge_list, int num_nodes);

		std::vector<int> Sort();

	private:
		void DFS(int node, std::vector<int>& order);

		const int num_nodes_;
		std::vector<short> visited_;
		std::vector<std::vector<int>> adj_list_;
	};

	TopoSort::TopoSort(const std::vector<std::pair<int, int>>& edge_list, const int num_nodes)
		:num_nodes_(num_nodes)
	{
		adj_list_.resize(num_nodes_ + 1);
		visited_.resize(num_nodes_ + 1);
		for (const auto& edge : edge_list)
		{
			adj_list_[edge.first].emplace_back(edge.second);
		}
	}

	std::vector<int> TopoSort::Sort()
	{
		std::vector<int> order;
		for (auto i = 1; i <= num_nodes_; ++i)
		{
			if (visited_[i] == 0)
			{
				DFS(i, order);
			}
		}
		std::reverse(order.begin(), order.end());
		return order;
	}

	void TopoSort::DFS(int node, std::vector<int>& order)
	{
		visited_[node] = 1;
		for (const auto adj_node : adj_list_[node])
		{
			if (visited_[adj_node] == 0)
			{
				DFS(adj_node, order);
			}
		}
		order.emplace_back(node);
	}
}

int main(int argc, char* argv[])
{
	int n, m;
	std::vector<std::pair<int, int>> edge_list;

	while (std::cin >> n >> m, n || m)
	{
		edge_list.resize(m);
		for (auto i = 0; i < m; ++i)
		{
			std::cin >> edge_list[i].first >> edge_list[i].second;
		}

		uva10305::TopoSort sorter(edge_list, n);
		auto separator = "";
		for (const auto value : sorter.Sort())
		{
			std::cout << separator << value;
			separator = " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
