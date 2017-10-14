#include <stdio.h>
#include <ios>
#include <math.h>

int main()
{
	std::ios::sync_with_stdio(false);

	unsigned long long test_cases;
	char pawn;
	int m, n;

	scanf("%llu\n", &test_cases);
	while (test_cases--)
	{
		scanf("%c%d%d\n", &pawn, &m, &n);
		switch (pawn)
		{
		case 'r':
		case 'Q':
			printf("%d\n", m < n ? m : n);
			break;
		case 'k':
			printf("%d\n", static_cast<int>(ceil(m*n / 2.0)));
			break;
		case 'K':
			printf("%d\n", (m & 1 ? m + 1 : m)*(n & 1 ? n + 1 : n) / 4);
			break;
		}
	}
}
