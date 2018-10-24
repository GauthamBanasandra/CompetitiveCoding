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
	if (numbers.empty())
	{
		return -1;
	}

	const auto i_pivot = GetPivotIndex(numbers);
	auto pivot_end_it = numbers.begin();
	std::advance(pivot_end_it, i_pivot + 1);

	auto find_it = std::lower_bound(numbers.begin(), pivot_end_it, target);
	if (find_it == numbers.end())
	{
		return -1;
	}
	if (*find_it == target)
	{
		return std::distance(numbers.begin(), find_it);
	}
	if (pivot_end_it == numbers.end())
	{
		return -1;
	}
	find_it = std::lower_bound(pivot_end_it, numbers.end(), target);
	if (find_it == numbers.end() || *find_it != target)
	{
		return -1;
	}
	return std::distance(numbers.begin(), find_it);
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
	std::vector<int> numbers{ 8 };
	std::cout << Solution::search(numbers, 8) << std::endl;
	return 0;
}
