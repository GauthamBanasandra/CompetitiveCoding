#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <ios>

namespace uva260
{
	class Filler
	{
	public:
		explicit Filler(std::vector<std::string> &board);

		char FindWinner() const;

	private:
		bool Fill(int row, int column, char expected_colour,
			char fill_colour) const;
		bool HasReached(int row, int column, char colour) const;
		bool IsOutside(const int row, const int column) const
		{
			return row < 0 || row >= num_rows_ || column < 0 || column >= num_columns_;
		}

		const int num_rows_;
		const int num_columns_;
		std::vector<std::string> &board_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> Filler::directions_;

	Filler::Filler(std::vector<std::string>& board) :
		num_rows_(static_cast<int>(board.size())),
		num_columns_(static_cast<int>(board.front().size())), board_(board)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, 1} };
		}
	}

	char Filler::FindWinner() const
	{
		for (auto column = 0; column < num_columns_; ++column)
		{
			if (board_[0][column] != 'b')
			{
				continue;
			}

			if (Fill(0, column, 'b', '0'))
			{
				return 'B';
			}
		}

		for (auto row = 0; row < num_rows_; ++row)
		{
			if (board_[row][0] != 'w')
			{
				continue;
			}

			if (Fill(row, 0, 'w', '1'))
			{
				return 'W';
			}
		}
		assert(false && "Either B or W should win");
		return '\0';
	}

	bool Filler::Fill(const int row, const int column,
		const char expected_colour, const char fill_colour) const
	{
		if (IsOutside(row, column) || board_[row][column] != expected_colour)
		{
			return false;
		}

		board_[row][column] = fill_colour;
		if (HasReached(row, column, expected_colour))
		{
			return true;
		}

		for (const auto& direction : directions_)
		{
			if (Fill(row + direction.first, column + direction.second,
				expected_colour, fill_colour))
			{
				return true;
			}
		}
		return false;
	}

	bool Filler::HasReached(const int row, const int column, const char colour) const
	{
		switch (colour)
		{
		case 'b':
			return row == num_rows_ - 1;

		case 'w':
			return column == num_columns_ - 1;

		default:
			assert(false && "Invalid colour");
		}
		return false;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n;
	auto t = 0;
	std::vector<std::string> board;

	while (std::cin >> n, n)
	{
		board.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> board[i];
		}

		uva260::Filler filler(board);
		std::cout << ++t << ' ' << filler.FindWinner() << std::endl;
	}
	return 0;
}
