#include <vector>
#include <string>
#include <iostream>
#include <ios>

namespace uva11953
{
	class FloodFill
	{
	public:
		FloodFill(std::vector<std::string>& grid, int n);

		int Count() const;

	private:
		void Fill(int row, int column, bool& is_standing) const;

		bool IsOutside(const int row, const int column) const
		{
			return row < 0 || row >= n_ || column < 0 || column >= n_;
		}

		const int n_;
		std::vector<std::string>& grid_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> FloodFill::directions_;

	FloodFill::FloodFill(std::vector<std::string>& grid, const int n) : n_(n), grid_(grid)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		}
	}

	int FloodFill::Count() const
	{
		auto ships = 0;
		for (auto i = 0; i < n_; ++i)
		{
			for (auto j = 0; j < n_; ++j)
			{
				if (grid_[i][j] == 'x' || grid_[i][j] == '@')
				{
					auto is_standing = false;
					Fill(i, j, is_standing);
					ships += is_standing ? 1 : 0;
				}
			}
		}
		return ships;
	}

	void FloodFill::Fill(const int row, const int column, bool& is_standing) const
	{
		if (IsOutside(row, column) ||
			grid_[row][column] == '.' ||
			grid_[row][column] == 'v')
		{
			return;
		}

		if (grid_[row][column] == 'x')
		{
			is_standing = true;
		}
		grid_[row][column] = 'v';

		for (const auto& direction : directions_)
		{
			Fill(row + direction.first, column + direction.second, is_standing);
		}
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	int n;
	std::vector<std::string> grid;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> n;
		grid.resize(n);
		for (auto j = 0; j < n; ++j)
		{
			std::cin >> grid[j];
		}

		uva11953::FloodFill filler(grid, n);
		std::cout << "Case " << i << ": " << filler.Count() << std::endl;
	}
	return 0;
}
