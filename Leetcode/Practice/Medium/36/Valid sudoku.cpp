#include <iostream>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <ios>

using Board = std::vector<std::vector<char>>;

class Solution
{
public:
	bool isValidSudoku(const Board &board);

private:
	bool IsValidSudoku(const Board &board);
	std::unordered_set<char>& GetGrid(const std::size_t i, const std::size_t j);

	std::unordered_set<char> row_;
	std::vector<std::unordered_set<char>> columns_;
	std::vector<std::unordered_set<char>> grids_;
};

bool Solution::isValidSudoku(const Board &board)
{
	columns_.resize(9);
	grids_.resize(9);
	return IsValidSudoku(board);
}

bool Solution::IsValidSudoku(const Board& board)
{
	for (std::size_t i = 0, row_len = board.size(); i < row_len; ++i)
	{
		for (std::size_t j = 0, column_len = board[i].size(); j < column_len; ++j)
		{
			auto c = board[i][j];
			if (c == '.')
			{
				continue;
			}
			if (c <'1' || c >'9')
			{
				return false;
			}

			if (row_.find(c) != row_.end())
			{
				return false;
			}
			row_.insert(c);

			auto &column = columns_[j];
			if (column.find(c) != column.end())
			{
				return false;
			}
			column.insert(c);

			auto &grid = GetGrid(i, j);
			if (grid.find(c) != grid.end())
			{
				return false;
			}
			grid.insert(c);
		}
		row_.clear();
	}
	return true;
}

std::unordered_set<char>& Solution::GetGrid(const std::size_t i, const std::size_t j)
{
	if (0 <= j && j <= 2)
	{
		if (0 <= i && i <= 2)
		{
			return grids_[0];
		}
		if (3 <= i && i <= 5)
		{
			return grids_[1];
		}
		if (6 <= i && i <= 8)
		{
			return grids_[2];
		}
	}
	if (3 <= j && j <= 5)
	{
		if (0 <= i && i <= 2)
		{
			return grids_[3];
		}
		if (3 <= i && i <= 5)
		{
			return grids_[4];
		}
		if (6 <= i && i <= 8)
		{
			return grids_[5];
		}
	}
	if (6 <= j && j <= 8)
	{
		if (0 <= i && i <= 2)
		{
			return grids_[6];
		}
		if (3 <= i && i <= 5)
		{
			return grids_[7];
		}
		if (6 <= i && i <= 8)
		{
			return grids_[8];
		}
	}
	assert(false);
	return grids_[0];
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	const Board board{
		{'.','.','.','.','5','.','.','1','.'},
		{'.','4','.','3','.','.','.','.','.'},
		{'.','.','.','.','.','3','.','.','1'},
		{'8','.','.','.','.','.','.','2','.'},
		{'.','.','2','.','7','.','.','.','.'},
		{'.','1','5','.','.','.','.','.','.'},
		{'.','.','.','.','.','2','.','.','.'},
		{'.','2','.','9','.','.','.','.','.'},
		{'.','.','4','.','.','.','.','.','.'}
	};

	std::cout << Solution().isValidSudoku(board) << std::endl;
	return 0;
}
