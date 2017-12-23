#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <vector>

void print(const std::unordered_map<char, std::vector<char>> &adj_list, const std::unordered_set<char> &areas_asleep, const std::bitset<26> &areas_awake)
{
	std::cout << "Graph:" << std::endl;
	for (const auto &node : adj_list)
	{
		std::cout << node.first << " -> ";
		for (const auto &neighbour : node.second)
		{
			std::cout << neighbour << " ";
		}

		std::cout << std::endl;
	}

	std::cout << "\nAreas awake: " << areas_awake.to_string() << std::endl;
	std::cout << "\nAreas asleep:" << std::endl;
	for (auto area : areas_asleep)
	{
		std::cout << area << " ";
	}

	std::cout << std::endl;
}