#include <vector>
#include <string>
#include <iostream>

using ll = long long;

class Counter
{
public:
	explicit Counter(const std::string& number);

	ll CountNo9();

private:
	ll Count(int i_digit, int digit_sum, bool no_limit);
	int GetDigit(const std::size_t i) const { return number_[i] - '0'; }

	const std::string& number_;
	std::vector<std::vector<std::vector<ll>>> memo_;
};

Counter::Counter(const std::string& number) : number_(number)
{
	memo_.resize(number_.size(),
		std::vector<std::vector<ll>>(10,
			std::vector<ll>(2, -1)));
}

ll Counter::CountNo9()
{
	const auto limit = GetDigit(0);
	ll count = 0;
	for (auto i = 0; i <= limit; ++i)
	{
		count += Count(1, i % 9, i < limit);
	}
	return count;
}

ll Counter::Count(const int i_digit, const int digit_sum, const bool no_limit)
{
	if (i_digit >= static_cast<int>(number_.size()))
	{
		return digit_sum != 0 ? 1 : 0;
	}

	auto& memo = memo_[i_digit][digit_sum][no_limit ? 1 : 0];
	if (memo != -1)
	{
		return memo;
	}

	const auto limit = GetDigit(i_digit);
	ll count = 0;
	for (auto i = 0; i <= (no_limit ? 8 : limit); ++i)
	{
		count += Count(i_digit + 1, (digit_sum + i) % 9,
			no_limit || i < limit);
	}
	return memo = count;
}

int main(int argc, char* argv[])
{
	int t;
	std::string f;
	std::string l;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> f >> l;
		Counter f_counter(f);
		Counter l_counter(l);
		std::cout << "Case #" << i << ": " <<
			l_counter.CountNo9() - f_counter.CountNo9() + 1 << std::endl;
	}
	return 0;
}
