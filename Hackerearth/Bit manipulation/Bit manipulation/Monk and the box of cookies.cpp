#include <iostream>
#define MAX_BITS 32

void MonkAndTheBoxOfCookies()
{
	int test_cases;
	std::cin >> test_cases;
	while (test_cases--)
	{
		int bits[MAX_BITS];
		for (int i = 0; i < MAX_BITS; ++i)
		{
			bits[i] = 0;
		}

		int balls;
		std::cin >> balls;
		while (balls--)
		{
			unsigned long n;
			std::cin >> n;
			if (n != 0)
			{
				for (int i = 0; i < MAX_BITS; ++i)
				{
					if (n&(1 << i))
					{
						++bits[i];
					}
				}
			}
		}

		int max_idx = 0;
		for (int i = 1; i < MAX_BITS - 1; ++i)
		{
			if (bits[i] > bits[max_idx])
			{
				max_idx = i;
			}
		}

		std::cout << max_idx << '\n';
	}
}