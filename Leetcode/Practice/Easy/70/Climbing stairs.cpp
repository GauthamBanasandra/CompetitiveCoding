#include <vector>
#include <iostream>

class Counter
{
public:
	explicit Counter(int rem);

	int Count() { return Count(rem_); }

private:
	int Count(int rem);

	const int rem_;
	std::vector<int> memo_;
};

Counter::Counter(const int rem) :rem_(rem)
{
	memo_.resize(rem_ + 1, -1);
}

int Counter::Count(const int rem)
{
	if (rem < 0)
	{
		return 0;
	}
	if (rem == 0)
	{
		return 1;
	}

	auto& memo = memo_[rem];
	if (memo != -1)
	{
		return memo;
	}
	return memo = Count(rem - 1) + Count(rem - 2);
}

class Solution
{
public:
	static int climbStairs(int n);
};

int Solution::climbStairs(const int n)
{
	return Counter(n).Count();
}

int main(int argc, char* argv[])
{
	std::cout << Solution::climbStairs(2) << std::endl;
	return 0;
}
