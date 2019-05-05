#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <functional>
#include <ios>

class Solution
{
public:
	static void nextPermutation(std::vector<int>& numbers);
};

void Solution::nextPermutation(std::vector<int>& numbers)
{
	auto it = numbers.rbegin();
	for (; it != numbers.rend(); ++it)
	{
		auto head_it = it.base();
		if (head_it == numbers.end())
		{
			continue;
		}

		if (*it < *head_it)
		{
			break;
		}
	}

	if (it == numbers.rend())
	{
		std::reverse(numbers.rbegin(), numbers.rend());
		return;
	}

	const auto find_it = std::upper_bound(numbers.rbegin(), it, *it, std::less<>());
	assert(find_it != numbers.rend());

	std::iter_swap(it, find_it);
	std::reverse(numbers.rbegin(), it);
}

void Print(const std::vector<int> & numbers)
{
	for (const auto number : numbers)
	{
		std::cout << number << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::vector<int> numbers{ 1, 2 };
	Solution::nextPermutation(numbers);
	Print(numbers);
	return 0;
}
