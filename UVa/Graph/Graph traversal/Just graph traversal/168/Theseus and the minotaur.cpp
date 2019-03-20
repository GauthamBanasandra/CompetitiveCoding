// WIP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>

class Simulator
{
public:
	explicit Simulator(const std::string &graph);


private:
	std::unordered_map<char, int> lit_caverns_;
	std::unordered_map<char, std::vector<char>> graph_;
};

Simulator::Simulator(const std::string& graph)
{
	for (std::size_t i = 0, len = graph.size(); i < len;)
	{
		const auto node = graph[i++];
		const auto separator = graph[i++];
		assert(separator == ':');

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

int main(int argc, char* argv[])
{
	const std::string graph = "A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD.";
	Simulator simulator(graph);
	return 0;
}
