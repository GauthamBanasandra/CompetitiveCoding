#include <limits>
#include <iostream>

const auto max_int = std::numeric_limits<int>::max();
const auto min_int = std::numeric_limits<int>::min();

int Reverse(int number)
{
	const auto is_negative = number < 0;
	// Can't do anything with min int as it would overflow when reversed
	if (number == min_int)
	{
		return 0;
	}
	number = is_negative ? number * -1 : number;

	auto reverse = 0;
	while (number > 0)
	{
		// Check for multiplication overflow before doing anything
		if (reverse > max_int / 10 ||
			reverse < min_int / 10)
		{
			return 0;
		}
		reverse *= 10;
		reverse += number % 10;
		number /= 10;
	}
	return is_negative ? reverse * -1 : reverse;
}

class Solution {
public:
	static int reverse(int x);
};

int Solution::reverse(const int x)
{
	return Reverse(x);
}

int main(int argc, char* argv[])
{
	std::cout << Solution::reverse(15349) << std::endl;
	return 0;
}
