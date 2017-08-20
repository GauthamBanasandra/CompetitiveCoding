#include <stdio.h>
#include <ios>

void RelationalOperators()
{
	std::ios::sync_with_stdio(false);

	int test_cases;
	long long a, b;
	scanf("%d", &test_cases);
	while (test_cases--)
	{
		scanf("%lld%lld", &a, &b);
		if (a > b)
		{
			printf(">\n");
		}
		else if (a < b)
		{
			printf("<\n");
		}
		else
		{
			printf("=\n");
		}
	}
}
