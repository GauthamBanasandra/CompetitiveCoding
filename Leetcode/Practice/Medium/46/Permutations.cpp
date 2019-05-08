#include <vector>
#include <queue>
#include <iostream>

class Generator
{
public:
	explicit Generator(const std::vector<int>& numbers);

	std::vector<std::vector<int>> AllPermutations();

private:
	void Next(int i_number, std::vector<std::vector<int>>& all);

	const std::vector<int>& numbers_;
	std::vector<int> current_;
	std::queue<int> order_;
};

Generator::Generator(const std::vector<int>& numbers) : numbers_(numbers)
{
	current_.reserve(numbers_.size());
	for (const auto number : numbers_)
	{
		order_.push(number);
	}
}

std::vector<std::vector<int>> Generator::AllPermutations()
{
	std::vector<std::vector<int>> all;
	Next(0, all);
	return all;
}

void Generator::Next(const int i_number, std::vector<std::vector<int>>& all)
{
	const auto len = static_cast<int>(numbers_.size());
	if (i_number >= len)
	{
		all.emplace_back(current_);
		return;
	}

	for (auto i = 0; i < len - i_number; ++i)
	{
		const auto number = order_.front();
		order_.pop();
		current_.emplace_back(number);
		Next(i_number + 1, all);
		order_.push(number);
		current_.pop_back();
	}
}

class Solution {
public:
	static std::vector<std::vector<int>> permute(std::vector<int>& numbers);
};

std::vector<std::vector<int>> Solution::permute(std::vector<int>& numbers)
{
	return Generator(numbers).AllPermutations();
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 1, 2, 3, 4 };
	auto count = 1;
	for (const auto& p : Solution::permute(numbers))
	{
		std::cout << count++ << " : ";
		auto separator = "";
		for (const auto number : p)
		{
			std::cout << separator << number;
			separator = " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
