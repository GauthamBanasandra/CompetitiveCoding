// WA

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

namespace uva10400
{
	struct Data
	{
		Data() = default;
		Data(const std::size_t i, const std::size_t j, const char  opr) :i(i), j(j), opr(opr) {}

		std::size_t i{ 0 };
		std::size_t j{ 0 };
		char opr{ '\0' };
	};

	class ExpressionGenerator
	{
	public:
		ExpressionGenerator(const std::vector<int> &numbers, int target);

		std::string Generate();

	private:
		std::string Reconstruct() const;

		const int target_;
		const std::vector<int> &numbers_;
		std::vector<std::vector<short>> memo_;
		std::vector<std::vector<Data>> memo_expr_;
	};

	ExpressionGenerator::ExpressionGenerator(const std::vector<int>& numbers, const int target) : target_(target), numbers_(numbers)
	{
		memo_.resize(numbers_.size(), std::vector<short>(32000));
		memo_expr_.resize(numbers_.size(), std::vector<Data>(32000));
	}

	std::string ExpressionGenerator::Generate()
	{
		memo_[0][numbers_[0]] = 1;
		const auto len = numbers_.size();
		for (std::size_t i = 1ul; i < len; ++i)
		{
			for (std::size_t j = 0ul; j < 32000ul; ++j)
			{
				if (memo_[i - 1][j] == 0)
				{
					continue;
				}

				const auto number = static_cast<int>(j) * memo_[i - 1][j];
				const auto sum = number + numbers_[i];
				if (sum > -32000 && sum < 32000)
				{
					memo_[i][std::abs(sum)] = sum < 0 ? -1 : 1;
					memo_expr_[i][std::abs(sum)] = { i - 1, j, '+' };
				}

				const auto difference = number - numbers_[i];
				if (difference > -32000 && difference < 32000)
				{
					memo_[i][std::abs(difference)] = difference < 0 ? -1 : 1;
					memo_expr_[i][std::abs(difference)] = { i - 1, j, '-' };
				}

				const auto product = number * numbers_[i];
				if (product > -32000 && product < 32000)
				{
					memo_[i][std::abs(product)] = product < 0 ? -1 : 1;
					memo_expr_[i][std::abs(product)] = { i - 1, j, '*' };
				}

				const auto remainder = number % numbers_[i];
				if (remainder == 0)
				{
					const auto quotient = number / numbers_[i];
					if (quotient > -32000 && quotient < 32000)
					{
						memo_[i][std::abs(quotient)] = quotient < 0 ? -1 : 1;
						memo_expr_[i][std::abs(quotient)] = { i - 1, j, '/' };
					}
				}
			}
		}

		const auto target = memo_[len - 1][std::abs(target_)];
		if (target != 0 && (target > 0 && target_ > 0 || target < 0 && target_ < 0))
		{
			return Reconstruct();
		}
		return "NO EXPRESSION";
	}

	std::string ExpressionGenerator::Reconstruct() const
	{
		std::stringstream out;
		const auto len = numbers_.size();
		std::string operators;
		operators.reserve(len);

		Data data{ len - 1, static_cast<std::size_t>(std::abs(target_)), '\0' };
		do {
			data = memo_expr_[data.i][data.j];
			operators += data.opr;
		} while (data.i != 0);

		std::reverse(operators.begin(), operators.end());

		out << numbers_.front();
		for (std::size_t i = 0; i < len - 1; ++i)
		{
			out << operators[i] << numbers_[i + 1];
		}
		out << '=' << target_;
		return out.str();
	}
}

int main(int argc, char* argv[])
{
	std::size_t n, p;
	std::vector<int> numbers{ 1, 1 };
	auto target = 2000;

	std::cin >> n;
	while (n--)
	{
		std::cin >> p;
		numbers.resize(p);
		for (std::size_t i = 0; i < p; ++i)
		{
			std::cin >> numbers[i];
		}
		std::cin >> target;

		uva10400::ExpressionGenerator expression(numbers, target);
		std::cout << expression.Generate() << std::endl;
	}
	return 0;
}
