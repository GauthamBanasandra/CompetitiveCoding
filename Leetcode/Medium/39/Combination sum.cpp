// TLE

#include <vector>
#include <iostream>

class Generator
{
public:
	explicit Generator(const std::vector<int>& candidates);

	std::vector<std::vector<int>> Generate(int target);

private:
	void Next(std::size_t i, int rem, std::vector<std::vector<int>>& parts);

	const std::vector<int>& candidates_;
	std::vector<int> current_;
};

Generator::Generator(const std::vector<int>& candidates) :candidates_(candidates)
{
	current_.reserve(candidates_.size());
}

std::vector<std::vector<int>> Generator::Generate(const int target)
{
	std::vector<std::vector<int>> parts;
	Next(0, target, parts);
	return parts;
}

void Generator::Next(const std::size_t i, const int rem,
	std::vector<std::vector<int>>& parts)
{
	if (i >= candidates_.size())
	{
		if (rem == 0)
		{
			parts.emplace_back(current_);
		}
		return;
	}

	Next(i + 1, rem, parts);
	current_.emplace_back(candidates_[i]);
	if (rem - candidates_[i] >= 0)
	{
		Next(i, rem - candidates_[i], parts);
	}
	else
	{
		Next(i + 1, rem - candidates_[i], parts);
	}
	current_.pop_back();
}

class Solution {
public:
	static std::vector<std::vector<int>> combinationSum(
		std::vector<int>& candidates, int target);
};

std::vector<std::vector<int>> Solution::combinationSum(
	std::vector<int>& candidates, const int target)
{
	Generator generator(candidates);
	return generator.Generate(target);
}

int main(int argc, char* argv[])
{
	std::vector<int> candidates{ 21, 46, 35, 20, 44, 31, 29, 23, 45, 37, 33, 34, 39, 42, 24, 40, 41, 26, 22, 38, 36, 27, 25, 49, 48, 43 };
	auto solution = Solution().combinationSum(candidates, 71);
	for (const auto& row : solution)
	{
		auto separator = "";
		for (const auto item : row)
		{
			std::cout << separator << item;
			separator = " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
