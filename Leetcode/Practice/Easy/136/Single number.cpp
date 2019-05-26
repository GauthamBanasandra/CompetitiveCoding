#include <vector>

int GetSingleNumber(const std::vector<int>& numbers)
{
	auto single_num = 0;
	for (const auto number : numbers)
	{
		single_num ^= number;
	}
	return single_num;
}

class Solution
{
public:
	static int singleNumber(std::vector<int>& nums);
};

int Solution::singleNumber(std::vector<int>& nums)
{
	return GetSingleNumber(nums);
}

int main(int argc, char* argv[])
{
	return 0;
}
