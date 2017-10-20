#include <stdio.h>
#include <ios>

void JarvisAndLoneInteger()
{
	std::ios::sync_with_stdio(false);

	int test_cases;
	scanf("%d", &test_cases);
	while (test_cases--)
	{
		int n_len;
		scanf("%d", &n_len);
		unsigned long long store;
		scanf("%llu", &store);
		while (--n_len)
		{
			unsigned long long n;
			scanf("%llu", &n);
			store ^= n;
		}

		if (store)
		{
			printf("%llu\n", store);
		}
		else
		{
			printf("-1\n");
		}
	}
}