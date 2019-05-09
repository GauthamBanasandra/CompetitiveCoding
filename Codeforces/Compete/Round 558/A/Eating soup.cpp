#include <iostream>

namespace round_558
{
	int GetMaximumGroups(const int n, const int m)
	{
		if (n == 0)
		{
			return 0;
		}
		if (m == 0)
		{
			return 1;
		}

		if (m > n >> 1)
		{
			return n - m;
		}
		return m;
	}
}

int main(int argc, char* argv[])
{
	int n;
	int m;

	std::cin >> n >> m;
	std::cout << round_558::GetMaximumGroups(n, m) << std::endl;
	return 0;
}
