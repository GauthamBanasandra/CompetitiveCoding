#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <algorithm>
#include <queue>
#include <iostream>

namespace uva11749
{
	class Traversal
	{
	public:
		explicit Traversal(const std::vector<std::tuple<int, int, int>>& edge_list);

		int Count();

	private:
		int BFS(int node);

		std::unordered_map<int, std::vector<int>> adj_list_;
		std::unordered_set<int> visited_;
	};

	Traversal::Traversal(const std::vector<std::tuple<int, int, int>>& edge_list)
	{
		const auto max_ppa_it = std::max_element(edge_list.begin(), edge_list.end(),
			[](const std::tuple<int, int, int> & a, const std::tuple<int, int, int> & b)->bool
			{
				return std::get<2>(a) < std::get<2>(b);
			});

		const auto max_ppa = std::get<2>(*max_ppa_it);
		for (const auto& edge : edge_list)
		{
			const auto& [u, v, ppa] = edge;
			if (ppa != max_ppa)
			{
				continue;
			}

			adj_list_[u].emplace_back(v);
			adj_list_[v].emplace_back(u);
		}
	}

	int Traversal::Count()
	{
		auto max_count = 0;
		for (const auto& adj_list : adj_list_)
		{
			if (visited_.find(adj_list.first) != visited_.end())
			{
				continue;
			}

			const auto count = BFS(adj_list.first);
			max_count = std::max(max_count, count);
		}
		return max_count;
	}

	int Traversal::BFS(int node)
	{
		std::queue<int> order;
		order.push(node);
		auto count = 1;
		visited_.insert(node);

		while (!order.empty())
		{
			node = order.front();
			order.pop();

			for (const auto& adj_node : adj_list_[node])
			{
				if (visited_.find(adj_node) != visited_.end())
				{
					continue;
				}
				visited_.insert(adj_node);
				order.push(adj_node);
				++count;
			}
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	int n;
	int u, v, ppa;
	std::size_t m;
	std::vector<std::tuple<int, int, int>> edge_list;

	while (std::cin >> n >> m, n || m)
	{
		edge_list.resize(m);
		for (std::size_t i = 0; i < m; ++i)
		{
			std::cin >> u >> v >> ppa;
			edge_list[i] = { u, v, ppa };
		}

		uva11749::Traversal traversal(edge_list);
		std::cout << traversal.Count() << std::endl;
	}
	return 0;
}
