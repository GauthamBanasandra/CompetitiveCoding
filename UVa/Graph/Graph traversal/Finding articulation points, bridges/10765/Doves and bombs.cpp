// WA

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>

using AdjList = std::vector<std::vector<int>>;
using Edge = std::pair<int, int>;
using EdgeList = std::vector<Edge>;
const auto unvisited = -1;

class GraphCheck
{
public:
	GraphCheck(int num_nodes, int num_needed, const EdgeList& edge_list);

	std::vector<std::pair<int, int>> FindArticulationPoints();

private:
	int FindNumComponentsIfRemoved(int node) const;
	void Find(int node);

	const int num_nodes_;
	const int num_needed_;

	AdjList adj_list_;
	std::vector<int> parent_;
	std::vector<int> visit_order_;
	std::vector<int> lowest_reachable_;
	std::vector<int> is_articulation_point_;

	int root_{ 0 };
	int num_root_children_{ 0 };
	int order_{ 0 };
};

GraphCheck::GraphCheck(const int num_nodes, const int num_needed,
	const EdgeList& edge_list) :num_nodes_(num_nodes), num_needed_(num_needed)
{
	adj_list_.resize(num_nodes_);
	for (const auto& edge : edge_list)
	{
		adj_list_[edge.first].emplace_back(edge.second);
		adj_list_[edge.second].emplace_back(edge.first);
	}
	parent_.resize(num_nodes_);
	visit_order_.resize(num_nodes_, unvisited);
	lowest_reachable_.resize(num_nodes_);
	is_articulation_point_.resize(num_nodes_);
}

std::vector<std::pair<int, int>> GraphCheck::FindArticulationPoints()
{
	for (auto i = 0; i < num_nodes_; ++i)
	{
		if (visit_order_[i] != unvisited)
		{
			continue;
		}

		root_ = i;
		num_root_children_ = 0;
		Find(i);
		is_articulation_point_[root_] = num_root_children_ > 1;
	}

	std::vector<std::pair<int, int>> nodes(num_nodes_);
	for (auto i = 0; i < num_nodes_; ++i)
	{
		nodes[i] = std::make_pair(i, FindNumComponentsIfRemoved(i));
	}

	std::sort(nodes.begin(), nodes.end(),
		[](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			if (a.second == b.second)
			{
				return a.first < b.first;
			}
			return a.second > b.second;
		});
	nodes.resize(num_needed_);
	return nodes;
}

int GraphCheck::FindNumComponentsIfRemoved(const int node) const
{
	std::unordered_set<int> unique_lowest_reachable;
	for (const auto adj_node : adj_list_[node])
	{
		unique_lowest_reachable.insert(lowest_reachable_[adj_node]);
	}
	return static_cast<int>(unique_lowest_reachable.size());
}

void GraphCheck::Find(const int node)
{
	lowest_reachable_[node] = visit_order_[node] = ++order_;
	for (const auto adj_node : adj_list_[node])
	{
		if (visit_order_[adj_node] == unvisited)
		{
			parent_[adj_node] = node;
			if (node == root_)
			{
				++num_root_children_;
			}

			Find(adj_node);

			if (lowest_reachable_[adj_node] >= visit_order_[node])
			{
				is_articulation_point_[node] = 1;
			}
			lowest_reachable_[node] = std::min(lowest_reachable_[node],
				lowest_reachable_[adj_node]);
		}
		else if (parent_[node] != adj_node)
		{
			lowest_reachable_[node] = std::min(lowest_reachable_[node],
				visit_order_[adj_node]);
		}
	}
}

int main(int argc, char* argv[])
{
	int n;
	int m;
	Edge edge;

	while (std::cin >> n >> m, n || m)
	{
		EdgeList edge_list;
		while (std::cin >> edge.first >> edge.second,
			edge.first != -1 && edge.second != -1)
		{
			edge_list.emplace_back(edge);
		}

		GraphCheck graph(n, m, edge_list);
		for (const auto& point : graph.FindArticulationPoints())
		{
			std::cout << point.first << ' ' << point.second << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}
