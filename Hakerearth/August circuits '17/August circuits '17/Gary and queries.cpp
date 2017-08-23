#include <stdio.h>
#include <ios>
#include <math.h>

#define MAX_LIMIT 600000
unsigned long long nums[MAX_LIMIT];
unsigned long long f[MAX_LIMIT];

void GaryAndQueries()
{
	std::ios::sync_with_stdio(false);

	int op;
	unsigned long long n, q, max = 0, x, y;
	scanf("%llu%llu", &n, &q);
	for (unsigned long long i = 0; i < n; ++i)
	{
		scanf("%llu", &nums[i]);
		if (nums[i] > max)
		{
			max = nums[i];
		}

		++f[nums[i]];
	}

	for (unsigned long long i = 0; i < q; ++i)
	{
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			scanf("%llu%llu", &x, &y);
			--f[nums[x - 1]];
			++f[y];
			if (y >= max)
			{
				max = y;
			}
			else if (nums[x - 1] == max)
			{
				for (unsigned long long j = max; j != 0; --j)
				{
					if (f[j])
					{
						max = j;
						break;
					}
				}
			}

			nums[x - 1] = y;
			break;
		case 2:
			scanf("%llu", &x);
			if (x > max)
			{
				printf("0\n");
			}
			else
			{
				unsigned long long sum = 0;
				for (unsigned long long j = 0; j <= max; ++j)
				{
					sum += f[j] * static_cast<unsigned long long>(floor(j / x));
				}

				printf("%llu\n", sum);
			}
			break;
		}
	}
}