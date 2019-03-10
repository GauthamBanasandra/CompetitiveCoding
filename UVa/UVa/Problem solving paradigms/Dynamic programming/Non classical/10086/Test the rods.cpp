#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cassert>

const auto infinity = std::numeric_limits<long>::max();

class Selector
{
public:
	Selector(const std::vector<int> &rods,
		const std::vector<std::vector<int>> &cost_ncpc,
		const std::vector<std::vector<int>> &cost_bcew,
		int rem_ncpc, int rem_bcew);

	long Select() { return Select(0, rem_ncpc_, rem_bcew_); }

private:
	long Select(std::size_t i_rod, int rem_ncpc, int rem_bcew);

	const int rem_ncpc_;
	const int rem_bcew_;
	const std::vector<int> &rods_;
	const std::vector<std::vector<int>> &cost_ncpc_;
	const std::vector<std::vector<int>> &cost_bcew_;
	std::vector<std::vector<std::vector<long>>> memo_;
};

Selector::Selector(const std::vector<int>& rods,
	const std::vector<std::vector<int>>& cost_ncpc,
	const std::vector<std::vector<int>>& cost_bcew,
	const int rem_ncpc, const int rem_bcew) :rem_ncpc_(rem_ncpc), rem_bcew_(rem_bcew), rods_(rods), cost_ncpc_(cost_ncpc), cost_bcew_(cost_bcew)
{
	memo_.resize(rods_.size(),
		std::vector<std::vector<long>>(rem_ncpc_ + 1,
			std::vector<long>(rem_bcew_ + 1, -1)));
}

long Selector::Select(const std::size_t i_rod, const int rem_ncpc, const int rem_bcew)
{
	assert(rem_ncpc >= 0);
	assert(rem_bcew >= 0);

	if (i_rod >= rods_.size())
	{
		return infinity;
	}

	if (rem_ncpc == 0 && rem_bcew == 0)
	{
		return 0;
	}

	auto &memo = memo_[i_rod][rem_ncpc][rem_bcew];
	if (memo != -1)
	{
		return memo;
	}

	auto min_cost = infinity;
	for (auto i = 0, len = rods_[i_rod]; i <= len; ++i)
	{
		if (i > rem_ncpc || len - i > rem_bcew)
		{
			continue;
		}

		auto cost = Select(i_rod + 1,
			rem_ncpc - i,
			rem_bcew - (len - i));
		cost = cost == infinity ? 0 : cost;

		if (i == 0)
		{
			cost += cost_bcew_[i_rod][len - 1];
		}
		else if (i == len)
		{
			cost += cost_ncpc_[i_rod][len - 1];
		}
		else
		{
			cost += cost_ncpc_[i_rod][i - 1];
			cost += cost_bcew_[i_rod][len - (i + 1)];
		}

		min_cost = std::min(min_cost, cost);
	}
	return memo = min_cost;
}

int main(int argc, char* argv[])
{
	std::size_t num_rods;
	auto rem_ncpc = 10;
	auto rem_bcew = 12;
	std::vector<int> rods{ 5, 7, 4, 3, 3 };
	std::vector<std::vector<int>> cost_ncpc{
		/*{ 10, 30, 70, 150, 310 },
		{ 30, 60, 90, 120, 160, 200, 240 },
		{ 40, 60, 80, 100 },
		{ 60, 120, 180 },
		{ 30, 70, 100 }*/
	};

	std::vector<std::vector<int>> cost_bcew{
		/*{10, 20, 40, 60, 180},
		{20, 60, 100, 130, 160, 200, 240},
		{30, 70, 100, 120},
		{20, 50, 90},
		{30, 70, 100},*/
	};

	while (std::cin >> rem_ncpc >> rem_bcew, rem_ncpc || rem_bcew)
	{
		std::cin >> num_rods;
		rods.resize(num_rods);
		cost_ncpc.resize(num_rods);
		cost_bcew.resize(num_rods);

		for (std::size_t i = 0; i < num_rods; ++i)
		{
			std::cin >> rods[i];
			const auto num_samples = rods[i];
			cost_ncpc[i].resize(num_samples);
			cost_bcew[i].resize(num_samples);

			for (auto j = 0; j < num_samples; ++j)
			{
				std::cin >> cost_ncpc[i][j];
			}
			for (auto j = 0; j < num_samples; ++j)
			{
				std::cin >> cost_bcew[i][j];
			}
		}

		Selector selector(rods, cost_ncpc, cost_bcew, rem_ncpc, rem_bcew);
		std::cout << selector.Select() << std::endl;
	}

	/*Selector selector(rods, cost_ncpc, cost_bcew, rem_ncpc, rem_bcew);
	std::cout << selector.Select() << std::endl;*/
	return 0;
}
