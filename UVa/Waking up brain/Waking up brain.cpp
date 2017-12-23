#include <iostream>
#include <string>
#include <bitset>
#include <unordered_set>
#include <vector>
#include <unordered_map>

#define N_AREAS 26
#define REQ_LINKS_AWAKE 3

void print(const std::unordered_map<char, std::vector<char>> &adj_list, const std::unordered_set<char> &areas_asleep, const std::bitset<26> &areas_awake);

int main(int argc, char* argv[])
{
	std::size_t areas, links, all_awake_time = 0;
	std::string line;
	std::unordered_map<char, std::vector<char>> adj_list;
	std::bitset<N_AREAS> areas_awake, areas_woken_up;
	std::unordered_set<char> areas_asleep;

	while (true)
	{
		adj_list.clear();
		areas_asleep.clear();
		areas_awake.reset();
		all_awake_time = 0;

		std::cin >> areas >> links;
		std::cin.ignore();
		if (std::cin.eof())
		{
			break;
		}

		std::getline(std::cin, line);
		for (const auto c : line)
		{
			areas_awake.set(c - 'A', true);
		}

		for (std::size_t i = 0; i < links; ++i)
		{
			std::getline(std::cin, line);
			adj_list[line[0]].emplace_back(line[1]);
			adj_list[line[1]].emplace_back(line[0]);

			if (!areas_awake.test(line[0] - 'A'))
			{
				areas_asleep.insert(line[0]);
			}

			if (!areas_awake.test(line[1] - 'A'))
			{
				areas_asleep.insert(line[1]);
			}
		}

		if (areas == REQ_LINKS_AWAKE)
		{
			std::cout << "WAKE UP IN, 0, YEARS" << std::endl;
			continue;
		}

		if (links == 0)
		{
			std::cout << "THIS BRAIN NEVER WAKES UP" << std::endl;
			continue;
		}

		while (!areas_asleep.empty())
		{
			auto at_least_one_woke_up = false;
			areas_woken_up.reset();

			for (const auto &area_asleep : areas_asleep)
			{
				std::size_t woken_up_links = 0;
				for (const auto &area : adj_list[area_asleep])
				{
					if (areas_awake.test(area - 'A'))
					{
						++woken_up_links;
					}

					if (woken_up_links >= REQ_LINKS_AWAKE)
					{
						areas_woken_up.set(area_asleep - 'A', true);
						at_least_one_woke_up = true;
						break;
					}
				}
			}

			areas_awake |= areas_woken_up;
			for (auto i = 0; i < N_AREAS; ++i)
			{
				if (areas_woken_up[i])
				{
					areas_asleep.erase(i + 'A');
				}
			}

			if (at_least_one_woke_up)
			{
				++all_awake_time;
			}
			else
			{
				std::cout << "THIS BRAIN NEVER WAKES UP" << std::endl;
				break;
			}
		}

		if (areas_asleep.empty())
		{
			std::cout << "WAKE UP IN, " << all_awake_time << ", YEARS" << std::endl;
		}
	}

	return 0;
}
