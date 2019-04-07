#include <vector>
#include <string>
#include <iostream>
#include <ios>

using ll = long long;

class Number
{
public:
	Number(const std::string& number) : number_(number) {}

	int operator[](const std::size_t i) const { return number_[i] - '0'; }
	std::size_t Size() const { return number_.size(); }

private:
	const std::string& number_;
};

class Counter
{
public:
	explicit Counter(const std::string& number);

	ll CountNo9();

private:
	ll Count(std::size_t i_digit, int digit_sum, bool no_limit);

	const Number number_;
	std::vector<std::vector<std::vector<ll>>> memo_;
};

Counter::Counter(const std::string& number) : number_(number)
{
	// DP table structure - 
	// num_digits x max_value_of_a_digit(= 8) x can_current_digit_go_up_to_8
	memo_.resize(number_.Size(),
		std::vector<std::vector<ll>>(9,
			std::vector<ll>(2, -1)));
}

ll Counter::CountNo9()
{
	ll count = 0;
	for (auto i = 0; i <= number_[0]; ++i)
	{
		count += Count(1, i % 9, i < number_[0]);
	}
	return count;
}

// i_digit ->	The current digit
// digit_sum ->	Sum % 9 of the digits so far. Useful for checking if a number is divisible by 9
// no_limit ->	If digit i hasn't reached its limit(i.e. its digit value), it implies that all
//				the subsequent (i+1), (i+2) ... last_digit can loop over [0, 8]. Otherwise, they
//				can only loop only over [0, whatever_is_the_digit_limit]
ll Counter::Count(const std::size_t i_digit, const int digit_sum, const bool no_limit)
{
	if (i_digit >= number_.Size())
	{
		return digit_sum != 0 ? 1 : 0;
	}

	auto& memo = memo_[i_digit][digit_sum][no_limit ? 1 : 0];
	if (memo != -1)
	{
		return memo;
	}

	const auto limit = number_[i_digit];
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
	std::ios::sync_with_stdio(false);

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
