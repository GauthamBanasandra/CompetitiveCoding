#include <vector>
#include <algorithm>
#include <iostream>

class Estimator
{
public:
	Estimator(long long num_l, long long cost_1l, long long cost_2l);
	long long Estimate() const;

private:
	const long long num_l_;
	const long long cost_1l_;
	const long long cost_2l_;
};

Estimator::Estimator(long long num_l, long long cost_1l, long long cost_2l) :num_l_(num_l), cost_1l_(cost_1l), cost_2l_(cost_2l)
{
}

long long Estimator::Estimate() const
{
	long long max_2 = num_l_ / 2 * cost_2l_;
	if (num_l_ & 1)
	{
		max_2 += cost_1l_;
	}

	const long long max_1 = num_l_ * cost_1l_;
	return std::min(max_1, max_2);
}

int main(int argc, char* argv[])
{
	long long q, n, a, b;

	std::cin >> q;
	while (q--)
	{
		std::cin >> n >> a >> b;
		Estimator estimator(n, a, b);
		std::cout << estimator.Estimate() << std::endl;
	}
	return 0;
}
