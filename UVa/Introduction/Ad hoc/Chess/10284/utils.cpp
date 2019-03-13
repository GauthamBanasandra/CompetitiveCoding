#define MAX_ROWS 8
#define MAX_COLS 8
#include <stdio.h>

void PrintBoard(char board[MAX_ROWS][MAX_COLS])
{
	for (auto i = 0; i < MAX_ROWS; ++i)
	{
		for (auto j = 0; j < MAX_COLS; ++j)
		{
			printf("%c ", board[i][j]);
		}

		printf("\n");
	}
	printf("\n");
}