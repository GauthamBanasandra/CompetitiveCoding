#include <vector>
#include <algorithm>
#include <iostream>

namespace uva796
{
	using AdjList = std::vector<std::vector<int>>;
	using Edge = std::pair<int, int>;
	using EdgeList = std::vector<Edge>;
	const auto unvisited = -1;

	class GraphCheck
	{
	public:
		GraphCheck(int num_nodes, const AdjList& adj_list);

		EdgeList FindBridges();

	private:
		void NextBridge(int node, EdgeList& bridges);

		const int num_nodes_;
		const AdjList& adj_list_;
		std::vector<int> parent_;
		std::vector<int> visit_order_;
		std::vector<int> lowest_reachable_;
		int order_{ 0 };
	};


	GraphCheck::GraphCheck(const int num_nodes,
		const AdjList& adj_list) :num_nodes_(num_nodes), adj_list_(adj_list)
	{
		parent_.resize(num_nodes_);
		visit_order_.resize(num_nodes_, unvisited);
		lowest_reachable_.resize(num_nodes_);
	}

	EdgeList GraphCheck::FindBridges()
	{
		EdgeList bridges;
		for (auto i = 0; i < num_nodes_; ++i)
		{
			if (visit_order_[i] == unvisited)
			{
				NextBridge(i, bridges);
			}
		}

		std::sort(bridges.begin(), bridges.end(),
			[](const Edge & a, const Edge & b)->bool
			{
				if (a.first == b.first)
				{
					return a.second < b.second;
				}
				return a.first < b.first;
			});
		return bridges;
	}

	void GraphCheck::NextBridge(const int node, EdgeList& bridges)
	{
		visit_order_[node] = lowest_reachable_[node] = ++order_;
		for (const auto adj_node : adj_list_[node])
		{
			if (visit_order_[adj_node] == unvisited)
			{
				parent_[adj_node] = node;

				NextBridge(adj_node, bridges);

				if (lowest_reachable_[adj_node] > visit_order_[node])
				{
					bridges.emplace_back(std::min(node, adj_node),
						std::max(node, adj_node));
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
}

int main(int argc, char* argv[])
{
	int node;
	int num_nodes;
	int num_adj_nodes;
	char parenthesis;

	while (std::cin >> num_nodes, !std::cin.eof())
	{
		uva796::AdjList adj_list(num_nodes);
		for (auto i = 0; i < num_nodes; ++i)
		{
			std::cin >> node;
			std::cin >> parenthesis >> num_adj_nodes >> parenthesis;
			adj_list[node].resize(num_adj_nodes);
			for (auto j = 0; j < num_adj_nodes; ++j)
			{
				std::cin >> adj_list[node][j];
			}
		}

		uva796::GraphCheck graph(num_nodes, adj_list);
		const auto bridges = graph.FindBridges();
		std::cout << bridges.size() << " critical links" << std::endl;
		for (const auto& bridge : bridges)
		{
			std::cout << bridge.first << " - " << bridge.second << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}
