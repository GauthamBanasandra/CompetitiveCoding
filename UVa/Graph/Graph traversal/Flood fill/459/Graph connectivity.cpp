#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <ios>

namespace uva459
{
	class Traversal
	{
	public:
		explicit Traversal(const std::vector<std::string> &edge_list);

		int CountConnectedComponents() const;

	private:
		void DFS(char node, std::unordered_set<char>& visited) const;

		std::vector<char> nodes_;
		std::unordered_map<char, std::vector<char>> adj_list_;
	};

	Traversal::Traversal(const std::vector<std::string>& edge_list)
	{
		for (const auto& edge : edge_list)
		{
			adj_list_[edge.front()].emplace_back(edge.back());
			adj_list_[edge.back()].emplace_back(edge.front());
		}

		nodes_.resize(adj_list_.size());
		std::transform(adj_list_.begin(), adj_list_.end(), nodes_.begin(),
			[](const std::pair<char, const std::vector<char>&> item)->char
		{
			return item.first;
		});
	}

	int Traversal::CountConnectedComponents() const
	{
		auto num_connected_components = 0;
		const auto num_nodes = adj_list_.size();
		std::unordered_set<char> visited;

		for (std::size_t i = 0; i < num_nodes; ++i)
		{
			if (visited.find(nodes_[i]) != visited.end())
			{
				continue;
			}

			++num_connected_components;
			DFS(nodes_[i], visited);
		}
		return num_connected_components;
	}

	void Traversal::DFS(const char node, std::unordered_set<char>& visited) const
	{
		visited.insert(node);

		const auto find_it = adj_list_.find(node);
		assert(find_it != adj_list_.end());
		for (const auto adj_node : find_it->second)
		{
			if (visited.find(adj_node) != visited.end())
			{
				continue;
			}

			DFS(adj_node, visited);
		}
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	std::string edge;
	std::vector<std::vector<std::string>> inputs;

	std::cin >> t;
	inputs.resize(t);

	auto i_input = -1;
	while (t--)
	{
		while (std::cin >> edge, !std::cin.eof())
		{
			if (edge.size() == 1)
			{
				++i_input;
				for (auto i = 'A'; i <= edge[0]; ++i)
				{
					inputs[i_input].emplace_back(2, i);
				}
				continue;
			}

			inputs[i_input].emplace_back(edge);
		}
	}

	for (std::size_t i = 0, len = inputs.size(); i < len; ++i)
	{
		uva459::Traversal traversal(inputs[i]);
		std::cout << traversal.CountConnectedComponents() << (i == len - 1 ? "" : "\n") << std::endl;
	}
	return 0;
}
