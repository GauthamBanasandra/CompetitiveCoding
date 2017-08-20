#include <stdio.h>
#include <ios>

void HorrorDash()
{
	std::ios::sync_with_stdio(false);

	int T, c = 1;
	scanf("%d", &T);
	while (T--)
	{
		int N, max_speed, speed;
		scanf("%d%d", &N, &max_speed);
		for (int i = 0; i < N - 1; ++i)
		{
			scanf("%d", &speed);
			if (speed > max_speed)
			{
				max_speed = speed;
			}
		}

		printf("Case %d: %d\n", c++, max_speed);
	}
}