#include <vector>
#include <string>
#include <map>
#include <stack>
#include <algorithm>
#include <iostream>
#include <ios>

namespace uva12582
{
	std::vector<std::pair<char, std::size_t>> GetNodesDegree(const std::string& order)
	{
		// The order is just output of a DFS traversal
		// The output of a DFS traversal follows LIFO
		// Thus we could use a stack to follow the traversal and keep track of the edges
		std::stack<char> traversal;
		std::map<char, std::vector<char>> graph;

		for (const auto sprinkler : order)
		{
			// First node, so just push
			if (traversal.empty())
			{
				traversal.push(sprinkler);
				continue;
			}

			const auto top = traversal.top();
			// If the top of stack matches the current sprinkler,
			// it means that we're exiting the node (as per the problem)
			// Hence, we just pop it
			if (top == sprinkler)
			{
				traversal.pop();
				continue;
			}

			// If the top of stack doesn't match the current sprinkler,
			// it means that we're entering the node for the first time (as per the problem)
			// Hence, we just push it
			traversal.push(sprinkler);
			graph[sprinkler].emplace_back(top);
			graph[top].emplace_back(sprinkler);
		}

		std::vector<std::pair<char, std::size_t>> out;
		std::transform(graph.begin(), graph.end(), std::back_inserter(out),
			[](std::pair<const char, const std::vector<char>&> item)->std::pair<char, std::size_t>
		{
			return std::make_pair(item.first, item.second.size());
		});
		return out;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	std::string order;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> order;
		std::cout << "Case " << i << std::endl;
		for (const auto nodes_degree : uva12582::GetNodesDegree(order))
		{
			std::cout << nodes_degree.first << " = " << nodes_degree.second << std::endl;
		}
	}
	return 0;
}
