#include <vector>
#include <iostream>
#include <ios>

namespace uva10721
{
	using ll = long long;

	class Counter
	{
	public:
		Counter(std::size_t n, std::size_t k, std::size_t m);

		ll Count() { return Count(1, true, 1, 1); }

	private:
		ll Count(std::size_t i_bar, bool is_prev_black, std::size_t k, std::size_t m);

		const std::size_t n_;
		const std::size_t k_;
		const std::size_t m_;
		std::vector<std::vector<std::vector<std::vector<ll>>>> memo_;
	};

	Counter::Counter(const std::size_t n, const std::size_t k, const std::size_t m) : n_(n), k_(k), m_(m)
	{
		memo_.resize(n_,
		             std::vector<std::vector<std::vector<ll>>>(2,
		                                                       std::vector<std::vector<ll>>(k_ + 1,
		                                                                                    std::vector<ll>(m_ + 1, -1))));
	}

	ll Counter::Count(const std::size_t i_bar, const bool is_prev_black, const std::size_t k, const std::size_t m)
	{
		if (m > m_ || k > k_)
		{
			return 0;
		}

		if (i_bar >= n_)
		{
			if (k == k_)
			{
				return 1;
			}
			return 0;
		}

		auto &memo = memo_[i_bar][is_prev_black ? 1 : 0][k][m];
		if (memo != -1)
		{
			return memo;
		}

		const auto white = Count(
			i_bar + 1,
			false,
			k + (is_prev_black ? 1 : 0),
			!is_prev_black ? m + 1 : 1);

		const auto black = Count(
			i_bar + 1,
			true,
			k + (!is_prev_black ? 1 : 0),
			is_prev_black ? m + 1 : 1);
		return memo = white + black;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t n;
	std::size_t k;
	std::size_t m;

	while (std::cin >> n >> k >> m, !std::cin.eof())
	{
		uva10721::Counter counter(n, k, m);
		std::cout << counter.Count() << std::endl;
	}
	return 0;
}
