#include <vector>

int RemoveDuplicates(std::vector<int>& numbers)
{
	if (numbers.empty())
	{
		return 0;
	}

	auto i_wall = 1;
	for (auto i = 0, len = static_cast<int>(numbers.size()); i < len - 1; ++i)
	{
		if (numbers[i] == numbers[i + 1])
		{
			continue;
		}

		numbers[i_wall++] = numbers[i + 1];
	}
	return i_wall;
}

class Solution {
public:
	static int removeDuplicates(std::vector<int>& nums);
};

int Solution::removeDuplicates(std::vector<int>& nums)
{
	return RemoveDuplicates(nums);
}

int main(int argc, char* argv[])
{
	return 0;
}
