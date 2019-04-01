// WIP

#include <vector>
#include <algorithm>
#include <iostream>

using ll = long long;

class Evaluator
{
public:
	explicit Evaluator(const std::vector<short> &number);

	ll Evaluate();

private:
	ll Evaluate(int i_digit, int prev_num, bool no_limit);

	const std::vector<short>& number_;
	std::vector<std::vector<std::vector<ll>>> memo_;
};

Evaluator::Evaluator(const std::vector<short>& number) : number_(number)
{
	memo_.resize(number_.size(),
		std::vector<std::vector<ll>>(10,
			std::vector<ll>(2, -1)));
}

ll Evaluator::Evaluate()
{
	ll max_product = 0;
	for (auto i = 0; i <= number_.front(); ++i)
	{
		const auto product = Evaluate(1, i, i < number_.front());
		max_product = std::max(max_product, product);
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
	for (auto i = 0; i <= (no_limit ? 9 : number_[i_digit]); ++i)
	{
		const auto product = Evaluate(i_digit + 1, i, i < number_[i_digit]);
		max_product = std::max(max_product, product);
	}
	return max_product * (i_digit == 1 && prev_num == 0 ? 1 : prev_num);
}

std::vector<short> GetDigits(ll number)
{
	std::vector<short> digits;
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
	ll number = 11;
	const auto digits = GetDigits(number);
	Evaluator evaluator(digits);
	std::cout << evaluator.Evaluate() << std::endl;
	return 0;
}
