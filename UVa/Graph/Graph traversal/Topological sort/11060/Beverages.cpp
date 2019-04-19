#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <iostream>
#include <ios>

namespace uva11060
{
	class TopologicalSort
	{
	public:
		TopologicalSort(const std::vector<std::string>& beverages,
			const std::vector<std::pair<std::string, std::string>>& edge_list);

		std::vector<std::string> Sort();

	private:
		// Beverages list
		const std::vector<std::string>& beverages_;

		std::vector<int> in_degree_;

		// The adjacency list, based on the indices of the beverages
		// Using unordered_map with actual strings as node is expensive
		std::vector<std::vector<int>> adj_list_;

		// Reverse mapping of index to its corresponding beverage in the list
		std::unordered_map<int, std::string> rev_index_;
	};

	TopologicalSort::TopologicalSort(
		const std::vector<std::string>& beverages,
		const std::vector<std::pair<std::string, std::string>>&
		edge_list) :beverages_(beverages)
	{
		std::unordered_map<std::string, int> bev_index;
		const auto num_beverages = beverages_.size();
		for (auto i = 0; i < static_cast<int>(num_beverages); ++i)
		{
			rev_index_[i] = beverages_[i];
			bev_index[beverages_[i]] = i;
		}

		in_degree_.resize(num_beverages);
		adj_list_.resize(num_beverages);
		for (const auto& edge : edge_list)
		{
			adj_list_[bev_index[edge.first]].emplace_back(bev_index[edge.second]);
			++in_degree_[bev_index[edge.second]];
		}
	}

	// Need to use BFS based Kahn's algorithm here, rather than
	// the usual DFS based (Tarjan's) topological sorting algorithm
	// Explanation : In Kahn's algorithm, we have a deterministic start point
	// i.e. the node having 0 in-degree. If there are multiple nodes having
	// 0 in-degree, we choose the one according to the order in the input beverage list
	// Thus, we process the graph in a particular order
	// This is unlike DFS based topological sorting algorithm, where we start visiting
	// from all unvisited nodes, which can't guarantee that the graph will be
	// traversed in a particular order

	// Thus, whenever we expect topological sorting to be done in a particular order,
	// we need to use Kahn's algorithm
	std::vector<std::string> TopologicalSort::Sort()
	{
		// This is a variant of BFS
		// General implementation of Kahn's algorithm doesn't require a priority queue
		// Since the problem asks for us to pick in the order of beverages list,
		// we are using a priority queue here

		// Note that since the graph is maintained based on the index of beverages in the list
		// This guarantees that we follow the order specified in the beverages list

		// Another way of explaining this is as follows -
		// the beverage can enter the queue only when its in-degree becomes 0
		// This implies that all the beverages in this queue are peers w.r.t each other and to
		// break the tie, we go by the order specified in the beverages list
		// Thus, we need a priority queue to decide the order
		std::priority_queue<int, std::vector<int>, std::greater<>> order;

		// The following is just an implementation of Kahn's algorithm
		// where I read from - https://medium.com/insider-inc-engineering/the-wrath-of-kahns-algorithm-68081cf2fc55
		// It's highly advisable to go through the above link
		// It's very nicely explained
		const auto num_beverages = beverages_.size();
		for (auto i = 0; i < static_cast<int>(num_beverages); ++i)
		{
			if (in_degree_[i] == 0)
			{
				order.push(i);
			}
		}

		std::vector<std::string> beverages;
		beverages.reserve(num_beverages);
		while (!order.empty())
		{
			const auto node = order.top();
			order.pop();
			beverages.emplace_back(beverages_[node]);

			for (const auto adj_node : adj_list_[node])
			{
				--in_degree_[adj_node];
				if (in_degree_[adj_node] == 0)
				{
					order.push(adj_node);
				}
			}
		}
		return beverages;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	auto t = 0;
	int n;
	int m;
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
		if (std::cin.eof())
		{
			break;
		}

		std::vector<std::string> beverages;
		std::vector<std::pair<std::string, std::string>> edge_list;

		std::istringstream n_tokenizer(line);
		n_tokenizer >> n;
		beverages.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::getline(std::cin, beverages[i]);
		}

		std::getline(std::cin, line);
		std::istringstream m_tokenizer(line);
		m_tokenizer >> m;
		edge_list.resize(m);
		for (auto i = 0; i < m; ++i)
		{
			std::getline(std::cin, line);
			std::istringstream edge_list_tokenizer(line);
			edge_list_tokenizer >> edge_list[i].first >> edge_list[i].second;
		}

		std::cout << "Case #" << ++t << ": Dilbert should drink beverages in this order: ";
		uva11060::TopologicalSort sorter(beverages, edge_list);
		auto separator = "";
		for (const auto& beverage : sorter.Sort())
		{
			std::cout << separator << beverage;
			separator = " ";
		}
		std::cout << '.' << std::endl << std::endl;
		std::getline(std::cin, line);
	}
	return 0;
}
