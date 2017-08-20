#include <stdio.h>
#include <ios>

void EventPlanning()
{
	std::ios::sync_with_stdio(false);

	int n, h, w, p, a;
	unsigned long long b;

	while (scanf("%d%llu%d%d", &n, &b, &h, &w) != EOF)
	{
		unsigned long long final_budget = -1;
		while (h--)
		{
			scanf("%d", &p);
			bool sufficient_beds = true;
			for (int i = 0; i < w; ++i)
			{
				scanf("%d", &a);
				if (a < n)
				{
					sufficient_beds = false;
				}
			}

			if (sufficient_beds)
			{
				unsigned long long budget = p*n;
				if (final_budget == -1)
				{
					final_budget = budget;
				}
				else if (budget < final_budget)
				{
					final_budget = budget;
				}
			}
		}

		if (final_budget == -1)
		{
			printf("stay home\n");
		}
		else
		{
			printf("%llu\n", final_budget);
		}
	}
}