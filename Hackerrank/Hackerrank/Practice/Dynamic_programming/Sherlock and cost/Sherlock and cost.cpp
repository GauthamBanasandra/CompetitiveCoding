#include <vector>
#include <algorithm>
#include <iostream>

class CostEstimator
{
public:
	explicit CostEstimator(const std::vector<int> &numbers);

	int Estimate();

private:
	std::vector<std::vector<int>> memo_;
	std::vector<std::vector<int>> possibilities_;
	const std::vector<int> &numbers_;
};

CostEstimator::CostEstimator(const std::vector<int>& numbers) :numbers_(numbers)
{
	memo_.resize(numbers_.size());
	possibilities_.resize(numbers_.size());
	for (std::size_t i = 0, len = memo_.size(); i < len; ++i)
	{
		memo_[i].resize(static_cast<std::size_t>(numbers_[i]));
		possibilities_[i].resize(static_cast<std::size_t>(numbers_[i]));
		for (auto j = 0; j < numbers_[i]; ++j)
		{
			possibilities_[i][j] = j + 1;
		}
	}
}

int CostEstimator::Estimate()
{
	for (std::size_t i = 1, len = memo_.size(); i < len; ++i)
	{
		for (std::size_t i_curr = 0, curr_len = possibilities_[i].size(); i_curr < curr_len; ++i_curr)
		{
			for (std::size_t i_prev = 0, prev_len = possibilities_[i - 1].size(); i_prev < prev_len; ++i_prev)
			{
				auto cost = std::abs(possibilities_[i][i_curr] - possibilities_[i - 1][i_prev]);
				cost += memo_[i - 1][i_prev];
				memo_[i][i_curr] = std::max(cost, memo_[i][i_curr]);
			}
		}
	}

	auto cost = 0;
	for (const auto value : memo_.back())
	{
		cost = std::max(cost, value);
	}
	return cost;
}

int main(int argc, char* argv[])
{
	std::size_t t, num_len;
	std::vector<int> numbers{ 10, 1, 10, 1, 10 };

	std::cin >> t;
	while (t--)
	{
		std::cin >> num_len;
		numbers.resize(num_len);
		for (std::size_t i = 0; i < num_len; ++i)
		{
			std::cin >> numbers[i];
		}

		CostEstimator estimator(numbers);
		std::cout << estimator.Estimate() << std::endl;
	}
	return 0;
}
