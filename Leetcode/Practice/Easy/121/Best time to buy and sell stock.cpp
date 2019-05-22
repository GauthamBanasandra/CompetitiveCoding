#include <iostream>
#include <vector>

int GetMaxProfit(const std::vector<int>& prices)
{
	if (prices.empty())
	{
		return 0;
	}

	auto min_price = prices.front();
	auto max_profit = 0;

	for (auto i = 1, len = static_cast<int>(prices.size()); i < len; ++i)
	{
		const auto profit = prices[i] - min_price;
		if (profit < 0)
		{
			min_price = prices[i];
		}
		else if (profit > max_profit)
		{
			max_profit = profit;
		}
	}
	return max_profit;
}

class Solution
{
public:
	static int maxProfit(std::vector<int>& prices);
};

int Solution::maxProfit(std::vector<int>& prices)
{
	return GetMaxProfit(prices);
}

int main(int argc, char* argv[])
{
	return 0;
}
