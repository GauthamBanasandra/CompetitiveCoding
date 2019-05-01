// WIP

#include <vector>
#include <algorithm>
#include <iostream>

using AdjList = std::vector<std::vector<int>>;
using EdgeList = std::vector<std::pair<int, int>>;

const auto unvisited = -1;

class Graph
{
public:
	Graph(const EdgeList& edge_list, int num_nodes);
	std::vector<std::pair<int, int>> GetOneWayRoute();

private:
	void FindBridge(int node, EdgeList& bridges);

	const int num_nodes_;
	AdjList adj_list_;
	std::vector<int> parent_;
	std::vector<int> visit_order_;
	std::vector<int> lowest_reachable_;

	int order_{ 0 };
};

Graph::Graph(const EdgeList& edge_list, const int num_nodes)
	:num_nodes_(num_nodes)
{
	adj_list_.resize(num_nodes_ + 1);
	for (const auto& edge : edge_list)
	{
		adj_list_[edge.first].emplace_back(edge.second);
		adj_list_[edge.second].emplace_back(edge.first);
	}

	parent_.resize(num_nodes_ + 1);
	visit_order_.resize(num_nodes_ + 1, -1);
	lowest_reachable_.resize(num_nodes_ + 1);
}

std::vector<std::pair<int, int>> Graph::GetOneWayRoute()
{
	EdgeList bridges;

	for (auto i = 1; i <= num_nodes_; ++i)
	{
		if (visit_order_[i] == unvisited)
		{
			FindBridge(i, bridges);
		}
	}
	return bridges;
}

void Graph::FindBridge(const int node, EdgeList & bridges)
{
	visit_order_[node] = lowest_reachable_[node] = ++order_;
	for (const auto& adj_node : adj_list_[node])
	{
		if (visit_order_[adj_node] == unvisited)
		{
			parent_[adj_node] = node;

			FindBridge(adj_node, bridges);

			if (lowest_reachable_[adj_node] > visit_order_[node])
			{
				bridges.emplace_back(node, adj_node);
			}
			lowest_reachable_[node] = std::min(
				lowest_reachable_[node], lowest_reachable_[adj_node]);
		}
		else if (parent_[node] != adj_node)
		{
			lowest_reachable_[node] = std::min(
				lowest_reachable_[node], visit_order_[adj_node]);
		}
	}
}

int main(int argc, char* argv[])
{
	auto t = 0;
	int num_nodes;
	int num_edges;
	EdgeList edge_list;

	while (std::cin >> num_nodes >> num_edges, num_nodes || num_edges)
	{
		edge_list.resize(num_edges);
		for (auto i = 0; i < num_edges; ++i)
		{
			std::cin >> edge_list[i].first >> edge_list[i].second;
		}

		Graph graph(edge_list, num_nodes);
		std::cout << ++t << std::endl << std::endl;
		for (const auto& bridge : graph.GetOneWayRoute())
		{
			std::cout << bridge.first << ' ' << bridge.second << std::endl;
		}
		std::cout << '#' << std::endl;
	}
	return 0;
}
