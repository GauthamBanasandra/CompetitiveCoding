#include <vector>
#include <algorithm>
#include <iostream>

namespace uva10912
{
	class Counter
	{
	public:
		Counter(std::size_t l, int s);

		long Count() { return Count(0, 0, rem_); }

	private:
		long Count(std::size_t i_letter, std::size_t prev_char, int rem);

		const std::size_t l_;
		const int rem_;
		std::vector<std::vector<std::vector<long>>> memo_;
	};

	// Initialization of l_ is the key to the solution
	// As per the problem, l_ could be as large as 10000, if this is considered, the complexity of the solution is L * 27 * S = 10^4 * 27 * 10^4 ~= 10^9
	// However, it's impossible to have such a large string while honoring the strictly increasing order
	// Thus, the longest possible string having strictly increasing order is of length 26 (a,b,c....z)
	Counter::Counter(const std::size_t l, const int s) :l_(std::min(l, static_cast<std::size_t>(27))), rem_(s)
	{
		memo_.resize(l_,
			std::vector<std::vector<long>>(27,
				std::vector<long>(rem_ + 1, -1)));
	}

	long Counter::Count(const std::size_t i_letter, const std::size_t prev_char, const int rem)
	{
		if (rem < 0 || prev_char > 26)
		{
			return 0;
		}

		if (i_letter >= l_)
		{
			if (rem == 0)
			{
				return 1;
			}
			return 0;
		}

		auto &memo = memo_[i_letter][prev_char][rem];
		if (memo != -1)
		{
			return memo;
		}

		long count = 0;
		for (auto i = prev_char + 1; i <= 26; ++i)
		{
			count += Count(i_letter + 1, i, rem - static_cast<int>(i));
		}
		return memo = count;
	}
}

int main(int argc, char* argv[])
{
	std::size_t t = 0;
	std::size_t l;
	int s;

	while (std::cin >> l >> s, l || s)
	{
		uva10912::Counter counter(l, s);
		std::cout << "Case " << ++t << ": " << counter.Count() << std::endl;
	}
	return 0;
}
