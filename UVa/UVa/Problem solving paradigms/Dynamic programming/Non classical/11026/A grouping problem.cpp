// WIP

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using ll = long long;

void Print(const std::vector<int> &elements);

class Group
{
public:
	Group(const std::vector<int> &numbers, std::size_t k);

	void Next();
	void GenerateCombinations();

private:
	void SelectNext(std::size_t i_memo, std::size_t i_start_num);
	ll Next(std::size_t i_memo, std::size_t i_start_num);

	std::vector<std::vector<ll>> memo_;
	std::vector<int> memo_selection_;
	const std::vector<int> &numbers_;
};

Group::Group(const std::vector<int>& numbers, const std::size_t k) :numbers_(numbers)
{
	memo_selection_.resize(k);
	memo_.resize(k, std::vector<ll>(numbers_.size(), -1));
}

void Group::Next()
{
	for (std::size_t i = 0, len = numbers_.size(); i < len; ++i)
	{
		std::cout << i << '\t' << Next(0, i) << std::endl;
	}
	std::cout << std::endl;
}

void Group::GenerateCombinations()
{
	for (std::size_t i = 0, len = numbers_.size(); i < len; ++i)
	{
		SelectNext(0, i);
	}
}

void Group::SelectNext(const std::size_t i_memo, const std::size_t i_start_num)
{
	if (i_memo >= memo_selection_.size() || i_start_num >= numbers_.size())
	{
		return;
	}

	memo_selection_[i_memo] = numbers_[i_start_num];
	if (i_memo == memo_selection_.size() - 1)
	{
		Print(memo_selection_);
	}

	for (auto i_num = i_start_num + 1, len = numbers_.size(); i_num < len; ++i_num)
	{
		SelectNext(i_memo + 1, i_num);
	}
}

ll Group::Next(const std::size_t i_memo, const std::size_t i_start_num)
{
	if (i_memo >= memo_.size() || i_start_num >= numbers_.size())
	{
		return -1;
	}

	auto &memo = memo_[i_memo][i_start_num];
	if (memo != -1)
	{
		return memo;
	}

	ll max_score = -1;
	for (auto i_num = i_start_num + 1, len = numbers_.size(); i_num < len; ++i_num)
	{
		const auto score = Next(i_memo + 1, i_num);
		max_score = std::max(max_score, score);
	}
	return memo = max_score != -1 ? max_score * numbers_[i_start_num] : numbers_[i_start_num];
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 1, 2, 3, 4 };

	Group group(numbers, 2);
	group.Next();
	group.GenerateCombinations();
	return 0;
}
