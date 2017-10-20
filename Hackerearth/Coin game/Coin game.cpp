#include <iostream>
#include <ios>
#include <math.h>

typedef long long big_int;

inline big_int TwoPow(big_int num)
{
	big_int ec = 0;
	while (true)
	{
		if (num & 1)
		{
			break;
		}

		++ec;
		num /= 2;
	}

	return ec;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	big_int test_cases, n;
	scanf("%lld", &test_cases);
	while (test_cases--)
	{
		scanf("%lld", &n);
		big_int moves = 0, pc = 0;
		while (n--)
		{
			scanf("%lld", &pc);
			if (!(pc & 1))
			{
				moves += TwoPow(pc);
			}
		}

		printf("%s\n", moves % 2 ? "Charlie" : "Alan");
	}

	return 0;
}
