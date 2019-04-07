#include <queue>
#include <iostream>

namespace april_challenge_2019
{
	using ll = long long;

	ll GetMaximumRemaining(const int n)
	{
		ll number;
		std::priority_queue<ll> numbers;
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> number;
			numbers.emplace(number);
		}

		const auto biggest = numbers.top();
		numbers.pop();

		while (!numbers.empty() && numbers.top() == biggest)
		{
			numbers.pop();
		}
		return numbers.empty() ? 0 : numbers.top();
	}
}

int main(int argc, char* argv[])
{
	int n;
	std::cin >> n;
	std::cout << april_challenge_2019::GetMaximumRemaining(n) << std::endl;
	return 0;
}
