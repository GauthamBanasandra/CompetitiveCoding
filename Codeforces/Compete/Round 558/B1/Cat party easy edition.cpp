// WIP

#include <vector>
#include <unordered_set>
#include <iostream>
#include <cassert>
#include <cmath>

int GetMaximumStreak(const std::vector<int>& numbers)
{
	std::vector<int> frequency(11);
	for (const auto number : numbers)
	{
		++frequency[number];
	}

	const auto is_valid_streak = [&frequency]()->bool
	{
		auto min_f = 1000000;
		auto max_f = 0;
		for (const auto f : frequency)
		{
			if (f > max_f)
			{
				max_f = f;
			}
			if (f < min_f)
			{
				min_f = f;
			}
		}


	};

	for (auto streak = static_cast<int>(numbers.size()); streak > 0; --streak)
	{
		if (is_valid_streak())
		{
			return streak;
		}
		--frequency[numbers[streak - 1]];
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int n;
	std::cin >> n;

	std::vector<int> numbers(n);
	for (auto i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}
	std::cout << GetMaximumStreak(numbers) << std::endl;
	return 0;
}
