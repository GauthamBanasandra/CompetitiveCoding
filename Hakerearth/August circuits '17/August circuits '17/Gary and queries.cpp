#include <stdio.h>
#include <ios>
#include <map>
#include <math.h>

#define MAX_LIMIT 600000
unsigned long long nums[MAX_LIMIT];

void GaryAndQueries()
{
	std::ios::sync_with_stdio(false);

	int op;
	unsigned long long n, q, max = 0, x, y;
	std::map<unsigned long long, unsigned long long> f_map;
	scanf("%llu%llu", &n, &q);
	for (unsigned long long i = 0; i < n; ++i)
	{
		scanf("%llu", &nums[i]);
		if (nums[i] > max)
		{
			max = nums[i];
		}

		++f_map[nums[i]];
	}

	for (unsigned long long i = 0; i < q; ++i)
	{
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			scanf("%llu%llu", &x, &y);			
			++f_map[y];
			--f_map[nums[x - 1]];
			if (f_map[nums[x - 1]] <= 0)
			{
				f_map.erase(nums[x - 1]);
			}

			max = f_map.rbegin()->first;
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
				auto it = f_map.find(x);
				if (it == f_map.end())
				{
					f_map[x] = 0;
					for (auto j = f_map.find(x); j != f_map.end(); ++j)
					{
						sum += j->second * static_cast<unsigned long long>(floor(j->first / x));
					}

					f_map.erase(x);
				}
				else
				{
					for (auto j = it; j != f_map.end(); ++j)
					{
						sum += j->second * static_cast<unsigned long long>(floor(j->first / x));
					}
				}
				printf("%llu\n", sum);
			}
			break;
		}
	}
}