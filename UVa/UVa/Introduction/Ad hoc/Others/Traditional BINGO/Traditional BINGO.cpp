#include <stdio.h>
#include <ios>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#define ROW_LEN 5
#define COL_LEN 5
#define MID_ROW_IDX 2
#define MID_COL_IDX 2
#define GUESS_ROW_LEN 8
#define GUESS_COL_LEN 10

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	unsigned long long n;
	std::unordered_map<int, std::unordered_set<std::string>> num_rev;
	std::unordered_map<std::string, int> f;

	scanf("%llu", &n);
	while (n--)
	{
		num_rev.clear();
		f.clear();
		auto num = 0;

		for (auto i = 0; i < ROW_LEN; ++i)
		{
			const auto row = "r" + std::to_string(i + 1);
			for (auto j = 0; j < COL_LEN; ++j)
			{
				scanf("%d", &num);
				i == MID_ROW_IDX && j == MID_COL_IDX && ++j;

				num_rev[num].insert(row);
				const auto col = "c" + std::to_string(j + 1);
				num_rev[num].insert(col);
				if (i == j)
				{
					const auto diagonal = "d1";
					num_rev[num].insert(diagonal);
				}

				if (ROW_LEN - (i + 1) == j)
				{
					const auto diagonal = "d2";
					num_rev[num].insert(diagonal);
				}
			}

			f[row] = 5;
			const auto col = "c" + std::to_string(i + 1);
			f[col] = 5;
		}

		f["r3"] = f["c3"] = f["d1"] = f["d2"] = 4;
		auto win = false;
		auto guess_count = 0;
		for (auto i = 0; i < GUESS_ROW_LEN; ++i)
		{
			const auto guess_col_len = i == GUESS_ROW_LEN - 1 ? 5 : GUESS_COL_LEN;
			for (auto j = 0; j < guess_col_len; ++j)
			{
				scanf("%d", &num);
				if (win)
				{
					continue;
				}

				++guess_count;
				const auto find_num = num_rev.find(num);
				if (find_num != num_rev.end())
				{
					for (const auto pos : find_num->second)
					{
						--f[pos];

						assert(f[pos] >= 0);
						if (!f[pos])
						{
							win = true;
						}
					}

					num_rev.erase(find_num);
				}
			}
		}

		printf("BINGO after %d numbers announced\n", guess_count);
	}

	return 0;
}
