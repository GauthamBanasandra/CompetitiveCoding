#include <tuple>
#include <utility>
#include <vector>
#include <iostream>
#include <limits>
#include <cassert>
#include <ios>

namespace uva10086
{
	const auto infinity = std::numeric_limits<long>::max();
	using Pos = std::tuple<std::size_t, int, int>;

	struct Metadata final
	{
		Pos pos;
		int num_ncpc{ 0 };
	};

	class Selector final
	{
	public:
		Selector(const std::vector<int> &rods,
			const std::vector<std::vector<int>> &cost_ncpc,
			const std::vector<std::vector<int>> &cost_bcew,
			int rem_ncpc, int rem_bcew);

		std::pair<long, std::vector<int>> Select();

	private:
		long Select(std::size_t i_rod, int rem_ncpc, int rem_bcew);
		std::vector<int> Reconstruct() const;

		const int rem_ncpc_;
		const int rem_bcew_;
		const std::vector<int> &rods_;
		const std::vector<std::vector<int>> &cost_ncpc_;
		const std::vector<std::vector<int>> &cost_bcew_;
		std::vector<std::vector<std::vector<long>>> memo_;

		// In order to reconstruct and print selections that were made,
		// we need a another memo table with the same dimensions as the primary (memo_)
		std::vector<std::vector<std::vector<Metadata>>> memo_selection_;
	};

	Selector::Selector(const std::vector<int>& rods,
		const std::vector<std::vector<int>>& cost_ncpc,
		const std::vector<std::vector<int>>& cost_bcew,
		const int rem_ncpc, const int rem_bcew) :rem_ncpc_(rem_ncpc), rem_bcew_(rem_bcew), rods_(rods), cost_ncpc_(cost_ncpc), cost_bcew_(cost_bcew)
	{
		memo_.resize(rods_.size(),
			std::vector<std::vector<long>>(rem_ncpc_ + 1,
				std::vector<long>(rem_bcew_ + 1, -1)));

		memo_selection_.resize(rods_.size(),
			std::vector<std::vector<Metadata>>(rem_ncpc_ + 1,
				std::vector<Metadata>(rem_bcew_ + 1)));
	}

	std::pair<long, std::vector<int>> Selector::Select()
	{
		const auto min_cost = Select(0, rem_ncpc_, rem_bcew_);
		return std::make_pair(min_cost, Reconstruct());
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
		Metadata metadata;
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

			if (cost < min_cost)
			{
				min_cost = cost;
				// Printing out the selections that were made involves retracing the recursive calls that were made
				// Here, during reconstruction, we just trace only one path -> starting from the initial state (0, rem_ncpc_, rem_bcew) to the last state
				// We accomplish this by storing the next state that returned a "minimal" value to the current state 

				// Plainly, the current state (i_rod, rem_ncpc, rem_bcew) transitioned to (i_rod + 1, rem_ncpc - i, rem_bcew - (len - i))
				// So, we're just storing this tuple if upon transitioning to this state returned a minimal value
				metadata.pos = { i_rod + 1, rem_ncpc - i, rem_bcew - (len - i) };
				metadata.num_ncpc = i;
			}
		}

		std::swap(memo_selection_[i_rod][rem_ncpc][rem_bcew], metadata);
		return memo = min_cost;
	}

	std::vector<int> Selector::Reconstruct() const
	{
		std::size_t i_rod = 0;
		auto rem_ncpc = rem_ncpc_;
		auto rem_bcew = rem_bcew_;

		const auto len = rods_.size();
		std::vector<int> min_ncpc(len);

		while (i_rod < len)
		{
			const auto next = memo_selection_[i_rod][rem_ncpc][rem_bcew];
			min_ncpc[i_rod] = next.num_ncpc;
			std::tie(i_rod, rem_ncpc, rem_bcew) = next.pos;
		}
		return min_ncpc;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int rem_ncpc;
	int rem_bcew;
	std::size_t num_rods;
	std::vector<int> rods;
	std::vector<std::vector<int>> cost_ncpc;
	std::vector<std::vector<int>> cost_bcew;

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

		uva10086::Selector selector(rods, cost_ncpc, cost_bcew, rem_ncpc, rem_bcew);
		auto[min_cost, selection] = selector.Select();
		std::cout << min_cost << std::endl;
		std::cout << selection.front();
		for (std::size_t i = 1; i < num_rods; ++i)
		{
			std::cout << " " << selection[i];
		}
		std::cout << std::endl << std::endl;
	}
	return 0;
}
