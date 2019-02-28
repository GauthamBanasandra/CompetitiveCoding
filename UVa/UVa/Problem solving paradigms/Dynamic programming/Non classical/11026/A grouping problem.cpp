// WIP

#include <vector>
#include <iostream>

void Print(const std::vector<int> &elements);

class Group
{
public:
	Group(const std::vector<int> &numbers, std::size_t k);

	void Next() { Next(0, 0); }

private:
	void Next(std::size_t i_memo, std::size_t start_num);

	std::vector<int> memo_;
	const std::vector<int> &numbers_;
};

Group::Group(const std::vector<int>& numbers, const std::size_t k) :numbers_(numbers)
{
	memo_.resize(k);
}

void Group::Next(const std::size_t i_memo, const std::size_t start_num)
{
	if (i_memo >= memo_.size() || start_num >= numbers_.size())
	{
		return;
	}

	if (i_memo == memo_.size() - 1)
	{
		Print(memo_);
		return;
	}

	memo_[i_memo] = numbers_[start_num];
	for (auto i_num = start_num, len = numbers_.size(); i_num < len; ++i_num)
	{
		Next(i_memo + 1, i_num + 1);
	}
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 1, 2, 3, 4 };

	Group group(numbers, 2);
	group.Next();
	return 0;
}
