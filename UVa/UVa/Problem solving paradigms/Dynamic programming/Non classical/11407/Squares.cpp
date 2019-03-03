#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cassert>

namespace uva11407
{
	const auto infinity = std::numeric_limits<int>::max();

	class Counter
	{
	public:
		Counter();

		long Count(int rem) const;

	private:
		static const std::size_t max_square{ 10000 };
		static std::vector<long> memo_;
		static std::vector<int> squares_;
	};

	std::vector<long> Counter::memo_;
	std::vector<int> Counter::squares_;

	Counter::Counter()
	{
		if (!memo_.empty())
		{
			return;
		}

		memo_.resize(max_square + 1, -1);
		squares_.reserve(100);
		for (auto i = 1; i <= 100; ++i)
		{
			squares_.emplace_back(i * i);
		}
	}

	long Counter::Count(const int rem) const
	{
		if (rem < 0)
		{
			return infinity;
		}

		if (rem == 0)
		{
			return 0;
		}

		auto &memo = memo_[rem];
		if (memo != -1)
		{
			return memo;
		}

		long min_count = infinity;
		for (const auto& square : squares_)
		{
			const auto count = Count(rem - square);
			if (count == infinity)
			{
				break;
			}

			min_count = std::min(min_count, count + 1);
		}
		assert(min_count != infinity);
		return memo = min_count;
	}
}

int main(int argc, char* argv[])
{
	std::size_t t;
	int n;
	uva11407::Counter counter;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		std::cout << counter.Count(n) << std::endl;
	}
	return 0;
}
