#include <vector>

int IsReachable(const std::vector<int>& numbers)
{
	const auto len = static_cast<int>(numbers.size());
	auto i_reachable = len - 1;

	for (auto i = len - 2; i >= 0; --i)
	{
		if (numbers[i] + i >= i_reachable)
		{
			i_reachable = i;
		}
	}
	return  i_reachable == 0;
}

class Solution {
public:
	static bool canJump(std::vector<int>& nums);
};

bool Solution::canJump(std::vector<int>& nums)
{
	return IsReachable(nums);
}

int main(int argc, char* argv[])
{
	return 0;
}
