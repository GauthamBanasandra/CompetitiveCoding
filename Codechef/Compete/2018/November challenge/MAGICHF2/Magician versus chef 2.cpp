// WA

#include <iostream>

using ll = long long;

double GetProbability(const ll n, const ll k)
{
	if (n == 1)
	{
		return 1;
	}

	if (n % 2)
	{
		if (n > 2 * k)
		{
			if (n - 2 * k >= 3)
			{
				return static_cast<double>(1) / (n - 2 * k);
			}
			return static_cast<double>(1) / 2;
		}
		return 1;
	}

	if (n > 2 * k)
	{
		return static_cast<double>(1) / (n - 2 * k);
	}
	if (n == 2 * k)
	{
		return static_cast<double>(1) / 2;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	ll t, n, k;
	std::cin >> t;
	while (t--)
	{
		std::cin >> n >> k;
		printf("%lf\n", GetProbability(n, k));
	}
	return 0;
}
