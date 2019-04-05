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

	numbers.pop();
	return  numbers.top();
}

int main(int argc, char* argv[])
{
	int n;
	std::cin >> n;
	std::cout << GetMaximumRemaining(n) << std::endl;
	return 0;
}
