#include <vector>
#include <limits>

int GetMaximumSubArraySum(const std::vector<int>& numbers)
{
	if (numbers.empty())
	{
		return 0;
	}

	// To handle the case when all the numbers are negative
	auto max_sum = std::numeric_limits<int>::min();
	auto sum = 0;
	for (const auto number : numbers)
	{
		sum += number;
		if (sum > max_sum)
		{
			max_sum = sum;
		}
		if (sum < 0)
		{
			sum = 0;
		}
	}
	return max_sum;
}

class Solution {
public:
	static int maxSubArray(std::vector<int>& nums);
};

int Solution::maxSubArray(std::vector<int>& nums)
{
	return GetMaximumSubArraySum(nums);
}

int main(int argc, char* argv[])
{
	return 0;
}
