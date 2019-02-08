#include <iostream>
#include <vector>
#include <ios>

class Numbers
{
public:
	Numbers(const std::vector<int> &numbers, std::size_t k);

	bool IsDivisible();

private:
	long Mod(long n) const;

	const std::size_t k_;
	const std::vector<int> &numbers_;
	std::vector<std::vector<short>> memo_;
};

Numbers::Numbers(const std::vector<int>& numbers, const std::size_t k) :k_(k), numbers_(numbers)
{
	memo_.resize(numbers_.size(), std::vector<short>(k_));
}

bool Numbers::IsDivisible()
{
	memo_[0][Mod(numbers_[0])] = 1;
	const auto len = numbers_.size();
	for (std::size_t i = 1ul; i < len; ++i)
	{
		for (auto j = 0l; j < static_cast<long>(k_); ++j)
		{
			if (memo_[i - 1][j] == 0)
			{
				continue;
			}

			const auto add = j + numbers_[i];
			const auto sub = j - numbers_[i];
			const auto i_add = Mod(add);
			const auto i_sub = Mod(sub);
			memo_[i][i_add] = memo_[i][i_sub] = 1;
		}
	}
	return memo_[len - 1][0] == 1;
}

long Numbers::Mod(long n) const
{
	const auto q = std::abs(n) / k_ + 1;
	n += q * k_;
	return n % static_cast<long>(k_);
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t m, n, k;
	std::vector<int> nums;

	std::cin >> m;
	while (m--)
	{
		std::cin >> n >> k;
		nums.resize(n);
		for (std::size_t i = 0ul; i < n; ++i)
		{
			std::cin >> nums[i];
		}

		Numbers numbers(nums, k);
		std::cout << (numbers.IsDivisible() ? "Divisible" : "Not divisible") << std::endl;
	}
	return 0;
}
