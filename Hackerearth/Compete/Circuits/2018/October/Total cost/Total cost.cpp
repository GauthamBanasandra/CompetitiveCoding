#include <iostream>

using ll = long long;

ll TotalCost(const ll p, int s, const int t, const ll h, const int x)
{
	ll cost = 0;
	for (auto i = 1; i <= x; ++i, --s)
	{
		if (s <= t)
		{
			cost += h;
		}
		else
		{
			cost += p;
		}
	}
	return cost;
}

int main(int argc, char* argv[])
{
	ll p, h;
	int s, t, x;

	std::cin >> p >> s >> t >> h >> x;
	std::cout << TotalCost(p, s, t, h, x);
	return 0;
}
