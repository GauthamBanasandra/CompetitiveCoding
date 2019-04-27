#include <vector>
#include <bitset>
#include <iostream>

namespace april_lunchtime_2019
{
	long GetMinimumSum(const std::vector<std::bitset<32>>& numbers)
	{
		long sum = 0;
		std::bitset<32> x;
		for (auto i = 0; i < 32; ++i)
		{
			auto num_zero = 0;
			auto num_one = 0;
			for (const auto& number : numbers)
			{
				++(number.test(i) ? num_one : num_zero);
			}

			if (num_one > num_zero)
			{
				x.set(i);
			}
		}

		for (const auto& number : numbers)
		{
			sum += (number ^ x).to_ulong();
		}
		return sum;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	long number;
	std::vector<std::bitset<32>> numbers;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		numbers.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> number;
			numbers[i] = number;
		}

		std::cout << april_lunchtime_2019::GetMinimumSum(numbers) << std::endl;
	}
	return 0;
}
