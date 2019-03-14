#include <vector>
#include <algorithm>
#include <iostream>
#include <ios>

class Maximizer
{
public:
	explicit Maximizer(const std::vector<int> &numbers, int max_num);

	long Maximize() { return Maximize(0, 0); }

private:
	long Maximize(std::size_t i_num, int prev_num);

	const std::vector<int> &numbers_;
	std::vector<std::vector<long>> memo_;
};

Maximizer::Maximizer(const std::vector<int>& numbers, const int max_num) : numbers_(numbers)
{
	memo_.resize(numbers_.size(),
		std::vector<long>(max_num + 1, -1));
}

long Maximizer::Maximize(const std::size_t i_num, const int prev_num)
{
	if (i_num >= numbers_.size())
	{
		return 0;
	}

	auto &memo = memo_[i_num][prev_num];
	if (memo != -1)
	{
		return memo;
	}

	const auto min_num = 1;
	auto lower_bound = Maximize(i_num + 1, min_num);
	if (i_num != 0)
	{
		lower_bound += std::abs(prev_num - min_num);
	}

	const auto max_num = numbers_[i_num];
	auto upper_bound = Maximize(i_num + 1, max_num);
	if (i_num != 0)
	{
		upper_bound += std::abs(prev_num - max_num);
	}
	return memo = std::max(lower_bound, upper_bound);
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t t, num_len;
	std::vector<int> numbers;

	std::cin >> t;
	while (t--)
	{
		std::cin >> num_len;
		numbers.resize(num_len);
		auto max_num = 0;
		for (std::size_t i = 0; i < num_len; ++i)
		{
			std::cin >> numbers[i];
			max_num = std::max(max_num, numbers[i]);
		}

		Maximizer maximizer(numbers, max_num);
		std::cout << maximizer.Maximize() << std::endl;
	}
	return 0;
}
