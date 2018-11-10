#include <algorithm>
#include <iostream>

using ll = long long;

double GetProbability(ll n, ll k)
{
	if (n == 2)
	{
		return static_cast<double>(1) / 2;
	}

	auto have_fake = false;
	while (n > 1 && k > 0)
	{
		const auto half = (n + (n & 1 ? 1 : 0)) / 2; // Ceil if n is odd
		auto in = std::max(half, n - half); // Will be used in balance
		auto out = std::min(half, n - half); // Will not be used in balance
		if (in & 1 && !have_fake)
		{
			--in;
			++out;
		}
		n = std::max(in, out); // Guarantees minimum probability
		--k;
		have_fake = true;
	}
	return static_cast<double>(1) / n;
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
