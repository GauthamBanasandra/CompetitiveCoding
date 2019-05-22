#include <iostream>
#include <vector>

int GetMaxProfit(const std::vector<int>& prices)
{
	if (prices.empty())
	{
		return 0;
	}

	// Assume that the first one is the one with least cost
	auto min_price = prices.front();
	// Profit can never be negative
	auto max_profit = 0;

	for (auto i = 1, len = static_cast<int>(prices.size()); i < len; ++i)
	{
		const auto profit = prices[i] - min_price;
		// Profit being negative implies that prices[i] is a better
		// minimum than min_price that could give better profits
		// for the upcoming prices
		if (profit < 0)
		{
			min_price = prices[i];
		}
		// Profit is positive so, check if it's the best profit
		// so far and update
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
