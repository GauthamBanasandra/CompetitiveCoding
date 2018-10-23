#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

class Solution {
public:
	static int search(std::vector<int>& numbers, int target);

private:
	static std::size_t GetPivotIndex(const std::vector<int> &numbers);
};

int Solution::search(std::vector<int>& numbers, const int target)
{
	const auto i_pivot = GetPivotIndex(numbers);
	auto pivot_it = numbers.begin();
	std::advance(pivot_it, i_pivot);

	const auto l_it = std::lower_bound(numbers.begin(), pivot_it, target);
	if (*l_it == target)
	{
		return std::distance(numbers.begin(), l_it);
	}

	return 0;
}

std::size_t Solution::GetPivotIndex(const std::vector<int>& numbers)
{
	assert(!numbers.empty());
	if (numbers.size() == 1)
	{
		return 0;
	}

	std::size_t l = 0, h = numbers.size() - 1;
	while (h - l != 1)
	{
		const auto m = (h + l) / 2;
		if (numbers[l] < numbers[m])
		{
			l = m;
		}
		else
		{
			h = m;
		}
	}
	return numbers[l] < numbers[h] ? h : l;
}

int main(int argc, char* argv[])
{
	const std::vector<int> numbers{ 0, 1, 2, 4, 5, 6, 7 };
	return 0;
}
