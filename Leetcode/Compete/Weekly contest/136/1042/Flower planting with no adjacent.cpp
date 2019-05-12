#include <vector>
#include <queue>
#include <iostream>

const auto colourless = -1;

class Graph
{
public:
	Graph(int num_nodes, const std::vector<std::vector<int>>& edge_list);

	std::vector<int> Colour() const;

private:
	void Colour(int start_node, std::vector<int>& colours) const;

	const int num_nodes_;
	std::vector<std::vector<int>> adj_list_;
};

Graph::Graph(const int num_nodes,
	const std::vector<std::vector<int>>& edge_list) :num_nodes_(num_nodes)
{
	adj_list_.resize(num_nodes_ + 1);
	for (const auto& edge : edge_list)
	{
		adj_list_[edge.front()].emplace_back(edge.back());
		adj_list_[edge.back()].emplace_back(edge.front());
	}
}

std::vector<int> Graph::Colour() const
{
	std::vector<int> colours(num_nodes_ + 1, colourless);
	for (auto i = 1; i <= num_nodes_; ++i)
	{
		if (colours[i] == colourless)
		{
			Colour(i, colours);
		}
	}
	return { colours.begin() + 1, colours.end() };
}

void Graph::Colour(const int start_node,
	std::vector<int>& colours) const
{
	std::queue<int> order;
	order.push(start_node);
	colours[start_node] = 1;

	while (!order.empty())
	{
		const auto node = order.front();
		order.pop();
		auto colour = colours[node];
		for (const auto adj_node : adj_list_[node])
		{
			if (colours[adj_node] == colourless)
			{
				++colour;
				colour = colour == 5 ? 1 : colour;
				std::vector<int> pick{ 0, 1, 1, 1, 1 };
				for (const auto adj_adj_node : adj_list_[adj_node])
				{
					if (colours[adj_adj_node] != colourless)
					{
						pick[colours[adj_adj_node]] = 0;
					}
				}
				for (auto i = 1; i <= 4; ++i)
				{
					if (pick[i] == 1)
					{
						colours[adj_node] = i;
						break;
					}
				}
				order.push(adj_node);
			}
		}
	}
}

class Solution {
public:
	static std::vector<int> gardenNoAdj(
		int N, std::vector<std::vector<int>>& paths);
};

std::vector<int> Solution::gardenNoAdj(const int N, std::vector<std::vector<int>>& paths)
{
	return Graph(N, paths).Colour();
}

int main(int argc, char* argv[])
{
	//std::vector<std::vector<int>> paths{ {1, 2}, {3, 4}, {3, 2}, {4, 2}, {1, 4} };
	std::vector<std::vector<int>> paths{ {3, 4}, {4, 5}, {3, 2}, {5, 1}, {1, 3}, {4, 2} };
	for (const auto colour : Solution::gardenNoAdj(5, paths))
	{
		std::cout << colour << std::endl;
	}
	return 0;
}
