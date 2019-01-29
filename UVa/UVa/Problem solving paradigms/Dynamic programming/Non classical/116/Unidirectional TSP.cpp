#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits>
#include <cassert>

using Matrix = std::vector<std::vector<int>>;
using Pos = std::pair<std::size_t, std::size_t>;
const auto infinity = std::numeric_limits<int>::max();

class PathFinder
{
public:
	explicit PathFinder(const Matrix &matrix);
	int Visit();

private:
	int Visit(long i_row, std::size_t i_column);
	inline std::size_t ResolveRow(long i_row) const;
	std::vector<std::string> Reconstruct(std::size_t i_row) const;
	static void Print(const std::vector<std::string> &nodes);

	const Matrix &matrix_;
	std::size_t num_rows_;
	std::size_t num_columns_;
	Matrix memo_;
	std::vector<std::vector<Pos>> memo_visit_;
};

PathFinder::PathFinder(const Matrix& matrix) : matrix_(matrix)
{
	assert(!matrix_.empty() && !matrix_.front().empty());

	num_rows_ = matrix_.size();
	num_columns_ = matrix_.front().size();
	memo_.resize(num_rows_, std::vector<int>(num_columns_, -1));
	memo_visit_.resize(num_rows_, std::vector<Pos>(num_columns_));
}

int PathFinder::Visit()
{
	auto min_cost = infinity;
	std::size_t min_row = 0;
	for (std::size_t i_row = 0; i_row < num_rows_; ++i_row)
	{
		const auto cost = Visit(static_cast<long>(i_row), 0);
		if (cost == min_cost)
		{
			min_row = Reconstruct(i_row) < Reconstruct(min_row) ? i_row : min_row;
		}
		else if (cost < min_cost)
		{
			min_cost = cost;
			min_row = i_row;
		}
	}
	Print(Reconstruct(min_row));
	assert(min_cost != infinity);
	return min_cost;
}

int PathFinder::Visit(const long i_row, const std::size_t i_column)
{
	if (i_column == num_columns_ - 1)
	{
		return matrix_[i_row][i_column];
	}

	auto &memo = memo_[i_row][i_column];
	if (memo != -1)
	{
		return memo;
	}

	auto min_cost = infinity;
	std::size_t min_row = 0, min_column = 0;
	const auto visit = [this, &min_cost, &min_row, &min_column]
	(const std::size_t i_row, const std::size_t i_column) -> void
	{
		const auto cost = Visit(i_row, i_column);
		if (cost < min_cost)
		{
			min_cost = cost;
			min_row = i_row;
			min_column = i_column;
		}
	};

	visit(ResolveRow(i_row - 1), i_column + 1);
	visit(ResolveRow(i_row), i_column + 1);
	visit(ResolveRow(i_row + 1), i_column + 1);
	assert(min_cost != infinity);

	memo_visit_[i_row][i_column] = { min_row, min_column };
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

std::vector<std::string> PathFinder::Reconstruct(std::size_t i_row) const
{
	std::vector<std::string> nodes;
	nodes.reserve(num_columns_);
	std::size_t i_column = 0;
	while (i_column < num_columns_)
	{
		nodes.emplace_back(std::to_string(i_row + 1));
		if (i_column == num_columns_ - 1)
		{
			break;
		}
		const auto &[next_row, next_column] = memo_visit_[i_row][i_column];
		i_row = next_row;
		i_column = next_column;
	}
	return nodes;
}

void PathFinder::Print(const std::vector<std::string>& nodes)
{
	for (const auto& node : nodes)
	{
		std::cout << node << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	Matrix matrix = {
		{3, 4, 1, 2, 8, 6},
		{6, 1, 8, 2, 7, 4},
		{5, 9, 3, 9, 9, 5},
		{8, 4, 1, 3, 2, 6},
		{3, 7, 2, 8, 6, 4},

		/*{3, 4, 1, 2, 8, 6},
		{6, 1, 8, 2, 7, 4},
		{5, 9, 3, 9, 9, 5},
		{8, 4, 1, 3, 2, 6},
		{3, 7, 2, 1, 2, 3},*/

		/*{9, 10},
		{9, 10},*/
	};
	std::size_t num_rows = 0, num_columns = 0;

	while (std::cin >> num_rows >> num_columns, !std::cin.eof())
	{
		matrix.resize(num_rows);
		for (std::size_t i = 0; i < num_rows; ++i)
		{
			matrix[i].resize(num_columns);
			for (std::size_t j = 0; j < num_columns; ++j)
			{
				std::cin >> matrix[i][j];
			}
		}

		PathFinder finder(matrix);
		std::cout << finder.Visit() << std::endl;
	}
	/*PathFinder finder(matrix);
	std::cout << finder.Visit() << std::endl;*/
	return 0;
}
