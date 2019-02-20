#include <vector>
#include <iostream>
#include <ios>

namespace round540
{
	class Counter
	{
	public:
		explicit Counter(const std::vector<int> &candies);

		int GoodCandies() const;

	private:
		long RangeSum(long i_start, long i_end) const;

		long i_last_even_;
		long i_last_odd_;
		std::vector<long> cumulative_sum_;
	};

	Counter::Counter(const std::vector<int>& candies)
	{
		const auto len = candies.size();
		cumulative_sum_.resize(len);

		for (std::size_t i = 0; i < len; ++i)
		{
			if (i == 0 || i == 1)
			{
				cumulative_sum_[i] = candies[i];
				continue;
			}

			cumulative_sum_[i] = candies[i] + cumulative_sum_[i - 2];
		}

		if (len <= 1)
		{
			return;
		}

		i_last_even_ = len - (len & 1 ? 1 : 2);
		i_last_odd_ = len - (len & 1 ? 2 : 1);
	}

	int Counter::GoodCandies() const
	{
		auto num_good_candies = 0;
		const auto len = static_cast<long>(cumulative_sum_.size());
		if (len == 1)
		{
			return 1;
		}

		for (long i = 0; i < len; ++i)
		{
			long odd = 0, even = 0;
			if (i & 1)
			{
				odd = RangeSum(1, i - 2);
				even = RangeSum(0, i - 1);
				odd += RangeSum(i + 1, i_last_even_);
				even += RangeSum(i + 2, i_last_odd_);
			}
			else
			{
				odd = RangeSum(1, i - 1);
				even = RangeSum(0, i - 2);
				odd += RangeSum(i + 2, i_last_even_);
				even += RangeSum(i + 1, i_last_odd_);
			}

			num_good_candies = odd == even ? num_good_candies + 1 : num_good_candies;
		}
		return num_good_candies;
	}

	long Counter::RangeSum(const long i_start, const long i_end) const
	{
		const auto len = static_cast<long>(cumulative_sum_.size());
		if (i_start < 0 || i_end < 0 ||
			i_start >= len || i_end >= len ||
			i_end < i_start)
		{
			return 0;
		}

		const auto subtrahend = i_start - 2 < 0 ? 0l : cumulative_sum_[i_start - 2];
		return cumulative_sum_[i_end] - subtrahend;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t n;
	std::vector<int> candies;

	std::cin >> n;
	candies.resize(n);
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> candies[i];
	}

	round540::Counter counter(candies);
	std::cout << counter.GoodCandies() << std::endl;
	return 0;
}
