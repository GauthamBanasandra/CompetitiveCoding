#include <vector>
#include <algorithm>
#include <iostream>

namespace round550
{
	using ll = long long;

	ll MinimumSum(const std::vector<long> &numbers)
	{
		std::vector<long> even, odd;
		for (const auto number : numbers)
		{
			(number & 1 ? odd : even).emplace_back(number);
		}

		std::sort(odd.begin(), odd.end());
		std::sort(even.begin(), even.end());

		if (odd.size() == even.size() ||
			abs(static_cast<long>(odd.size()) - static_cast<long>(even.size())) == 1)
		{
			return 0;
		}

		if (odd.size() < even.size())
		{
			ll sum = 0;
			for (std::size_t i = 0, len = even.size() - odd.size(); i < len - 1; ++i)
			{
				sum += even[i];
			}
			return sum;
		}

		ll sum = 0;
		for (std::size_t i = 0, len = odd.size() - even.size(); i < len - 1; ++i)
		{
			sum += odd[i];
		}
		return sum;
	}
}

int main(int argc, char* argv[])
{
	std::size_t n;
	std::cin >> n;

	std::vector<long> numbers(n);
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}

	std::cout << round550::MinimumSum(numbers) << std::endl;
	return 0;
}
