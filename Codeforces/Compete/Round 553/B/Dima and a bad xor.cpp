#include <vector>
#include <algorithm>
#include <iostream>

namespace round_553
{
	std::pair<bool, std::vector<int>> FindXOR(const std::vector<std::vector<int>>& numbers)
	{
		const auto num_rows = static_cast<int>(numbers.size());
		std::vector<std::vector<std::pair<bool, int>>> memo(numbers.size(),
			std::vector<std::pair<bool, int>>(1024, { false, 0 }));

		const auto num_columns = static_cast<int>(memo.front().size());

		for (auto i = 0; i < static_cast<int>(numbers.front().size()); ++i)
		{
			memo.front()[numbers.front()[i]] = { true, i };
		}

		for (auto i = 1; i < num_rows; ++i)
		{
			for (auto j = 0; j < num_columns; ++j)
			{
				if (!memo[i - 1][j].first)
				{
					continue;
				}

				for (auto k = 0; k < static_cast<int>(numbers[i].size()); ++k)
				{
					memo[i][numbers[i][k] ^ j] = { true, k };
				}
			}
		}

		std::vector<int> selected_columns;
		for (auto i = 1; i < num_columns; ++i)
		{
			auto [is_non_zero, column] = memo.back()[i];
			if (!is_non_zero)
			{
				continue;
			}
			selected_columns.emplace_back(column);

			auto k = num_rows - 1;
			while (k > 0)
			{
				i = i ^ numbers[k][column];
				auto next = memo[k - 1][i];
				selected_columns.emplace_back(next.second);
				column = next.second;
				--k;
			}

			std::reverse(selected_columns.begin(), selected_columns.end());
			return { true, selected_columns };
		}


		return { false, selected_columns };
	}
}

int main(int argc, char* argv[])
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> numbers(n, std::vector<int>(m));

	for (auto i = 0; i < n; ++i)
	{
		for (auto j = 0; j < m; ++j)
		{
			std::cin >> numbers[i][j];
		}
	}

	const auto& [is_possible, unique_nums] = round_553::FindXOR(numbers);
	if (!is_possible)
	{
		std::cout << "NIE" << std::endl;
		return 0;
	}

	std::cout << "TAK" << std::endl;
	auto separator = "";
	for (const auto num : unique_nums)
	{
		std::cout << separator << num + 1;
		separator = " ";
	}
	std::cout << std::endl;
	return 0;
}
