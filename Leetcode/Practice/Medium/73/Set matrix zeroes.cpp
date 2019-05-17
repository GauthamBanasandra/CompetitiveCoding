#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

class Matrix
{
public:
	explicit Matrix(std::vector<std::vector<int>>& matrix);

	void NullifyRowColumn() const;

private:
	std::tuple<bool, std::size_t, std::size_t> GetNonZeroRowColumn() const;
	void NullifyMarked(std::size_t i_marked_row, std::size_t i_marked_column) const;

	std::size_t num_rows_;
	std::size_t num_columns_;
	std::vector<std::vector<int>>& matrix_;
};

Matrix::Matrix(std::vector<std::vector<int>>& matrix) :matrix_(matrix)
{
	num_rows_ = matrix.size();
	if (!matrix_.empty())
	{
		num_columns_ = matrix_.front().size();
	}
}

void Matrix::NullifyRowColumn() const
{
	const auto& [is_possible, i_marking_row, i_marking_column] = GetNonZeroRowColumn();
	if (!is_possible)
	{
		for (auto& row : matrix_)
		{
			row.assign(num_columns_, 0);
		}
		return;
	}

	for (std::size_t i = 0; i < num_rows_; ++i)
	{
		if (i == i_marking_row)
		{
			continue;
		}

		for (std::size_t j = 0; j < num_columns_; ++j)
		{
			if (j == i_marking_column)
			{
				continue;
			}

			if (matrix_[i][j] == 0)
			{
				matrix_[i][i_marking_column] = matrix_[i_marking_row][j] = 0;
			}
		}
	}
	NullifyMarked(i_marking_row, i_marking_column);
}

std::tuple<bool, std::size_t, std::size_t> Matrix::GetNonZeroRowColumn() const
{
	auto is_possible = false;
	std::size_t i_row = 0;
	std::size_t i_column = 0;

	for (std::size_t i = 0; i < num_rows_; ++i)
	{
		const auto& row = matrix_[i];
		auto find_it = std::find(row.begin(), row.end(), 0);
		if (find_it == row.end())
		{
			is_possible = true;
			i_row = i;
			break;
		}
	}
	if (!is_possible)
	{
		return{ false, 0, 0 };
	}

	for (std::size_t i = 0; i < num_columns_; ++i)
	{
		is_possible = true;
		for (std::size_t j = 0; j < num_rows_; ++j)
		{
			if (matrix_[j][i] == 0)
			{
				is_possible = false;
				break;
			}
		}
		if (is_possible)
		{
			i_column = i;
			break;
		}
	}
	return{ is_possible, i_row, i_column };
}

void Matrix::NullifyMarked(const std::size_t i_marked_row,
	const std::size_t i_marked_column) const
{
	for (std::size_t i = 0; i < num_rows_; ++i)
	{
		if (matrix_[i][i_marked_column] == 0)
		{
			matrix_[i].assign(num_columns_, 0);
		}
	}

	for (std::size_t i = 0; i < num_columns_; ++i)
	{
		if (matrix_[i_marked_row][i] == 0)
		{
			for (std::size_t j = 0; j < num_rows_; ++j)
			{
				matrix_[j][i] = 0;
			}
		}
	}
}

class Solution
{
public:
	static void setZeroes(std::vector<std::vector<int>>& matrix);
};

void Solution::setZeroes(std::vector<std::vector<int>>& matrix)
{
	Matrix m(matrix);
	m.NullifyRowColumn();
}

int main(int argc, char* argv[])
{
	return 0;
}
