#include <vector>
#include <iostream>

class Traversal
{
public:
	Traversal(int num_rows, int num_columns);
	std::vector<std::pair<int, int>> Traverse();

private:
	bool Jump(int row, int column, int rem);

	const int num_rows_;
	const int num_columns_;
	std::vector<std::vector<int>> grid_;
	std::vector<std::pair<int, int>> moves_;
};

Traversal::Traversal(const int num_rows, const int num_columns) :num_rows_(num_rows), num_columns_(num_columns)
{
	grid_.resize(num_rows_ + 1,
		std::vector<int>(num_columns_ + 1));
	moves_.reserve(num_rows_ * num_columns_);
}

std::vector<std::pair<int, int>> Traversal::Traverse()
{
	for (auto i = 1; i <= num_rows_; ++i)
	{
		for (auto j = 1; j <= num_columns_; ++j)
		{
			moves_.emplace_back(i, j);
			grid_[i][j] = 1;
			if (Jump(i, j, num_rows_ * num_columns_ - 1))
			{
				return moves_;
			}
			grid_[i][j] = 0;
			moves_.pop_back();
		}
	}
	return moves_;
}

bool Traversal::Jump(const int row, const int column, const int rem)
{
	if (rem == 0)
	{
		return true;
	}
	if (rem < 0)
	{
		return false;
	}

	for (auto i = 1; i <= num_rows_; ++i)
	{
		if (i == row)
		{
			continue;
		}
		for (auto j = 1; j <= num_columns_; ++j)
		{
			if (grid_[i][j] == 1 || row - column == i - j || row + column == i + j || j == column)
			{
				continue;
			}

			grid_[i][j] = 1;
			moves_.emplace_back(i, j);
			if (Jump(i, j, rem - 1))
			{
				return true;
			}
			grid_[i][j] = 0;
			moves_.pop_back();
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	int t;
	int num_rows;
	int num_columns;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> num_rows >> num_columns;
		Traversal traversal(num_rows, num_columns);
		auto moves = traversal.Traverse();

		std::cout << "Case #" << i << ": ";
		if (moves.empty())
		{
			std::cout << "IMPOSSIBLE" << std::endl;
		}
		else
		{
			std::cout << "POSSIBLE" << std::endl;
			for (const auto& move : moves)
			{
				std::cout << move.first << ' ' << move.second << std::endl;
			}
		}
	}
	return 0;
}
