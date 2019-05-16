#include <vector>
#include <iostream>

class Counter
{
public:
	Counter(int num_rows, int num_columns);

	int Count() { return Count(0, 0); }

private:
	int Count(int x, int y);
	bool IsOutside(const int x, const int y) const
	{
		return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
	}
	bool HasReached(const int x, const int y) const
	{
		return x == num_rows_ - 1 && y == num_columns_ - 1;
	}

	const int num_rows_;
	const int num_columns_;
	std::vector<std::vector<int>> memo_;
	static std::vector<std::pair<int, int>> directions_;
};

std::vector<std::pair<int, int>> Counter::directions_;

Counter::Counter(const int num_rows, const int num_columns)
	:num_rows_(num_rows), num_columns_(num_columns)
{
	memo_.resize(num_rows_,
		std::vector<int>(num_columns_, -1));

	if (directions_.empty())
	{
		directions_ = { {1, 0}, {0, 1} };
	}
}

int Counter::Count(const int x, const int y)
{
	if (IsOutside(x, y))
	{
		return 0;
	}
	if (HasReached(x, y))
	{
		return 1;
	}

	auto& memo = memo_[x][y];
	if (memo != -1)
	{
		return memo;
	}

	auto count = 0;
	for (const auto& direction : directions_)
	{
		count += Count(x + direction.first, y + direction.second);
	}
	return  memo = count;
}

class Solution {
public:
	static int uniquePaths(int m, int n);
};

int Solution::uniquePaths(const int m, const int n)
{
	return Counter(m, n).Count();
}

int main(int argc, char* argv[])
{
	std::cout << Solution::uniquePaths(7, 3) << std::endl;
	return 0;
}
