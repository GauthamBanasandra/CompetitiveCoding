#include <stdio.h>
#include <ios>

void DivisionOfNlogonia()
{
	std::ios::sync_with_stdio(false);

	int k;
	long long x, y, a, b;

	while (true)
	{
		scanf("%d", &k);
		if (!k)
		{
			break;
		}

		scanf("%lld%lld", &x, &y);
		while (k--)
		{
			scanf("%lld%lld", &a, &b);
			if (x == a || y == b)
			{
				printf("divisa\n");
			}
			else if (x > a && y < b)
			{
				printf("NO\n");
			}
			else if (x < a && y < b)
			{
				printf("NE\n");
			}
			else if (x < a && y > b)
			{
				printf("SE\n");
			}
			else if (x > a && y > b)
			{
				printf("SO\n");
			}
		}
	}
}