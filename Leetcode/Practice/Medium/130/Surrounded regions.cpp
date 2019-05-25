#include <vector>

class Matrix
{
public:
	explicit Matrix(std::vector<std::vector<char>>& matrix);

	void Capture() const;

private:
	void Fill(int x, int y) const;
	void Replace() const;
	bool IsOutside(const int x, const int y) const
	{
		return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
	}

	int num_rows_{ 0 };
	int num_columns_{ 0 };
	std::vector<std::vector<char>>& matrix_;
	static std::vector<std::pair<int, int>> directions_;
};

std::vector<std::pair<int, int>> Matrix::directions_;

Matrix::Matrix(std::vector<std::vector<char>>& matrix) : matrix_(matrix)
{
	num_rows_ = static_cast<int>(matrix_.size());
	if (!matrix_.empty())
	{
		num_columns_ = static_cast<int>(matrix_.front().size());
	}
	if (directions_.empty())
	{
		directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	}
}

void Matrix::Capture() const
{
	if (matrix_.empty())
	{
		return;
	}

	for (auto i = 0; i < num_columns_; ++i)
	{
		Fill(0, i);
		Fill(num_rows_ - 1, i);
	}
	for (auto i = 0; i < num_rows_; ++i)
	{
		Fill(i, 0);
		Fill(i, num_columns_ - 1);
	}

	Replace();
}

void Matrix::Fill(const int x, const int y) const
{
	if (IsOutside(x, y) || matrix_[x][y] != 'O')
	{
		return;
	}

	matrix_[x][y] = 'a';
	for (const auto& direction : directions_)
	{
		Fill(x + direction.first, y + direction.second);
	}
}

void Matrix::Replace() const
{
	for (auto i = 0; i < num_rows_; ++i)
	{
		for (auto j = 0; j < num_columns_; ++j)
		{
			if (matrix_[i][j] == 'a')
			{
				matrix_[i][j] = 'O';
			}
			else if (matrix_[i][j] == 'O')
			{
				matrix_[i][j] = 'X';
			}
		}
	}
}

class Solution
{
public:
	static void
		solve(std::vector<std::vector<char>>& board);
};

void Solution::solve(std::vector<std::vector<char>>& board)
{
	Matrix(board).Capture();
}

int main(int argc, char* argv[])
{
	return 0;
}
