#include <stdio.h>
#include <ios>
#define SIZE 100000

unsigned long long nums[SIZE], odd_counts[SIZE], even_counts[SIZE];

void SherlockAndXor()
{
	std::ios::sync_with_stdio(false);

	int test_cases;
	scanf("%d", &test_cases);
	while (test_cases--)
	{
		unsigned long long size, odd = 0, even = 0;
		scanf("%llu", &size);

		for (unsigned long long i = 0; i < size; ++i)
		{
			scanf("%llu", &nums[i]);
			if (nums[i] & 1)
			{
				++odd;
			}
			else
			{
				++even;
			}

			odd_counts[i] = odd;
			even_counts[i] = even;
		}

		unsigned long long count = 0;
		for (unsigned long long i = 0; i < size; ++i)
		{
			if (nums[i] & 1)
			{
				count += even - even_counts[i];
			}
			else
			{
				count += odd - odd_counts[i];
			}
		}

		printf("%llu\n", count);
	}
}