#include <vector>
#include <algorithm>
#include <iostream>

int GetFirstMissingNumber(std::vector<int>& numbers)
{
	const auto len = static_cast<int>(numbers.size());
	// Just to simplify the solution, decrement each number
	// This avoids the 0-based and 1-based confusion
	for (auto& number : numbers)
	{
		// No point in decrementing a number that's already negative
		if (number >= 0)
		{
			--number;
		}
	}

	// The idea is that there must be a 0 at numbers[0], 1 at numbers[1] ...	
	for (auto i = 0; i < len; ++i)
	{
		// So, until the above criteria is met, we just keep swapping the
		// number at the current index i
		// Note that each time we swap, we put the target number at its right place
		// i.e. we put numbers[i] at index i
		// Thus, it runs in O(n)
		while (numbers[i] != i && numbers[i] >= 0)
		{
			const auto index = numbers[i];
			// The number at numbers[i] is supposed to go and sit at index i
			// However, if the array is too short for it, we just treat it as invalid since we can't
			// find a space for it, thus we mark it as -1 (invalid)			
			if (numbers[i] >= len ||
				// Another case is that of duplicates
				// If the number that we want to swap and its destination are the same
				// we just mark the current one as invalid because the destination already has numbers[i] == i
				numbers[index] == numbers[i])
			{
				numbers[i] = -1;
				break;
			}
			std::swap(numbers[i], numbers[index]);
		}
	}

	for (auto i = 0; i < len; ++i)
	{
		if (numbers[i] != i)
		{
			return i + 1;
		}
	}
	return len + 1;
}

class Solution {
public:
	static int firstMissingPositive(std::vector<int>& nums);
};

int Solution::firstMissingPositive(std::vector<int>& nums)
{
	return GetFirstMissingNumber(nums);
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ -1, -1, -1, -1 };
	std::cout << Solution::firstMissingPositive(numbers) << std::endl;
	return 0;
}
