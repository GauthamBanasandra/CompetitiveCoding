// TLE

#include <vector>
#include <algorithm>
#include <iostream>

int GetMaxArea(const std::vector<int>& heights)
{
	auto max_area = 0;
	for (auto i = 0, len = static_cast<int>(heights.size()); i < len; ++i)
	{
		for (auto j = i + 1; j < len; ++j)
		{
			const auto area = std::min(heights[i], heights[j]) * (j - i);
			max_area = std::max(max_area, area);
		}
	}
	return max_area;
}

class Solution {
public:
	static int maxArea(std::vector<int>& height);
};

int Solution::maxArea(std::vector<int> & height)
{
	return GetMaxArea(height);
}

int main(int argc, char* argv[])
{
	std::vector<int> heights{ 1,8,6,2,5,4,8,3,7 };
	std::cout << Solution::maxArea(heights) << std::endl;
	return 0;
}
