#include <vector>
#include <algorithm>
#include <iostream>

int GetMaxSatisfaction(const std::vector<int>& customers, const std::vector<int>& grumpy, const int x)
{
	auto satisfaction = 0;
	const auto len = static_cast<int>(customers.size());
	for (auto i = 0; i < len; ++i)
	{
		if (grumpy[i] == 0)
		{
			satisfaction += customers[i];
		}
	}

	for (auto j = 0; j < x; ++j)
	{
		if (grumpy[j] == 1)
		{
			satisfaction += customers[j];
		}
	}

	auto max_satisfaction = satisfaction;
	for (auto i = 0, j = x; j < len; ++i, ++j)
	{
		if (grumpy[j] == 1)
		{
			satisfaction += customers[j];
		}
		if (grumpy[i] == 1)
		{
			satisfaction -= customers[i];
		}
		max_satisfaction = std::max(max_satisfaction, satisfaction);
	}
	return max_satisfaction;
}

class Solution
{
public:
	static int maxSatisfied(std::vector<int>& customers,
		std::vector<int>& grumpy,
		int X);
};

int Solution::maxSatisfied(std::vector<int>& customers,
	std::vector<int>& grumpy, int X)
{
	return GetMaxSatisfaction(customers, grumpy, X);
}

int main(int argc, char* argv[])
{
	return 0;
}
