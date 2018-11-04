// WA

#include <iostream>
#include <sstream>

using ll = long long;

struct Fraction
{
	Fraction() :numerator(0ll), denominator(0ll) {}
	Fraction(const ll numerator, const ll denominator) :numerator(numerator), denominator(denominator) {}

	ll numerator;
	ll denominator;
};

Fraction GetRidgeWidth(const ll num_folds)
{
	return { 1, 1 << num_folds };
}

int main(int argc, char* argv[])
{
	int t;
	ll n;
	std::ostringstream output;

	std::cin >> t;
	for (auto i = 0; i < t; ++i)
	{
		std::cin >> n;
		const auto fraction = GetRidgeWidth(n);
		output << fraction.numerator << " " << fraction.denominator << " ";
	}

	auto output_str = output.str();
	output_str.pop_back();
	std::cout << output_str << std::endl;
	return 0;
}
