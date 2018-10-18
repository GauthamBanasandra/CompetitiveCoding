//
// Created by Gautham on 17-10-2018.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using FrequencyTable = std::unordered_map<int, int>;

int CountBeautifulPairs(const std::vector<int>& a, const std::vector<int>& b)
{
	FrequencyTable a_ft, b_ft;
	for (auto value : a)
	{
		++a_ft[value];
	}

	for (auto value : b)
	{
		++b_ft[value];
	}

	auto num_pairs = 0;
	for (auto b_it = b_ft.begin(); b_it != b_ft.end();)
	{
		auto find = a_ft.find(b_it->first);
		if (find == a_ft.end())
		{
			++b_it;
			continue;
		}

		if (b_it->second > find->second)
		{
			num_pairs += find->second;
			b_it->second -= find->second;
			find->second = 0;
		}
		else if (find->second > b_it->second)
		{
			num_pairs += b_it->second;
			find->second -= b_it->second;
			b_it->second = 0;
		}
		else
		{
			num_pairs += find->second;
			find->second = b_it->second = 0;
		}

		if (find->second == 0)
		{
			a_ft.erase(find);
		}
		if (b_it->second == 0)
		{
			b_it = b_ft.erase(b_it);
		}
		else
		{
			++b_it;
		}
	}
	return num_pairs + (b_ft.empty() && a_ft.empty() ? -1 : 1);
}

int main(int argc, char* argv[])
{
	std::size_t n;
	std::vector<int> a, b;
	std::cin >> n;
	a.resize(n);
	b.resize(n);

	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> a[i];
	}
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> b[i];
	}
	std::cout << CountBeautifulPairs(a, b) << std::endl;
	return 0;
}
