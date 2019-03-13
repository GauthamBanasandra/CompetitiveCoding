#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>
#include <ios>

namespace uva11703
{
	class Evaluator
	{
	public:
		Evaluator();

		long Evaluate(std::size_t i);

	private:
		std::vector<long> memo_;
	};

	Evaluator::Evaluator()
	{
		memo_.resize(1000000 + 1, -1);
	}

	long Evaluator::Evaluate(const std::size_t i)
	{
		assert(i < memo_.size());

		if (i == 0)
		{
			return 1;
		}

		auto& memo = memo_[i];
		if (memo != -1)
		{
			return memo;
		}

		const auto i_dbl = static_cast<long double>(i);

		const auto i_a = std::floor(i_dbl - std::sqrt(i_dbl));
		const auto a = Evaluate(static_cast<std::size_t>(i_a));

		const auto i_b = std::floor(std::log(i_dbl));
		const auto b = Evaluate(static_cast<std::size_t>(i_b));

		const auto sin_i = std::sin(i_dbl);
		const auto i_c = std::floor(i_dbl * sin_i * sin_i);
		const auto c = Evaluate(static_cast<std::size_t>(i_c));
		return memo = (a + b + c) % 1000000;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	long i;
	uva11703::Evaluator evaluator;

	while (std::cin >> i, i != -1)
	{
		std::cout << evaluator.Evaluate(i) << std::endl;
	}
	return 0;
}
