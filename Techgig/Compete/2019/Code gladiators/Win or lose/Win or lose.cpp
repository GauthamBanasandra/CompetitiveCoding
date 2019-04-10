#include <vector>
#include <algorithm>
#include <iostream>

namespace code_gladiators
{
	bool IsPossible(std::vector<int>& villains, std::vector<int>& players)
	{
		std::sort(villains.begin(), villains.end());
		std::sort(players.begin(), players.end());

		for (std::size_t i = 0, len = villains.size(); i < len; ++i)
		{
			if (players[i] <= villains[i])
			{
				return false;
			}
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	int t;
	std::size_t n;
	std::vector<int> villains;
	std::vector<int> players;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		villains.resize(n);
		players.resize(n);

		for (std::size_t i = 0; i < n; ++i)
		{
			std::cin >> villains[i];
		}
		for (std::size_t i = 0; i < n; ++i)
		{
			std::cin >> players[i];
		}

		std::cout << (code_gladiators::IsPossible(villains, players) ? "WIN" : "LOSE") << std::endl;
	}
	return 0;
}
