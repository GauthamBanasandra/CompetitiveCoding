#include <string>
#include <iostream>
#include <cassert>

inline bool IsNum(char c)
{
	return c >= 48 && c <= 57;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	char prev = '*', la;
	auto score = 0;
	auto frame = 0.0;
	std::string line;

	while (getline(std::cin, line), line[0] != 'G')
	{
		const auto len = line.length();
		for (size_t i = 0; i < len; i += 2)
		{
			const auto c = line[i];
			assert(c != ' ');

			if (IsNum(c))
			{
				frame += 0.5;
				score += c - '0';
			}
			else if (c == '/')
			{
				frame += 0.5;
				assert(prev != '*');
				score += 10 - (prev - '0');
				la = line[i + 2];
				assert(la != '\n');
				if (IsNum(la))
				{
					score += la - '0';
				}
				else if (la == 'X')
				{
					score += 10;
				}

				if (frame >= 10)
				{
					break;
				}
			}
			else if (c == 'X')
			{
				frame += 1.0;
				score += 10;
				la = line[i + 2];
				const auto lala = line[i + 4];
				if (IsNum(la) && IsNum(lala))
				{
					score += la + lala - 2 * '0';
				}
				else if (la == 'X' && lala == 'X')
				{
					score += 20;
				}
				else if (IsNum(la) && lala == '/')
				{
					score += 10;
				}
				else if (la == 'X' && IsNum(lala))
				{
					score += lala - '0' + 10;
				}

				if (frame >= 10)
				{
					break;
				}
			}

			prev = c;
		}

		printf("%d\n", score);
		score = 0;
		frame = 0.0;
	}

	return 0;
}
