#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

using Matrix = std::vector<std::vector<int>>;
const auto infinity = std::numeric_limits<int>::max();

class PathFinder
{
public:
	explicit PathFinder(const Matrix &matrix);
	int Visit();

private:
	int Visit(long i_row, std::size_t i_column);
	inline std::size_t ResolveRow(long i_row) const;

	const Matrix &matrix_;
	std::size_t num_rows_;
	std::size_t num_columns_;
	Matrix memo_;
};

PathFinder::PathFinder(const Matrix& matrix) : matrix_(matrix)
{
	assert(!matrix_.empty() && !matrix_.front().empty());

	num_rows_ = matrix_.size();
	num_columns_ = matrix_.front().size();
	memo_.resize(num_rows_, std::vector<int>(num_columns_, -1));
}

int PathFinder::Visit()
{
	auto min_cost = infinity;
	for (std::size_t i_row = 0; i_row < num_rows_; ++i_row)
	{
		const auto cost = Visit(static_cast<long>(i_row), 0);
		if (cost < min_cost)
		{
			min_cost = cost;
		}
	}
	return min_cost;
}

int PathFinder::Visit(const long i_row, const std::size_t i_column)
{
	if (i_column >= num_columns_)
	{
		return infinity;
	}

	auto &memo = memo_[ResolveRow(i_row)][i_column];
	if (memo != -1)
	{
		return memo;
	}

	auto min_cost = infinity;
	const auto visit = [this, &min_cost]
	(const std::size_t i_row, const std::size_t i_column) -> void
	{
		const auto cost = Visit(i_row, i_column);
		if (cost < min_cost)
		{
			min_cost = cost;
		}
	};

	visit(ResolveRow(i_row - 1), i_column + 1);
	visit(ResolveRow(i_row), i_column + 1);
	visit(ResolveRow(i_row + 1), i_column + 1);
	return memo = (min_cost == infinity ? 0 : min_cost) +
		matrix_[static_cast<std::size_t>(i_row)][i_column];
}

std::size_t PathFinder::ResolveRow(const long i_row) const
{
	if (i_row < 0)
	{
		return num_rows_ - 1;
	}
	if (static_cast<std::size_t>(i_row) >= num_rows_)
	{
		return 0;
	}
	return i_row;
}

int main(int argc, char* argv[])
{
	const Matrix matrix = {
		 {3, 4, 1, 2, 8, 6},
		 {6, 1, 8, 2, 7, 4},
		 {5, 9, 3, 9, 9, 5},
		 {3, 7, 2, 8, 6, 4},
		 {8, 4, 1, 3, 2, 6},

		/*{3, 4, 1, 2, 8, 6},
		{6, 1, 8, 2, 7, 4},
		{5, 9, 3, 9, 9, 5},
		{8, 4, 1, 3, 2, 6},
		{3, 7, 2, 1, 2, 3},*/

		/*{9, 10},
		{9, 10},*/
	};

	PathFinder finder(matrix);
	std::cout << finder.Visit() << std::endl;
	return 0;
}
