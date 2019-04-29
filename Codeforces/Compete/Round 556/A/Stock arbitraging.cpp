#include <vector>
#include <algorithm>
#include <iostream>

namespace round_556
{
	int GetMaxProfit(const std::vector<int>& cost_price,
		const std::vector<int>& selling_price, const int budget)
	{
		const auto cheapest_it = std::min_element(
			cost_price.begin(), cost_price.end());
		const auto num_shares = budget / *cheapest_it;
		const auto budget_remaining = budget % *cheapest_it;
		const auto expensive_it = std::max_element(
			selling_price.begin(), selling_price.end());
		return std::max(budget,
			num_shares * *expensive_it + budget_remaining);
	}
}

int main(int argc, char* argv[])
{
	int n;
	int m;
	int r;

	std::cin >> n >> m >> r;
	std::vector<int> cost_price(n);
	std::vector<int> selling_price(m);

	for (auto i = 0; i < n; ++i)
	{
		std::cin >> cost_price[i];
	}
	for (auto i = 0; i < m; ++i)
	{
		std::cin >> selling_price[i];
	}

	std::cout << round_556::GetMaxProfit(cost_price, selling_price, r) << std::endl;
	return 0;
}
