#include <vector>
#include <queue>
#include <iostream>
#include <ios>

namespace uva280
{
	using Graph = std::vector<std::vector<int>>;

	std::vector<int> GetUnreachableNodes(const Graph &graph, const int start_node)
	{
		std::vector<int> visited(graph.size());
		std::queue<int> order;
		order.push(start_node);

		while (!order.empty())
		{
			const auto node = order.front();
			order.pop();

			for (const auto adj_node : graph[node])
			{
				if (visited[adj_node] == 1)
				{
					continue;
				}

				visited[adj_node] = 1;
				order.push(adj_node);
			}
		}

		std::vector<int> unreachable_nodes;
		for (std::size_t i = 1, len = visited.size(); i < len; ++i)
		{
			if (visited[i] != 0)
			{
				continue;
			}
			unreachable_nodes.emplace_back(static_cast<int>(i));
		}
		return unreachable_nodes;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int node;
	int adj_node;
	int num_nodes;
	int num_start_nodes;
	int start_node;

	while (std::cin >> num_nodes, num_nodes != 0)
	{
		uva280::Graph graph(num_nodes + 1);
		while (std::cin >> node, node != 0)
		{
			auto &adj_nodes = graph[node];
			while (std::cin >> adj_node, adj_node != 0)
			{
				adj_nodes.emplace_back(adj_node);
			}
		}

		std::cin >> num_start_nodes;
		for (auto i = 0; i < num_start_nodes; ++i)
		{
			std::cin >> start_node;
			const auto unreachable_nodes = uva280::GetUnreachableNodes(graph, start_node);
			std::cout << unreachable_nodes.size();
			for (const auto unreachable_node : unreachable_nodes)
			{
				std::cout << ' ' << unreachable_node;
			}
			std::cout << std::endl;
		}
	}
	return 0;
}
