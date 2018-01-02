#include <vector>
#include <iostream>
#include <unordered_map>

void print(const std::vector<int>& data)
{
	for (const auto& value : data)
	{
		std::cout << value << " ";
	}

	std::cout << std::endl;
}

void print(const std::unordered_map<int, int> &kv)
{
	for (const auto& kv : kv)
	{
		std::cout << kv.first << " : " << kv.second << std::endl;
	}
}