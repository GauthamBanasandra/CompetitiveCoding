#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

using ll = long long;
class ChangeMaker
{
public:
	ChangeMaker(std::size_t max_value, std::size_t
	            max_coins);

	ll Count(const int rem) { return Count(1, rem); }
	ll RangeCount(int from, int to, int rem);

private:
	ll Count(int i, int rem);
	ll Count(int i, int n, int rem);

	const ll max_value_;
	std::vector<std::vector<ll>> memo_inf_;
	std::vector<std::vector<std::vector<ll>>> memo_fin_;
};

ChangeMaker::ChangeMaker(const std::size_t max_value, const std::size_t max_coins) :max_value_(static_cast<ll>(max_value))
{
	const std::vector<ll> row(max_value + 1, -1);
	memo_inf_.resize(max_value + 1, row);
	memo_fin_.resize(max_value + 1, std::vector<std::vector<ll>>(max_coins + 1, row));
}

ll ChangeMaker::Count(const int i, const int n, const int rem)
{
	if (i > max_value_ || rem < 0 || n < 0)
	{
		return 0;
	}
	if (rem == 0 && n == 0)
	{
		return 1;
	}

	auto &memo = memo_fin_[i][n][rem];
	if (memo != -1)
	{
		return memo;
	}
	return memo = Count(i + 1, n, rem) + Count(i, n - 1, rem - i);
}

ll ChangeMaker::RangeCount(const int from, const int to, const int rem)
{
	ll count = 0;
	for (auto n = from; n <= to; ++n)
	{
		count += Count(1, n, rem);
	}
	return count;
}

ll ChangeMaker::Count(const int i, const int rem)
{
	if (i > max_value_ || rem < 0)
	{
		return 0;
	}
	if (rem == 0)
	{
		return 1;
	}

	auto &memo = memo_inf_[static_cast<std::size_t>(i)][rem];
	if (memo != -1)
	{
		return memo;
	}

	return memo = Count(i + 1, rem) + Count(i, rem - i);
}

int main(int argc, char* argv[])
{
	std::string line;
	ll rem, a, b;
	const std::size_t max_value = 300;
	const std::size_t max_coins = 1000;
	ChangeMaker change_maker(max_value, max_coins);

	enum class InputType
	{
		kOne,
		kTwo,
		kThree
	};

	while (std::getline(std::cin, line), !std::cin.eof())
	{
		std::stringstream tokenizer(line);
		tokenizer >> rem;
		auto input_type = InputType::kOne;

		if (!tokenizer.eof())
		{
			tokenizer >> a;
			input_type = InputType::kTwo;
		}

		if (!tokenizer.eof())
		{
			tokenizer >> b;
			input_type = InputType::kThree;
		}

		switch (input_type) {
		case InputType::kOne:
			std::cout << change_maker.Count(rem) << std::endl;
			break;

		case InputType::kTwo:
			std::cout << change_maker.RangeCount(0, a, rem) << std::endl;
			break;

		case InputType::kThree:
			std::cout << change_maker.RangeCount(a, b, rem) << std::endl;
			break;

		default:
			assert(false);
		}
	}
	return 0;
}
