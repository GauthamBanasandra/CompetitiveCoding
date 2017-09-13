#include <iostream>
#include <ios>
#include <sstream>
#include <vector>
#include <string>

typedef unsigned long long big_int;

void Print(std::vector<std::vector<int>> scenarios);
void Print(std::vector<int> scenario);

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::vector<std::vector<int>> scenarios;
	std::vector<int> scenario;
	std::string line;
	int num;
	while (getline(std::cin, line), line != "0 0 0")
	{
		std::istringstream buf(line);
		while (buf >> num)
		{
			if (num == 0)
			{
				scenarios.push_back(scenario);
				scenario.clear();
				break;
			}

			scenario.push_back(num);
		}
	}

	for (big_int i = 0; i < scenarios.size(); ++i)
	{
		std::vector<int> status(scenarios[i].begin(), scenarios[i].end());
		Print(status);
		auto stop = false;

		while (!stop)
		{
			for (big_int k = 0; k < scenarios[i].size(); ++k)
			{
				status[k] += scenarios[i][k];
			}

			auto min_idx = 0;
			for (auto k = 1; k < status.size(); ++k)
			{
				if (status[k] < status[min_idx])
				{
					min_idx = k;
				}
			}

			stop = true;
			for (auto k = 0; k < status.size(); ++k)
			{
				if (!(status[k] >= status[min_idx] && status[k] < status[min_idx] + scenarios[i][k] - 5))
				{
					stop = false;
					break;
				}
			}

			Print(status);
		}
	}

	return 0;
}
