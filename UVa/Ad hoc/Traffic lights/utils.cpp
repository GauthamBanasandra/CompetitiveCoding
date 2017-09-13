#include <stdio.h>
#include <vector>

typedef unsigned long long big_int;

void Print(std::vector<std::vector<int>> scenarios)
{
	for (big_int i = 0; i < scenarios.size(); ++i)
	{
		for (big_int j = 0; j < scenarios[i].size(); ++j)
		{
			printf("%d ", scenarios[i][j]);
		}

		printf("\n");
	}
}

void Print(std::vector<int> scenario)
{
	for (auto cycle: scenario)
	{
		printf("%d ", cycle);
	}

	printf("\n");
}