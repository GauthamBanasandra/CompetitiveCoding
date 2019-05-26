#include <vector>
#include <algorithm>

int CountDisplacements(const std::vector<int>& heights)
{
	auto heights_sorted(heights);
	std::sort(heights_sorted.begin(), heights_sorted.end());
	auto num_mismatch = 0;
	for (auto i = 0, len = static_cast<int>(heights.size()); i < len; ++i)
	{
		if (heights[i] != heights_sorted[i])
		{
			++num_mismatch;
		}
	}
	return num_mismatch;
}

class Solution
{
public:
	static int heightChecker(std::vector<int>& heights);
};

int Solution::heightChecker(std::vector<int>& heights)
{
	return CountDisplacements(heights);
}

int main(int argc, char* argv[])
{
	return 0;
}
