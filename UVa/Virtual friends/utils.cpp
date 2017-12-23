#include <unordered_map>
#include <iostream>

void print(const std::unordered_map<std::size_t, std::size_t> &tree_size)
{
	std::cout << "Representative elements:" << std::endl;
	for (const auto item : tree_size)
	{
		std::cout << item.first << " -> " << item.second << std::endl;
	}

	std::cout << std::endl;
}