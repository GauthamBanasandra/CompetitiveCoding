#include <stdio.h>
#include <ios>
#include <algorithm>

#define MAX_DEVICES 100200
long long distx[MAX_DEVICES];
long long disty[MAX_DEVICES];
long long dist[MAX_DEVICES];

int main()
{
	std::ios::sync_with_stdio(false);

	unsigned long long n, k;
	scanf("%llu%llu", &n, &k);
	for (int i = 0; i < n; ++i)
	{
		scanf("%lld", &distx[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		scanf("%lld", &disty[i]);
		dist[i] = ceil(sqrt(distx[i] * distx[i] + disty[i] * disty[i]));
	}

	std::sort(dist, dist + n);
	printf("%lld\n", dist[k - 1]);
}