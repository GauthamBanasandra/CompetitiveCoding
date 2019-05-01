// WA

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <iostream>

using AdjList = std::vector<std::vector<int>>;
using Edge = std::pair<int, int>;
using EdgeList = std::vector<Edge>;

const auto unvisited = -1;

struct EdgeFinder
{
	explicit EdgeFinder(const EdgeList& bridges);

	bool Exists(const Edge& edge);

private:
	std::unordered_set<std::string> edges_;
};

class Graph
{
public:
	Graph(const EdgeList& edge_list, int num_nodes);

	std::vector<std::pair<int, int>> GetOneWayRoute();

private:
	void DFS(int node, EdgeList& edge_list);
	void FindBridge(int node, EdgeList& bridges);

	const int num_nodes_;
	AdjList adj_list_;
	const EdgeList& edge_list_;
	std::vector<int> parent_;
	std::vector<int> visit_order_;
	std::vector<int> lowest_reachable_;
	std::vector<int> is_visited_;
	std::vector<int> has_out_edge_;

	int order_{ 0 };
};

EdgeFinder::EdgeFinder(const EdgeList& bridges)
{
	for (const auto& bridge : bridges)
	{
		edges_.emplace(std::to_string(bridge.first) +
			" " + std::to_string(bridge.second));
		edges_.emplace(std::to_string(bridge.second) +
			" " + std::to_string(bridge.first));
	}
}

bool EdgeFinder::Exists(const Edge & edge)
{
	return edges_.find(std::to_string(edge.first)
		+ " " + std::to_string(edge.second)) != edges_.end();
}

Graph::Graph(const EdgeList & edge_list, const int num_nodes)
	:num_nodes_(num_nodes), edge_list_(edge_list)
{
	adj_list_.resize(num_nodes_ + 1);
	for (const auto& edge : edge_list_)
	{
		adj_list_[edge.first].emplace_back(edge.second);
		adj_list_[edge.second].emplace_back(edge.first);
	}

	parent_.resize(num_nodes_ + 1);
	visit_order_.resize(num_nodes_ + 1, -1);
	lowest_reachable_.resize(num_nodes_ + 1);
	is_visited_.resize(num_nodes_ + 1, unvisited);
	has_out_edge_.resize(num_nodes_ + 1);
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

	EdgeList one_way;
	for (const auto& edge : edge_list_)
	{
		if (has_out_edge_[edge.first] == 1)
		{
			has_out_edge_[edge.second] = 1;
			one_way.emplace_back(edge.second, edge.first);
		}
		else
		{
			has_out_edge_[edge.first] = 1;
			one_way.emplace_back(edge.first, edge.second);
		}
	}

	EdgeFinder finder(bridges);
	for (auto i = 0, len = static_cast<int>(one_way.size()); i < len; ++i)
	{
		const auto edge = one_way[i];
		if (finder.Exists(edge))
		{
			one_way.emplace_back(edge.second, edge.first);
		}
	}
	return one_way;
}

void Graph::DFS(int node, EdgeList & edge_list)
{
	is_visited_[node] = 1;
	for (const auto& adj_node : adj_list_[node])
	{
		if (is_visited_[adj_node] != unvisited)
		{
			continue;
		}

		if (has_out_edge_[node] == 1)
		{
			edge_list.emplace_back(node, adj_node);
		}
		else
		{
			has_out_edge_[node] = 1;
			edge_list.emplace_back(adj_node, node);
		}

		DFS(adj_node, edge_list);
	}
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
