#include <vector>
#include <algorithm>

std::vector<std::vector<int>> Merge(std::vector<std::vector<int>>& intervals)
{
	if (intervals.empty())
	{
		return {};
	}

	std::sort(intervals.begin(), intervals.end(),
		[](const std::vector<int> & a, const std::vector<int> & b)->bool
		{
			if (a.front() == b.front())
			{
				return a.back() > b.back();
			}
			return a.front() < b.front();
		});

	std::vector<std::vector<int>> merged;
	merged.reserve(intervals.size());
	merged.emplace_back(intervals.front());
	for (auto i = 1, len = static_cast<int>(intervals.size()); i < len; ++i)
	{
		auto& tail = merged.back();
		const auto& item = intervals[i];

		if (item.back() <= tail.back())
		{
			continue;
		}
		if (item.front() > tail.back())
		{
			merged.emplace_back(item);
			continue;
		}
		tail.back() = item.back();
	}
	return merged;
}

class Solution {
public:
	static std::vector<std::vector<int>> merge(
		std::vector<std::vector<int>>& intervals);
};

std::vector<std::vector<int>> Solution::merge(
	std::vector<std::vector<int>>& intervals)
{
	return Merge(intervals);
}

int main(int argc, char* argv[])
{
	return 0;
}
