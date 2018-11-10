// WA
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using ll = long long;
using ull = unsigned long long;

struct CountInfo
{
	CountInfo() : num_same(0), num_not_same(0) {}

	ull num_same;
	ull num_not_same;
};

class Sequence
{
public:
	explicit Sequence(std::vector<int> numbers);

	ull CountGoodMedians() const;

private:
	CountInfo CountLeft(ll i, int number) const;
	CountInfo CountRight(std::size_t i, int number) const;

	std::vector<int> numbers_;
};

Sequence::Sequence(std::vector<int> numbers) :numbers_(std::move(numbers))
{
	std::sort(numbers_.begin(), numbers_.end());
}

ull Sequence::CountGoodMedians() const
{
	assert(!numbers_.empty());

	ull count = 0;
	for (std::size_t i = 0, penultimate_len = numbers_.size() - 1; i < penultimate_len; ++i)
	{
		const auto number = numbers_[i];
		if (number != numbers_[i + 1])
		{
			continue;
		}

		const auto left_info = CountLeft(i, number);
		const auto right_info = CountRight(i + 1, number);
		count += left_info.num_same + right_info.num_same;
	}
	return count;
}

CountInfo Sequence::CountLeft(ll i, const int number) const
{
	assert(i < numbers_.size());

	CountInfo info;
	for (--i; i > -1; --i)
	{
		if (number == numbers_[i])
		{
			++info.num_same;
		}
		else
		{
			++info.num_not_same;
		}
	}
	return info;
}

CountInfo Sequence::CountRight(std::size_t i, const int number) const
{
	assert(i < numbers_.size());

	CountInfo info;
	for (++i; i < numbers_.size(); ++i)
	{
		if (number == numbers_[i])
		{
			++info.num_same;
		}
		else
		{
			++info.num_not_same;
		}
	}
	return info;
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 2, 3, 4, 3, 3, 0, 9, 8, 7, 1, 1 };
	Sequence sequence(numbers);
	std::cout << sequence.CountGoodMedians() << std::endl;
	return 0;
}
