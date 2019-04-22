// WIP

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

class BipartiteCheck
{
public:
	BipartiteCheck(const int num_nodes, const std::vector<std::vector<int>>& adj_list)
		:num_nodes_(num_nodes + 1), adj_list_(adj_list) {}

	int CountFriends() const;

private:
	int CountFriends(int start_node, std::vector<int>& node_colour) const;

	const int num_nodes_;
	const std::vector<std::vector<int>>& adj_list_;
};

int BipartiteCheck::CountFriends() const
{
	auto total_count = 0;
	std::vector<int> node_colour(num_nodes_, -1);
	for (auto i = 1; i < num_nodes_; ++i)
	{
		if (node_colour[i] != -1)
		{
			continue;
		}

		const auto count = CountFriends(i, node_colour);
		if (count != -1)
		{
			total_count += count;
		}
	}
	return total_count;
}

int BipartiteCheck::CountFriends(const int start_node,
	std::vector<int>& node_colour) const
{
	std::queue<int> order;
	order.push(start_node);
	node_colour[start_node] = 0;
	std::vector<int> num_colour(2);
	auto is_bipartite = true;

	while (!order.empty())
	{
		const auto node = order.front();
		order.pop();

		++num_colour[node_colour[node]];

		for (const auto adj_node : adj_list_[node])
		{
			if (node_colour[adj_node] == -1)
			{
				node_colour[adj_node] = 1 - node_colour[node];
				order.push(adj_node);
			}
			else if (node_colour[node] == node_colour[adj_node])
			{
				is_bipartite = false;
			}
		}
	}
	return is_bipartite ? *std::max_element(num_colour.begin(), num_colour.end()) : -1;
}

int main(int argc, char* argv[])
{
	int t;
	int num_nodes;
	int num_adj_nodes;
	int adj_node;

	std::cin >> t;
	while (t--)
	{
		std::cin >> num_nodes;
		std::vector<std::vector<int>> adj_list(num_nodes + 1);

		for (auto i = 1; i <= num_nodes; ++i)
		{
			std::cin >> num_adj_nodes;
			for (auto j = 0; j < num_adj_nodes; ++j)
			{
				std::cin >> adj_node;
				if (adj_node > num_nodes)
				{
					continue;
				}
				adj_list[i].emplace_back(adj_node);
				adj_list[adj_node].emplace_back(i);
			}
		}

		BipartiteCheck check(num_nodes, adj_list);
		std::cout << check.CountFriends() << std::endl;
	}
	return 0;
}
