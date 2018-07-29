#include <stdio.h>
#include <ios>
#include <unordered_map>
#include <unordered_set>

#define HG_MAN 7

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	unsigned long long round;
	std::string word;
	std::string guess;

	while (scanf("%llu\n", &round), round != -1)
	{
		std::unordered_map<char, bool> letters_guess;
		std::unordered_set<char> guesses;

		char c;
		while (c = getchar(), c != '\n')
		{
			letters_guess[c] = false;
		}

		long long guess_rem = letters_guess.size();
		auto chances = 0;
		auto lost = false, won = false;
		while (c = getchar(), c != '\n')
		{
			if (lost || won)
			{
				continue;
			}

			const auto find_guess = guesses.find(c);
			if (find_guess == guesses.end())
			{
				const auto find = letters_guess.find(c);
				if (find == letters_guess.end())
				{
					++chances;
					if (chances >= HG_MAN)
					{
						printf("Round %llu\nYou lose.\n", round);
						lost = true;
					}
				}
				else
				{
					if (!find->second)
					{
						--guess_rem;
					}

					if (guess_rem == 0)
					{
						printf("Round %llu\nYou win.\n", round);
						won = true;
					}

					find->second = true;
				}
			}

			guesses.insert(c);
		}

		if (!won && !lost)
		{
			printf("Round %llu\nYou chickened out.\n", round);
		}
	}

	return 0;
}
