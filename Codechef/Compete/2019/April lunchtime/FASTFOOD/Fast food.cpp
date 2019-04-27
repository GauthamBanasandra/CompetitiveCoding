#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

namespace april_lunchtime_2019
{
	int GetMaxProfit(const std::vector<int>& chefland,
		const std::vector<int>& chefabad, const int n)
	{
		auto max_profit = 0;
		auto profit_chefland = 0;
		auto profit_chefabad = std::accumulate(
			chefabad.begin(), chefabad.end(), 0);

		max_profit = profit_chefabad;

		for (auto i = 0; i < n; ++i)
		{
			profit_chefabad -= chefabad[i];
			profit_chefland += chefland[i];
			max_profit = std::max(
				max_profit, profit_chefland + profit_chefabad);
		}
		return max_profit;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	std::vector<int> chefland;
	std::vector<int> chefabad;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		chefland.resize(n);
		chefabad.resize(n);

		for (auto i = 0; i < n; ++i)
		{
			std::cin >> chefland[i];
		}
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> chefabad[i];
		}

		std::cout << april_lunchtime_2019::GetMaxProfit(chefland, chefabad, n) << std::endl;
	}
	return 0;
}
