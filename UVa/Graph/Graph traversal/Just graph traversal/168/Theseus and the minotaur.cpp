#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <ios>

namespace uva168
{
	class Simulator
	{
	public:
		explicit Simulator(const std::string &graph);

		std::pair<std::vector<char>, char> Simulate(char theseus, char minotaur, int k);

	private:
		std::vector<char> GetLitCaverns() const;

		std::unordered_map<char, int> lit_caverns_;
		std::unordered_map<char, std::vector<char>> graph_;
	};

	Simulator::Simulator(const std::string& graph)
	{
		// Create an adjacency graph
		for (std::size_t i = 0, len = graph.size(); i < len;)
		{
			const auto node = graph[i++];
			const auto separator = graph[i++];
			// Handling the corner cases while parsing input
			if (separator == '.')
			{
				break;
			}
			if (separator == ';')
			{
				continue;
			}

			auto &adj_nodes = graph_[node];
			auto adj_node = '\0';
			while (adj_node = graph[i++], adj_node != ';' && adj_node != '.')
			{
				adj_nodes.emplace_back(adj_node);
			}
			if (adj_node == '.')
			{
				break;
			}
		}
	}

	std::pair<std::vector<char>, char> Simulator::Simulate(char theseus, char minotaur, const int k)
	{
		auto i_candle = 0;
		auto count = 0;
		// Until the minotaur is able to find a way
		while (minotaur != '\0')
		{
			// Assume that minotaur can't find a way
			auto next = '\0';
			for (const auto node : graph_[minotaur])
			{
				// The next cavern minotaur chooses shouldn't have theseus and shouldn't be lit
				if (node == theseus || lit_caverns_.find(node) != lit_caverns_.end())
				{
					continue;
				}
				next = node;
				break;
			}

			// Theseus will reach the cavern in which minotaur is there
			theseus = minotaur;
			++count;

			// Minotaur will go to the next cavern that it has found
			minotaur = next;

			// Theseus lights a candle after he moves 'count' number of caverns
			// The next != '\0' check prevents Theseus from lighting a candle if minotaur has been captured
			if (count % k == 0 && next != '\0')
			{
				lit_caverns_[theseus] = i_candle++;
			}
		}
		return { GetLitCaverns(), theseus };
	}

	std::vector<char> Simulator::GetLitCaverns() const
	{
		std::vector<char> lit_caverns(lit_caverns_.size());
		for (const auto& cavern : lit_caverns_)
		{
			lit_caverns[cavern.second] = cavern.first;
		}
		return lit_caverns;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	char theseus;
	char minotaur;
	int k;
	std::string graph;

	while (std::cin >> graph, graph[0] != '#')
	{
		std::cin >> minotaur >> theseus >> k;
		uva168::Simulator simulator(graph);
		auto[lit_caverns, trapped_cavern] = simulator.Simulate(theseus, minotaur, k);
		for (const auto cavern : lit_caverns)
		{
			std::cout << cavern << ' ';
		}
		std::cout << '/' << trapped_cavern << std::endl;
	}
	return 0;
}
