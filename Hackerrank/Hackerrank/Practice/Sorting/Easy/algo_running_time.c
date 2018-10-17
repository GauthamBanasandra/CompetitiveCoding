/*Though the problem seems quite trivial, it was really hard. The trick is to accumulate the difference between the indices i and j+1.
Since, at the end of the loop, the element at i will be moved to the index j+1. It is also important to note that in the while loop, it is
num[j]>k and not num[j]>=k.*/
#include <stdio.h>
int main()
{
	int i = 0, j = 0, k = 0, n=0, shifts=0;
	scanf("%d", &n);
	int num[1000];
	for (i = 0; i < n; ++i)
		scanf("%d", &num[i]);
	for (i = 1; i <n ; i++)
	{
		j = i - 1;
		k = num[i];
		while (j >= 0 && num[j]>k && (num[j + 1] = num[j--]));
		num[j + 1] = k;
		shifts += i - (j+1);
	}
	printf("%d\n", shifts);
	return 0;
}