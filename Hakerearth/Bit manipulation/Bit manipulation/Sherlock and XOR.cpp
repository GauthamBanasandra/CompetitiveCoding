#include <stdio.h>
#include <ios>
#define SIZE 100000

void SherlockAndXor()
{
	std::ios::sync_with_stdio(false);

	int test_cases;
	scanf("%d", &test_cases);
	while (test_cases--)
	{
		int size;
		scanf("%d", &size);
		unsigned long long nums[SIZE];

		for (int i = 0; i < size; ++i)
		{
			scanf("%llu", &nums[i]);
		}

		int count = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				if ((nums[i] ^ nums[j]) & 1)
				{
					++count;
				}
			}
		}

		printf("%d\n", count);
	}
}