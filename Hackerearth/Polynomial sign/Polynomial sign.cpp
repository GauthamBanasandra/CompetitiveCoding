#include <stdio.h>

using big_int = long long;

int main(int argc, char* argv[])
{
	big_int n, a, recent_a = 0;
	scanf("%lld", &n);
	for (big_int i = 0; i < n + 1; ++i)
	{
		scanf("%lld", &a);
		if (a)
		{
			recent_a = a;
		}
	}

	if (recent_a > 0)
	{
		printf("1 -1\n");
	}
	else if (recent_a < 0)
	{
		printf("-1 1\n");
	}
	else
	{
		printf("0 0\n");
	}

	return 0;
}
