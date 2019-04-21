#include <vector>
#include <algorithm>
#include <iostream>

namespace april_cook_off_2019
{
	using Matrix = std::vector<std::vector<int>>;

	bool IsPossible(const int n, const Matrix& matrix)
	{
		for (const auto& row : matrix)
		{
			if (std::find(row.begin(), row.end(), 0) == row.end())
			{
				return false;
			}
		}

		for (auto i = 0; i < n; ++i)
		{
			auto is_possible = false;
			for (auto j = 0; j < n; ++j)
			{
				if (matrix[j][i] == 0)
				{
					is_possible = true;
					break;
				}
			}

			if (!is_possible)
			{
				return false;
			}
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	april_cook_off_2019::Matrix matrix;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		matrix.resize(n);
		for (auto& row : matrix)
		{
			row.resize(n);
		}

		for (auto i = 0; i < n; ++i)
		{
			for (auto j = 0; j < n; ++j)
			{
				std::cin >> matrix[i][j];
			}
		}

		std::cout << (april_cook_off_2019::IsPossible(n, matrix) ? "YES" : "NO") << std::endl;
	}
	return 0;
}
