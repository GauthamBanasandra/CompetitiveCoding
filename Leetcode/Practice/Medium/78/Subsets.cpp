#include <vector>

class Selector
{
public:
	Selector(const std::vector<int>& numbers) : numbers_(numbers) {}

	std::vector<std::vector<int>> Select();

private:
	void Select(std::size_t i, std::vector<std::vector<int>>& all_subsets);

	const std::vector<int>& numbers_;
	std::vector<int> subset_;
};

std::vector<std::vector<int>> Selector::Select()
{
	std::vector<std::vector<int>> all_subsets;
	Select(0, all_subsets);
	return all_subsets;
}

void Selector::Select(std::size_t i,
	std::vector<std::vector<int>>& all_subsets)
{
	if (i >= numbers_.size())
	{
		all_subsets.emplace_back(subset_);
		return;
	}

	Select(i + 1, all_subsets);
	subset_.emplace_back(numbers_[i]);
	Select(i + 1, all_subsets);
	subset_.pop_back();
}

class Solution
{
public:
	static std::vector<std::vector<int>> subsets(
		std::vector<int>& nums);
};

std::vector<std::vector<int>> Solution::subsets(
	std::vector<int>& nums)
{
	return Selector(nums).Select();
}

int main(int argc, char* argv[])
{
	return 0;
}
