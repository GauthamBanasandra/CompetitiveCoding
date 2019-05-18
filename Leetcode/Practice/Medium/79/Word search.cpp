#include <string>
#include <vector>

class Searcher
{
public:
	explicit Searcher(std::vector<std::vector<char>>& board,
		const std::string& target);

	bool Search() const;

private:
	bool Search(int i_target, int x, int y) const;
	bool IsOutside(const int x, const int y) const
	{
		return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
	}

	int num_rows_;
	int num_columns_;
	const std::string& target_;
	std::vector<std::vector<char>>& board_;
	static std::vector<std::pair<int, int>> directions_;
};

std::vector<std::pair<int, int>> Searcher::directions_;

Searcher::Searcher(std::vector<std::vector<char>>& board,
	const std::string& target) :target_(target), board_(board)
{
	num_rows_ = static_cast<int>(board_.size());
	if (!board_.empty())
	{
		num_columns_ = static_cast<int>(board_.front().size());
	}
	if (directions_.empty())
	{
		directions_ = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
	}
}

bool Searcher::Search() const
{
	for (auto i = 0; i < num_rows_; ++i)
	{
		for (auto j = 0; j < num_columns_; ++j)
		{
			if (board_[i][j] != target_.front())
			{
				continue;
			}
			if (Search(0, i, j))
			{
				return true;
			}
		}
	}
	return false;
}

bool Searcher::Search(const int i_target, const int x, const int y) const
{
	if (i_target >= static_cast<int>(target_.size()))
	{
		return true;
	}
	if (IsOutside(x, y) || target_[i_target] != board_[x][y])
	{
		return false;
	}

	const auto temp = board_[x][y];
	board_[x][y] = '\0';

	for (const auto& direction : directions_)
	{
		if (Search(i_target + 1, x + direction.first, y + direction.second))
		{
			return true;
		}
	}

	board_[x][y] = temp;
	return false;
}

class Solution 
{
public:
	static bool exist(std::vector<std::vector<char>>& board,
		std::string word);
};

bool Solution::exist(std::vector<std::vector<char>>& board,
	std::string word)
{
	return Searcher(board, word).Search();
}

int main(int argc, char* argv[])
{
	return 0;
}

