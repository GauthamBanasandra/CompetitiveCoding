#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <ios>
#include <cassert>

using Commands = std::vector<std::pair<char, int>>;

void TrackOpenTweets(const Commands& commands)
{
	std::unordered_set<int> tracker;
	for (const auto &command : commands)
	{
		switch (command.first)
		{
		case 'C':
		{
			const auto find_it = tracker.find(command.second);
			if (find_it == tracker.end())
			{
				tracker.insert(command.second);
			}
			else
			{
				tracker.erase(find_it);
			}
		}
		break;
		case 'A':
		{
			tracker.clear();
		}
		break;
		default:
			assert(false);
		}

		std::cout << tracker.size() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int x;
	std::size_t n, k;
	std::string command;
	std::cin >> n >> k;
	Commands commands;
	commands.reserve(k);

	for (std::size_t i = 0; i < k; ++i)
	{
		std::cin >> command;
		if (command.length() == 5)
		{
			std::cin >> x;
			commands.emplace_back('C', x);
		}
		else
		{
			commands.emplace_back('A', -1);
		}
	}

	TrackOpenTweets(commands);
	return 0;
}
