#include <ios>
#include <string>
#include <iostream>

#define MAX_ROWS 8
#define MAX_COLS 8
#define MAX_FEN_LEN 100

void PrintBoard(char board[MAX_ROWS][MAX_COLS]);

char board[MAX_ROWS][MAX_COLS];

inline bool InsideBoard(int x, int y)
{
	return x >= 0 && y >= 0 && x < MAX_ROWS && y < MAX_COLS;
}

inline void MarkIfValid(int x, int y)
{
	board[x][y] = InsideBoard(x, y) && board[x][y] == '.' ? 'x' : board[x][y];
}

inline bool IsEmpty(int x, int y)
{
	return board[x][y] == '.' || board[x][y] == 'x';
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::string fen;
	while (getline(std::cin, fen), !std::cin.eof())
	{
		for (auto i = 0; i < MAX_ROWS; ++i)
		{
			for (auto j = 0; j < MAX_COLS; ++j)
			{
				board[i][j] = '.';
			}
		}

		auto col = -1, row = 0;
		for (char c : fen)
		{
			switch (c)
			{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				col += c - '0';
				break;
			case 'p':
			case 'P':
			case 'n':
			case 'N':
			case 'b':
			case 'B':
			case 'r':
			case 'R':
			case 'q':
			case 'Q':
			case 'k':
			case 'K':
				++col;
				board[row][col] = c;				
				break;
			case '/':
				col = -1;
				++row;
				break;
			}
		}

		for (auto r = 0; r < MAX_ROWS; ++r)
		{
			for (auto c = 0; c < MAX_COLS; ++c)
			{
				switch (board[r][c])
				{
				case 'p':
					MarkIfValid(r + 1, c + 1);
					MarkIfValid(r + 1, c - 1);
					break;
				case 'P':
					MarkIfValid(r - 1, c - 1);
					MarkIfValid(r - 1, c + 1);
					break;
				case 'n':
				case 'N':
					MarkIfValid(r - 2, c - 1);
					MarkIfValid(r - 2, c + 1);
					MarkIfValid(r - 1, c + 2);
					MarkIfValid(r + 1, c + 2);
					MarkIfValid(r + 2, c + 1);
					MarkIfValid(r + 2, c - 1);
					MarkIfValid(r + 1, c - 2);
					MarkIfValid(r - 1, c - 2);
					break;
				case 'b':
				case 'B':
				{
					auto _r = r, _c = c;
					while (InsideBoard(--_r, --_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(--_r, ++_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(++_r, ++_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(++_r, --_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}
				}
				break;
				case 'r':
				case 'R':
				{
					auto _r = r, _c = c;
					while (InsideBoard(_r, --_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(_r, ++_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(--_r, _c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(++_r, _c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}
				}
				break;
				case 'q':
				case 'Q':
				{
					auto _r = r, _c = c;
					while (InsideBoard(--_r, --_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(--_r, ++_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(++_r, ++_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(++_r, --_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(_r, --_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(_r, ++_c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(--_r, _c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}

					_r = r, _c = c;
					while (InsideBoard(++_r, _c) && IsEmpty(_r, _c))
					{
						board[_r][_c] = 'x';
					}
				}
				break;
				case 'k':
				case 'K':
					MarkIfValid(r + 1, c + 1);
					MarkIfValid(r + 1, c - 1);
					MarkIfValid(r - 1, c - 1);
					MarkIfValid(r - 1, c + 1);
					MarkIfValid(r, c + 1);
					MarkIfValid(r, c - 1);
					MarkIfValid(r + 1, c);
					MarkIfValid(r - 1, c);
					break;
				}
			}
		}

		auto empty = 0;
		for (auto i = 0; i < MAX_ROWS; ++i)
		{
			for (auto j = 0; j < MAX_COLS; ++j)
			{
				if (board[i][j] == '.')
				{
					++empty;
				}
			}
		}
		
		printf("%d\n", empty);
		//PrintBoard(board);
	}

	return 0;
}

