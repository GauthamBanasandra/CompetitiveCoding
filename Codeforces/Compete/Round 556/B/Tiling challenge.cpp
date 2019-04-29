#include <vector>
#include <string>
#include <iostream>

namespace round_556
{
	bool IsPossible(std::vector<std::string>& grid, int n)
	{
		const auto is_outside = [n](const int x, const int y)->bool
		{
			return x < 0 || x >= n || y < 0 || y >= n;
		};
		const auto is_possible = [&grid, &is_outside]
		(const int x, const int y)->bool
		{
			return !is_outside(x, y) && grid[x][y] == '.';
		};

		std::vector<std::pair<int, int>> directions = {
			{0, 0},{1,-1},{1,0},{1, 1},{2, 0}
		};

		for (auto x = 0; x < n; ++x)
		{
			for (auto y = 0; y < n; ++y)
			{
				if (grid[x][y] != '.')
				{
					continue;
				}
				for (const auto& direction : directions)
				{
					const auto fill_x = x + direction.first;
					const auto fill_y = y + direction.second;

					if (!is_possible(fill_x, fill_y))
					{
						return false;
					}
					grid[fill_x][fill_y] = 'x';
				}
			}
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	int n;
	std::cin >> n;

	std::vector<std::string> grid(n);
	for (auto i = 0; i < n; ++i)
	{
		std::cin >> grid[i];
	}

	std::cout << (round_556::IsPossible(grid, n) ? "YES" : "NO") << std::endl;
	return 0;
}
