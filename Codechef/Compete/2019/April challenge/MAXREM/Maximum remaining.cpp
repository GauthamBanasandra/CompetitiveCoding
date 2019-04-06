// WA

#include <queue>
#include <iostream>

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
	const auto second_biggest = numbers.top();
	return biggest == second_biggest ? 0 : second_biggest;
}

int main(int argc, char* argv[])
{
	int n;
	std::cin >> n;
	std::cout << GetMaximumRemaining(n) << std::endl;
	return 0;
}
