#include <stdio.h>
#include <ios>

#define MAX_BUILDINGS 100200
int heights[MAX_BUILDINGS];

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n, h;
	scanf("%d", &n);
	for (auto i = 0; i < n; ++i)
	{
		scanf("%d", &h);
		heights[i] = h;
	}

	int q, k;
	scanf("%d", &q);
	while (q--)
	{
		int c = 0;
		scanf("%d", &k);
		for (auto i = 0; i < n; ++i)
		{
			if (!(heights[i] % k))
			{
				++c;
			}
		}

		printf("%d\n", c);
	}

	return 0;
}
