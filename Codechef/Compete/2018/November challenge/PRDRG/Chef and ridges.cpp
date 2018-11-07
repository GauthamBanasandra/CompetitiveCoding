#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <ios>

struct ProperFraction
{
	ProperFraction() :numerator(0), denominator(1) {}
	ProperFraction(const int numerator, const int denominator) :numerator(numerator), denominator(denominator) {}

	ProperFraction operator-(const ProperFraction& other) const;
	ProperFraction operator+(const ProperFraction& other) const;
	void Halve() { denominator *= 2; }

	int numerator;
	int denominator;
};

ProperFraction ProperFraction::operator-(const ProperFraction& other) const
{
	const auto max_d = std::max(denominator, other.denominator);
	const auto min_d = std::min(denominator, other.denominator);
	assert(max_d % min_d == 0);

	const auto factor = max_d / min_d;

	auto n = 0;
	if (denominator < other.denominator)
	{
		n = numerator * factor - other.numerator;
	}
	else if (denominator > other.denominator)
	{
		n = numerator - other.numerator * factor;
	}
	else
	{
		n = numerator - other.numerator;
	}
	assert(n >= 0);
	assert(n <= max_d);
	return { n, max_d };
}

ProperFraction ProperFraction::operator+(const ProperFraction& other) const
{
	const auto max_d = std::max(denominator, other.denominator);
	const auto min_d = std::min(denominator, other.denominator);
	assert(max_d % min_d == 0);

	const auto factor = max_d / min_d;

	int n = 0;
	if (denominator < other.denominator)
	{
		n = numerator * factor + other.numerator;
	}
	else if (denominator > other.denominator)
	{
		n = numerator + other.numerator * factor;
	}
	else
	{
		n = numerator + other.numerator;
	}
	assert(n < max_d);
	return { n, max_d };
}

class RidgeTracker
{
public:
	explicit RidgeTracker(std::size_t max_n);

	ProperFraction GetRidgeAfter(std::size_t n) const;

private:
	std::size_t max_n_;
	std::vector<std::pair<ProperFraction, ProperFraction>> states_;
};

RidgeTracker::RidgeTracker(const std::size_t max_n) :max_n_(max_n)
{
	states_.resize(max_n_ + 1);
	ProperFraction l{ 0, 1 };
	ProperFraction r{ 1, 1 };

	for (std::size_t i = 0; i <= max_n_; ++i)
	{
		auto m = r - l;
		m.Halve();

		if (i & 1)
		{
			l = l + m;
		}
		else
		{
			r = l + m;
		}

		states_[i] = std::make_pair(l, r);
	}
}

ProperFraction RidgeTracker::GetRidgeAfter(const std::size_t n) const
{
	assert(n <= max_n_);

	if (n & 1)
	{
		return states_[n].second;
	}
	return states_[n].first;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	int t, n;
	std::ostringstream output;
	RidgeTracker tracker(25);

	std::cin >> t;
	for (auto i = 0; i < t; ++i)
	{
		std::cin >> n;
		const auto ridge = tracker.GetRidgeAfter(n);
		output << ridge.numerator << " " << ridge.denominator << " ";
	}

	auto output_str = output.str();
	output_str.pop_back();
	std::cout << output_str << std::endl;
	return 0;
}
