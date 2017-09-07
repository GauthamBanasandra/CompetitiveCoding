#include <iostream>
#include <ios>
#include <string>
#include <ctype.h>
#include <math.h>

inline bool IsValid(char c)
{
	return c != ' '&& c != '.' && c != ','&&c != '!' && c != '?';
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::string line;
	while (getline(std::cin, line), line != "DONE")
	{
		std::string letters;
		for (auto c : line)
		{
			if (IsValid(c))
			{
				letters += toupper(c);
			}
		}

		const unsigned long long len = letters.length();
		unsigned long long mid;
		if (len & 1)
		{
			mid = static_cast<unsigned long long>(floor(len / 2));
		}
		else
		{
			mid = len / 2;
		}

		auto is_palindrome = true;
		for (unsigned long long i = 0; i < mid; ++i)
		{
			if (letters[i] != letters[len - i - 1])
			{
				is_palindrome = false;
				break;
			}
		}

		printf("%s\n", is_palindrome ? "You won't be eaten!" : "Uh oh..");
	}

	return 0;
}
