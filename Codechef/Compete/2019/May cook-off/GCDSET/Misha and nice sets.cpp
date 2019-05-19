// WA

#include <iostream>
#include <cmath>

using ull = long long;

ull CountNiceSetSize(const ull l, const ull r, const ull g)
{
	const auto a = static_cast<ull>(std::ceil(l / static_cast<double>(g))) * g;
	const auto tn = static_cast<ull>(std::floor(r / static_cast<double>(g))) * g;
	return (tn - a) / g + 1;
}

int main(int argc, char* argv[])
{
	int t;
	ull l;
	ull r;
	ull g;

	std::cin >> t;
	while (t--)
	{
		std::cin >> l >> r >> g;
		std::cout << CountNiceSetSize(l, r, g) << std::endl;
	}
	return 0;
}
