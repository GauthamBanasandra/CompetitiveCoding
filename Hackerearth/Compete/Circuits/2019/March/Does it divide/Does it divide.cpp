// WA

#include <iostream>

using ull = unsigned long long;

bool IsDivisible(const ull n)
{
	if (n == 1)
	{
		return true;
	}
	if ((n & 1) == 0)
	{
		return false;
	}

	return (n + 1) / 2 <= n - 1;
}

int main(int argc, char* argv[])
{
	int t;
	ull n;

	std::cin >> t;
	for (auto i = 0; i < t; ++i)
	{
		std::cin >> n;
		std::cout << (IsDivisible(n) ? "YES" : "NO") << std::endl;
	}
	return 0;
}
