#include <iostream>

void CountTheBits()
{
	int test_cases = 0,
		n = 0,
		count = 0;

	std::cin >> test_cases;
	while (test_cases--)
	{
		count = 0;
		std::cin >> n;
		while (n)
		{
			n = n & (n - 1);
			++count;
		}

		std::cout << count << '\n';
	}
}