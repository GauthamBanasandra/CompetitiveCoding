#include <vector>
#include <queue>
#include <iostream>

namespace uva10004
{
	class BipartiteCheck
	{
	public:
		BipartiteCheck(int num_nodes, const std::vector<std::pair<int, int>>& edge_list);

		bool Check() const;

	private:
		bool Check(int start_node, std::vector<int>& node_colour) const;

		const int num_nodes_;
		std::vector<std::vector<int>> adj_list_;
	};

	BipartiteCheck::BipartiteCheck(const int num_nodes,
		const std::vector<std::pair<int, int>>& edge_list) :num_nodes_(num_nodes)
	{
		adj_list_.resize(num_nodes_);
		for (const auto& edge : edge_list)
		{
			adj_list_[edge.first].emplace_back(edge.second);
			adj_list_[edge.second].emplace_back(edge.first);
		}
	}

	bool BipartiteCheck::Check() const
	{
		std::vector<int> node_colour(num_nodes_, -1);
		for (auto i = 0; i < num_nodes_; ++i)
		{
			if (node_colour[i] != -1)
			{
				continue;
			}

			if (!Check(i, node_colour))
			{
				return false;
			}
		}
		return true;
	}

	bool BipartiteCheck::Check(const int start_node,
		std::vector<int>& node_colour) const
	{
		std::queue<int> order;
		order.push(start_node);
		node_colour[start_node] = 0;

		while (!order.empty())
		{
			const auto node = order.front();
			order.pop();

			for (const auto adj_node : adj_list_[node])
			{
				if (node_colour[adj_node] == -1)
				{
					node_colour[adj_node] = 1 - node_colour[node];
					order.push(adj_node);
				}
				else if (node_colour[node] == node_colour[adj_node])
				{
					return false;
				}
			}
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	int n;
	int m;
	std::vector<std::pair<int, int>> edge_list;

	while (std::cin >> n, n)
	{
		std::cin >> m;
		edge_list.resize(m);
		for (auto i = 0; i < m; ++i)
		{
			std::cin >> edge_list[i].first >> edge_list[i].second;
		}

		uva10004::BipartiteCheck bipartite(n, edge_list);
		std::cout << (bipartite.Check() ? "BICOLORABLE." : "NOT BICOLORABLE.") << std::endl;
	}
	return 0;
}
