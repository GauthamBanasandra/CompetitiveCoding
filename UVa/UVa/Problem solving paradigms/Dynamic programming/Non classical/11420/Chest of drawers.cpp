#include <vector>
#include <iostream>

using ll = long long;

class Counter
{
public:
	Counter(std::size_t n, int s);
	ll Count() { return Count(0, true, 0); }

private:
	ll Count(std::size_t i, bool is_prev_lock, int s);

	const std::size_t n_;
	const int s_;
	std::vector<std::vector<std::vector<ll>>> memo_;
};

Counter::Counter(const std::size_t n, const int s) :n_(n), s_(s)
{
	memo_.resize(n_, std::vector<std::vector<ll>>(2, std::vector<ll>(n_ + 1, -1)));
}

/*
 * Using "rem" all the time isn't going to work.
 * By "rem", I mean passing the remaining and subtracting it till "rem" reaches 0.
 * 
 * In this case, it will prune the branches. But the problem needs to explore
 * all the branches and count them, even if the solution is reached
 * 
 * For example,
 * Let's say n = 3 and s = 1. We get the following possibilities (U - Unlocked, L - Locked)
 * U U U
 * U U L
 * U L U
 * U L L
 * L U U
  -------
 | L U L |  These permutations are pruned because s = 0, on the first recursion itself
 | L L U |	and will return immediately without exploring the subsequent positions
 | L L L |
  -------

 * The code looks like this for "rem" logic
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
 */
ll Counter::Count(const std::size_t i, const bool is_prev_lock, const int s)
{
	if (i >= n_)
	{
		if (s == s_)
		{
			return 1;
		}
		return 0;
	}

	auto& memo = memo_[i][is_prev_lock ? 1 : 0][s];
	if (memo != -1)
	{
		return memo;
	}

	const auto unlocked = Count(i + 1, false, s);
	const auto locked = Count(i + 1, true, s + (is_prev_lock ? 1 : 0));
	return memo = unlocked + locked;
}

int main(int argc, char* argv[])
{
	ll n;
	int s;

	while (std::cin >> n >> s, n != -1 && s != -1)
	{
		Counter counter(n, s);
		std::cout << counter.Count() << std::endl;
	}
	return 0;
}
