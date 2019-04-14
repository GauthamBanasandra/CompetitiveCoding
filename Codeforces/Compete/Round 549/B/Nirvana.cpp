// TLE

#include <vector>
#include <algorithm>
#include <iostream>

using ll = long long;

class Evaluator
{
public:
	explicit Evaluator(const std::vector<int>& number);

	ll Evaluate();

private:
	ll Evaluate(int i_digit, int prev_num, bool no_limit);

	const std::vector<int>& number_;
	std::vector<std::vector<std::vector<ll>>> memo_;
};

Evaluator::Evaluator(const std::vector<int>& number) : number_(number)
{
	memo_.resize(number_.size(),
		std::vector<std::vector<ll>>(10,
			std::vector<ll>(2, -1)));
}

ll Evaluator::Evaluate()
{
	ll max_product = 0;
	for (auto i_digit = static_cast<int>(number_.size()) - 1; i_digit >= 0; --i_digit)
	{
		const auto limit = number_[i_digit];
		const auto no_limit = i_digit > 0;
		for (auto i = 1; i <= (no_limit ? 9 : limit); ++i)
		{
			const auto product = Evaluate(i_digit + 1,
				i, no_limit || i < limit);
			max_product = std::max(max_product, product);
		}
	}
	return max_product;
}

ll Evaluator::Evaluate(const int i_digit, const int prev_num, const bool no_limit)
{
	if (i_digit >= static_cast<int>(number_.size()))
	{
		return prev_num;
	}

	auto& memo = memo_[i_digit][prev_num][no_limit ? 1 : 0];
	if (memo != -1)
	{
		return memo;
	}

	ll max_product = 0;
	const auto limit = number_[i_digit];
	for (auto i = 1; i <= (no_limit ? 9 : limit); ++i)
	{
		const auto product = Evaluate(i_digit + 1,
			i, no_limit || i < limit);
		max_product = std::max(max_product, product);
	}
	return max_product * prev_num;
}

std::vector<int> GetDigits(ll number)
{
	std::vector<int> digits;
	while (number != 0)
	{
		digits.emplace_back(static_cast<short>(number % 10));
		number /= 10;
	}
	std::reverse(digits.begin(), digits.end());
	return digits;
}

int main(int argc, char* argv[])
{
	ll number = 100000000;
	const auto digits = GetDigits(number);
	Evaluator evaluator(digits);
	std::cout << evaluator.Evaluate() << std::endl;
	return 0;
}
