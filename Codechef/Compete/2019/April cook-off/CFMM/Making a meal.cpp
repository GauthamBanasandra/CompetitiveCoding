#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

namespace april_cook_off_2019
{
	int MaxFullMeals(const std::vector<std::string>& strings)
	{
		std::unordered_map<char, int> cauldron;
		for (const auto& str : strings)
		{
			for (const auto c : str)
			{
				++cauldron[c];
			}
		}

		std::vector<std::pair<char, int>> frequency{
			{'c', 2},
			{'o', 1},
			{'d', 1},
			{'e', 2},
			{'h', 1},
			{'f', 1},
		};

		auto count = 0;
		auto is_possible = true;
		while (is_possible)
		{
			for (const auto& f : frequency)
			{
				cauldron[f.first] -= f.second;
				if (cauldron[f.first] < 0)
				{
					is_possible = false;
					return count;
				}
			}
			++count;
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	std::vector<std::string> strings;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		strings.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> strings[i];
		}

		std::cout << april_cook_off_2019::MaxFullMeals(strings) << std::endl;
	}
	return 0;
}
