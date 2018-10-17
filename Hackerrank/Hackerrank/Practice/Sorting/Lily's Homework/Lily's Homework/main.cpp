#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100000

int Comparator(const void *a, const void *b)
{
	return (*(unsigned long *)a - *(unsigned long *)b);
}

int DiffCount(unsigned long *numbers, unsigned long *numbers_sorted, int n)
{
	int fwd = 0,
		rev = 0;

	for (int i = 0; i < n; ++i)
	{
		if (numbers[i] != numbers_sorted[i])
		{
			++fwd;
		}
		if (numbers[i] != numbers_sorted[n - i - 1])
		{
			++rev;
		}
	}

	return fwd < rev ? fwd : rev;
}

int main()
{
	int n = 0,
		swap_count = 0;
	scanf("%d", &n);
	unsigned long numbers[SIZE],
		numbers_sorted[SIZE];

	for (int i = 0; i < n; ++i)
	{
		scanf("%lu", &numbers[i]);
		numbers_sorted[i] = numbers[i];
	}

	qsort(numbers_sorted, n, sizeof(unsigned long), Comparator);	

	int diff_count = DiffCount(numbers, numbers_sorted, n);
	swap_count = ceil(diff_count / 2.0);
	printf("%d", swap_count);

	return 0;
}