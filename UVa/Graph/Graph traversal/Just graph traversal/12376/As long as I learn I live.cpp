#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <ios>

namespace uva12376
{
	struct Node
	{
		Node(const int id, const int value) :id(id), value(value) {}

		int id{ 0 };
		int value{ 0 };
	};

	class Traversal
	{
	public:
		explicit Traversal(int num_nodes,
			const std::vector<std::pair<int, int>> &edge_list, const std::vector<int> &value);

		std::pair<int, int> Traverse();

	private:
		void DFS(int node, const int
			value_sum, int& max_value,
			int& last_node, bool& is_done);

		std::vector<std::vector<Node>> adj_list_;
		std::vector<short> visited_;
	};

	Traversal::Traversal(const int num_nodes,
		const std::vector<std::pair<int, int>>& edge_list, const std::vector<int> &value)
	{
		adj_list_.resize(num_nodes);
		visited_.resize(num_nodes);
		for (const auto& edge : edge_list)
		{
			const auto&[u, v] = edge;
			adj_list_[u].emplace_back(v, value[v]);
		}

		for (auto &nodes : adj_list_)
		{
			std::sort(nodes.begin(), nodes.end(),
				[](const Node &a, const Node&b)->bool
			{
				return a.value > b.value;
			});
		}
	}

	std::pair<int, int> Traversal::Traverse()
	{
		auto max_value = 0;
		auto last_node = 0;
		bool is_done = false;
		DFS(0, 0, max_value, last_node, is_done);
		return std::make_pair(max_value, last_node);
	}

	void Traversal::DFS(const int node, const int value_sum,
		int& max_value, int& last_node, bool& is_done)
	{
		visited_[node] = 1;
		auto is_leaf = true;
		for (const auto& adj_node : adj_list_[node])
		{
			is_leaf = false;
			if (visited_[adj_node.id] != 0)
			{
				continue;
			}

			DFS(adj_node.id, value_sum + adj_node.value, max_value, last_node, is_done);
			if (is_done)
			{
				return;
			}
		}

		if (is_leaf && value_sum > max_value)
		{
			max_value = value_sum;
			last_node = node;
			is_done = true;
		}
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	int n;
	int m;
	std::vector<int> values;
	std::vector<std::pair<int, int>> edge_list;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> n >> m;
		values.resize(n);
		for (auto j = 0; j < n; ++j)
		{
			std::cin >> values[j];
		}

		edge_list.resize(m);
		for (auto j = 0; j < m; ++j)
		{
			std::cin >> edge_list[j].first >> edge_list[j].second;
		}

		uva12376::Traversal traversal(n, edge_list, values);
		auto[max_value, last_node] = traversal.Traverse();
		std::cout << "Case " << i << ": " << max_value << ' ' << last_node << std::endl;
	}

	return 0;
}
