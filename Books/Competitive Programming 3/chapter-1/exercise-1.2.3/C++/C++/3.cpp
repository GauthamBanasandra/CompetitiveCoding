#include <stdio.h>
#include <ios>
#include <set>

void Sort()
{
	std::ios::sync_with_stdio(false);

	int n, i;
	scanf("%d", &n);
	std::set<int> num_set;
	while (n--)
	{
		scanf("%d", &i);
		num_set.insert(i);
	}

	for (int num : num_set)
	{
		printf("%d\t", num);
	}

	printf("\n");
}