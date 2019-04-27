#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

namespace april_lunchtime_2019
{
	std::vector<std::string> GetNames(const std::vector<std::pair<std::string, std::string>>& full_names)
	{
		std::vector<std::string> names;
		names.reserve(full_names.size());

		std::unordered_map<std::string, int> unique_first;
		for (const auto& name : full_names)
		{
			++unique_first[name.first];
		}

		for (const auto& name : full_names)
		{
			if (unique_first[name.first] > 1)
			{
				names.emplace_back(name.first + " " + name.second);
			}
			else
			{
				names.emplace_back(name.first);
			}
		}
		return names;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	std::vector<std::pair<std::string, std::string>> full_names;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		full_names.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> full_names[i].first >> full_names[i].second;
		}

		for (const auto& name : april_lunchtime_2019::GetNames(full_names))
		{
			std::cout << name << std::endl;
		}
	}
	return 0;
}
