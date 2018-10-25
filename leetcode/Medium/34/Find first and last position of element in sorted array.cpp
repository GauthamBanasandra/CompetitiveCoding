#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class Solution {
public:
	static std::vector<int> searchRange(const std::vector<int>& numbers, int target);
};

std::vector<int> Solution::searchRange(const std::vector<int>& numbers, int target)
{
	const auto find_it = std::equal_range(numbers.begin(), numbers.end(), target);
	if (find_it.first == numbers.end() || *find_it.first != target)
	{
		return { -1, -1 };
	}

	const int i_begin = std::distance(numbers.begin(), find_it.first);
	const int i_end = std::distance(numbers.begin(), find_it.second) - 1;
	return { i_begin, i_end };
}

int main(int argc, char* argv[])
{
	auto result = Solution::searchRange({ 5 }, 5);
	std::cout << result[0] << "\t" << result[1] << std::endl;
	return 0;
}
