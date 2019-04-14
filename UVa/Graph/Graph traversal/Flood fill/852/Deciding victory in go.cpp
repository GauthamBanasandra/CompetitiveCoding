#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <ios>

namespace uva852
{
	enum class Lord { kUninitialized, kBlack, kWhite, kNeither };

	class Filler
	{
	public:
		explicit Filler(std::vector<std::string>& board);

		std::pair<int, int> Count() const;

	private:
		int FillTerritories(int row, int column, char expected_colour,
			char fill_colour, Lord& lord) const;

		static bool IsOutside(const int row, const int column)
		{
			return row < 0 || row >= 9 || column < 0 || column >= 9;
		}

		const char black_colour_ = 'X';
		const char white_colour_ = 'O';
		std::vector<std::string>& board_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> Filler::directions_;

	Filler::Filler(std::vector<std::string>& board) : board_(board)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		}
	}

	std::pair<int, int> Filler::Count() const
	{
		auto num_black = 0;
		auto num_white = 0;
		for (auto i = 0; i < 9; ++i)
		{
			for (auto j = 0; j < 9; ++j)
			{
				const auto cell = board_[i][j];
				if (cell == black_colour_)
				{
					++num_black;
				}
				else if (cell == white_colour_)
				{
					++num_white;
				}
				else if (cell == '.')
				{
					auto lord{ Lord::kUninitialized };
					const auto count = FillTerritories(
						i, j, '.', 'c', lord);
					if (lord == Lord::kBlack)
					{
						num_black += count;
					}
					else if (lord == Lord::kWhite)
					{
						num_white += count;
					}
				}
			}
		}
		return std::make_pair(num_black, num_white);
	}

	int Filler::FillTerritories(const int row, const int column,
		const char expected_colour, const char fill_colour, Lord& lord) const
	{
		if (IsOutside(row, column) || board_[row][column] == fill_colour)
		{
			return 0;
		}

		auto& cell = board_[row][column];
		if (cell == black_colour_)
		{
			if (lord == Lord::kUninitialized || lord == Lord::kBlack)
			{
				lord = Lord::kBlack;
			}
			else
			{
				lord = Lord::kNeither;
			}
			return 0;
		}
		if (cell == white_colour_)
		{
			if (lord == Lord::kUninitialized || lord == Lord::kWhite)
			{
				lord = Lord::kWhite;
			}
			else
			{
				lord = Lord::kNeither;
			}
			return 0;
		}
		assert(cell == expected_colour);

		cell = fill_colour;
		auto count = 1;
		for (const auto& direction : directions_)
		{
			count += FillTerritories(row + direction.first,
				column + direction.second, expected_colour, fill_colour, lord);
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	std::vector<std::string> board(9);

	std::cin >> t;
	while (t--)
	{
		for (auto i = 0; i < 9; ++i)
		{
			std::cin >> board[i];
		}

		uva852::Filler filler(board);
		const auto [num_black, num_white] = filler.Count();
		std::cout << "Black " << num_black << " White " << num_white << std::endl;
	}
	return 0;
}
