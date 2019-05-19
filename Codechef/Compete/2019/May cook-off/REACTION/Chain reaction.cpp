#include <vector>
#include <iostream>

namespace may_cook_off_2019
{
	class Matrix
	{
	public:
		Matrix(const std::vector<std::vector<int>>& matrix,
			int num_rows, int num_columns);

		bool IsStable() const;

	private:
		bool IsOutside(const int x, const int y) const
		{
			return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
		}
		int CountValidAdjacentCells(const int x, const int y) const;

		const int num_rows_;
		const int num_columns_;
		const std::vector<std::vector<int>>& matrix_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> Matrix::directions_;

	Matrix::Matrix(const std::vector<std::vector<int>>& matrix,
		const int num_rows, const int num_columns) :
		num_rows_(num_rows), num_columns_(num_columns),
		matrix_(matrix)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		}
	}

	bool Matrix::IsStable() const
	{
		for (auto i = 0; i < num_rows_; ++i)
		{
			for (auto j = 0; j < num_columns_; ++j)
			{
				if (matrix_[i][j] >= CountValidAdjacentCells(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}

	int Matrix::CountValidAdjacentCells(const int x, const int y) const
	{
		auto count = 0;
		for (const auto& direction : directions_)
		{
			if (!IsOutside(x + direction.first, y + direction.second))
			{
				++count;
			}
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int num_rows;
	int num_columns;
	std::vector<std::vector<int>> matrix;

	std::cin >> t;
	while (t--)
	{
		std::cin >> num_rows >> num_columns;
		matrix.resize(num_rows);
		for (auto i = 0; i < num_rows; ++i)
		{
			matrix[i].resize(num_columns);
			for (auto j = 0; j < num_columns; ++j)
			{
				std::cin >> matrix[i][j];
			}
		}
		std::cout << (may_cook_off_2019::Matrix(matrix, num_rows, num_columns).IsStable() ? "Stable" : "Unstable") << std::endl;
	}
	return 0;
}
