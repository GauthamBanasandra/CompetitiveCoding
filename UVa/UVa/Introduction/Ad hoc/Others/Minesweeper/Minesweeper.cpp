#include <stdio.h>

#define MAX_ROWS 110
#define MAX_COLS 110

char field[MAX_ROWS][MAX_COLS];

inline bool InsideField(int x, int y, int n, int m)
{
	return x >= 0 && y >= 0 && x < n && y < m;
}

inline void IncrIfValid(int x, int y, int n, int m)
{
	InsideField(x, y, n, m) && field[x][y] != '*' && ++field[x][y];
}

int main(int argc, char* argv[])
{
	int n, m;
	unsigned long long f = 0;
	while (scanf("%d%d\n", &n, &m), n && m)
	{
		for (auto i = 0; i < n; ++i)
		{
			for (auto j = 0; j < m; ++j)
			{
				field[i][j] = '0';
			}

			field[i][m] = '\0';
		}

		if (f > 0)
		{
			printf("\n");
		}

		for (auto r = 0; r < n; ++r)
		{
			for (auto c = 0; c < m + 1; ++c)
			{
				if (getchar() == '*')
				{
					field[r][c] = '*';
					IncrIfValid(r, c + 1, n, m);
					IncrIfValid(r, c - 1, n, m);
					IncrIfValid(r + 1, c, n, m);
					IncrIfValid(r - 1, c, n, m);
					IncrIfValid(r - 1, c - 1, n, m);
					IncrIfValid(r - 1, c + 1, n, m);
					IncrIfValid(r + 1, c + 1, n, m);
					IncrIfValid(r + 1, c - 1, n, m);
				}
			}
		}

		printf("Field #%llu:\n", ++f);
		for (int r = 0; r < n; ++r)
		{
			printf("%s\n", field[r]);
		}
	}

	return 0;
}
