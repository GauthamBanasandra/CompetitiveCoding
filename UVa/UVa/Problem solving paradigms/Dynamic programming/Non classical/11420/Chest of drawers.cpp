// WIP

#include <vector>
#include <iostream>

class Counter
{
public:
	Counter(std::size_t n, std::size_t s);
	long Count() { return Count(0, true, s_); }

private:
	long Count(std::size_t i, bool is_prev_lock, int rem);

	const std::size_t n_;
	const std::size_t s_;
	std::vector<std::vector<std::vector<long>>> memo_;
};

Counter::Counter(const std::size_t n, const std::size_t s) :n_(n), s_(s)
{
	memo_.resize(n_, std::vector<std::vector<long>>(2, std::vector<long>(s_ + 1, -1)));
}

long Counter::Count(const std::size_t i, const bool is_prev_lock, const int rem)
{
	if (rem == 0)
	{
		return 1;
	}

	if (i >= n_ || rem < 0)
	{
		return 0;
	}

	auto& memo = memo_[i][is_prev_lock ? 1 : 0][rem];
	if (memo != -1)
	{
		return memo;
	}

	const auto unlocked = Count(i + 1, false, rem);
	const auto locked = Count(i + 1, true, rem - (is_prev_lock ? 1 : 0));
	return memo = unlocked + locked;
}

int main(int argc, char* argv[])
{
	Counter counter(3, 1);
	std::cout << counter.Count() << std::endl;
	return 0;
}
