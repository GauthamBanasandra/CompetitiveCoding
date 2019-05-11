#include <vector>
#include <map>

std::vector<int> GetOperands(const std::vector<int>& numbers, const int target)
{
	// Need to remember to use multimap here to handle the case when
	// numbers contain duplicate elements
	std::multimap<int, int> m;
	for (auto i = 0, len = static_cast<int>(numbers.size()); i < len; ++i)
	{
		m.emplace(numbers[i], i);
	}

	for (auto i = 0, len = static_cast<int>(numbers.size()); i < len; ++i)
	{
		const auto a = numbers[i];
		// Calling m.erase directly on the key will erase all occurrences of the
		// key. Thus we just want to pass only the iterator to one occurrence
		m.erase(m.find(a));
		const auto b = target - a;
		const auto find_it = m.find(b);
		if (find_it != m.end())
		{
			return { i, find_it->second };
		}
		m.emplace(a, i);
	}
	return{};
}

class Solution {
public:
	static std::vector<int> twoSum(std::vector<int>& nums, int target);
};

std::vector<int> Solution::twoSum(std::vector<int>& nums, int target)
{
	return GetOperands(nums, target);
}

int main(int argc, char* argv[])
{
	std::vector<int> nums{ 3, 3 };
	Solution::twoSum(nums, 6);
	return 0;
}
