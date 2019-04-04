// WIP

#include <vector>
#include <string>
#include <stack>
#include <iostream>

class Palindrome
{
public:
	explicit Palindrome(const std::string& number);

	std::string GetNext();

private:
	std::pair<bool, const std::string*> Next(int i_digit, int prev_num,
		bool no_limit, std::stack<int>& verifier);
	int GetDigit(const int i_digit) const
	{
		return i_digit < static_cast<int>(number_.size()) ? number_[i_digit] - '0' : 0;
	}

	bool IsMirror(const int i_digit) const
	{
		return current_num_digits_ & 1 ? i_digit > current_num_digits_ / 2 : i_digit >= current_num_digits_ / 2;
	}
	bool IsMiddle(const int i_digit) const
	{
		return current_num_digits_ & 1 ? i_digit == current_num_digits_ / 2 : false;
	}

	const std::string& number_;
	static std::string largest_palindrome_;
	int current_num_digits_;
	std::vector<std::vector<std::vector<std::pair<bool, std::string>>>> memo_;
};

Palindrome::Palindrome(const std::string& number) : number_(number), current_num_digits_(0)
{
	auto item = std::make_pair(false, "");
	auto row = std::vector<std::pair<bool, std::string>>(2, item);
	auto table = std::vector<std::vector<std::pair<bool, std::string>>>(10, row);
	memo_.resize(1'000'000, table); // Grows to GB

	if (largest_palindrome_.empty())
	{
		largest_palindrome_.assign(10'000'000, '0');
		largest_palindrome_.front() = '1';
		largest_palindrome_.back() = '1';
	}
}

std::string Palindrome::largest_palindrome_;

std::string Palindrome::GetNext()
{
	std::stack<int> verifier;
	const auto num_digits = static_cast<int>(number_.size());

	for (auto i = num_digits - 1; i < 1'000'000; ++i)
	{
		const auto current_num = GetDigit(i);
		for (auto d = current_num; d <= 9; ++d)
		{
			verifier.push(d);
			const auto [is_possible, palindrome] = Next(i - 1, d,
				d > current_num, verifier);
			if (is_possible)
			{
				return *palindrome + std::to_string(d);
			}
		}
	}
	return largest_palindrome_;
}

std::pair<bool, const std::string*> Palindrome::Next(const int i_digit,
	const int prev_num, const bool no_limit, std::stack<int>& verifier)
{
	if (i_digit < 0)
	{
		return { false, nullptr };
	}

	auto& memo = memo_[i_digit][prev_num][no_limit ? 1 : 0];
	if (!memo.second.empty())
	{
		return std::make_pair(memo.first, &memo.second);
	}

	const auto limit = GetDigit(i_digit);

	if (IsMirror(i_digit))
	{
		const auto top = verifier.top();
		if (!(no_limit || top >= limit))
		{
			memo = { false, "-" };
			return std::make_pair(false, &memo.second);
		}

		verifier.pop();
		const auto [is_possible, palindrome] = Next(i_digit - 1, top,
			no_limit || top > limit, verifier);
		if (is_possible)
		{
			memo = { true, *palindrome + std::to_string(top) };
			return std::make_pair(true, &memo.second);
		}
		memo = { false, "-" };
		return std::make_pair(false, &memo.second);
	}

	for (auto d = no_limit ? 0 : limit; d <= 9; ++d)
	{
		if (!IsMiddle(i_digit))
		{
			verifier.push(d);
		}

		const auto [is_possible, palindrome] = Next(i_digit - 1, d,
			no_limit || d > limit, verifier);
		if (is_possible)
		{
			memo = { true, *palindrome + std::to_string(d) };
			return std::make_pair(true, &memo.second);
		}
	}
	return { false, nullptr };
}

int main(int argc, char* argv[])
{
	Palindrome palindrome("808");
	std::cout << palindrome.GetNext() << std::endl;
	return 0;
}
