#include <stdio.h>
#include <ios>

void PrintPiDigits()
{
	std::ios::sync_with_stdio(false);

	int n;
	scanf("%d", &n);
	double pi = 22 / 7.0;
	printf("%0.*f\n", n, pi);
}