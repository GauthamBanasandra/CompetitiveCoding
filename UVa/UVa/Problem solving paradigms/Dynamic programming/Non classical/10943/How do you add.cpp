#include <vector>
#include <iostream>

class Counter
{
public:
	Counter(std::size_t n, std::size_t k);

	long Count();

private:
	long Count(std::size_t i_num, int rem);

	const std::size_t n_;
	const std::size_t k_;
	std::vector<std::vector<long>> memo_;
};

Counter::Counter(const std::size_t n, const std::size_t k) : n_(n), k_(k)
{
	memo_.resize(k_, std::vector<long>(n_ + 1, -1));
}

long Counter::Count()
{
	auto count = 0l;
	for (std::size_t i = 0; i <= n_; ++i)
	{
		count += Count(0, n_ - i);
		count = count % 1000000;
	}
	return count;
}

long Counter::Count(const std::size_t i_num, const int rem)
{
	if (i_num >= k_ || rem < 0)
	{
		return 0;
	}

	if (i_num == k_ - 1 && rem == 0)
	{
		return 1;
	}

	auto &memo = memo_[i_num][rem];
	if (memo != -1)
	{
		return memo;
	}

	auto count = 0l;
	for (std::size_t i = 0; i <= n_; ++i)
	{
		count += Count(i_num + 1, rem - i);
		count = count % 1000000;
	}
	return memo = count;
}

int main(int argc, char* argv[])
{
	std::size_t n, k;

	while (std::cin >> n >> k, n || k)
	{
		Counter counter(n, k);
		std::cout << counter.Count() << std::endl;
	}
	return 0;
}
