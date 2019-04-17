#include <vector>
#include <string>
#include <iostream>
#include <ios>

namespace uva11561
{
	class FloodFill
	{
	public:
		explicit FloodFill(std::vector<std::string>& grid);

		int Count() const;

	private:
		int Next(int row, int column) const;
		bool IsSafe(int row, int column) const;
		std::pair<int, int> GetStartPosition() const;

		std::vector<std::string>& grid_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> FloodFill::directions_;

	FloodFill::FloodFill(std::vector<std::string>& grid) :grid_(grid)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		}
	}

	int FloodFill::Count() const
	{
		const auto [row_start, column_start] = GetStartPosition();
		return Next(row_start, column_start);
	}

	int FloodFill::Next(const int row, const int column) const
	{
		if (grid_[row][column] == '#' ||
			grid_[row][column] == 'v' ||
			grid_[row][column] == 'T')
		{
			return 0;
		}

		auto count = grid_[row][column] == 'G' ? 1 : 0;
		grid_[row][column] = 'v';
		if (!IsSafe(row, column))
		{
			return count;
		}

		for (const auto& direction : directions_)
		{
			count += Next(row + direction.first, column + direction.second);
		}
		return count;
	}

	bool FloodFill::IsSafe(const int row, const int column) const
	{
		for (const auto& direction : directions_)
		{
			if (grid_[row + direction.first][column + direction.second] == 'T')
			{
				return false;
			}
		}
		return true;
	}

	std::pair<int, int> FloodFill::GetStartPosition() const
	{
		for (auto i = 0, num_rows = static_cast<int>(grid_.size()); i < num_rows; ++i)
		{
			for (auto j = 0, num_columns = static_cast<int>(grid_.front().size()); j < num_columns; ++j)
			{
				if (grid_[i][j] == 'P')
				{
					return { i, j };
				}
			}
		}
		return { -1, -1 };
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int h, w;
	std::vector<std::string> grid;

	while (std::cin >> w >> h, !std::cin.eof())
	{
		grid.resize(h);
		for (auto i = 0; i < h; ++i)
		{
			std::cin >> grid[i];
		}

		uva11561::FloodFill filler(grid);
		std::cout << filler.Count() << std::endl;
	}
	return 0;
}
