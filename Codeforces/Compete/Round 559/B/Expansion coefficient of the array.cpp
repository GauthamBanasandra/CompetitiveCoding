// WA

#include <vector>
#include <algorithm>
#include <iostream>

namespace round_559
{
	using ll = long long;

	ll GetExpansionCoefficient(const std::vector<ll>& numbers)
	{
		const auto len = static_cast<ll>(numbers.size());
		const auto c1 = std::min(numbers.front(), numbers.back()) / (len - 1);

		const auto min_it = std::min_element(numbers.begin(), numbers.end());
		const auto i_min = static_cast<ll>(std::distance(numbers.begin(), min_it)) + 1;
		const auto distance = i_min == 1 ? len - 1 : std::max(i_min - 1, len - i_min);
		const auto c2 = *min_it / distance;
		return std::min(c1, c2);
	}
}

int main(int argc, char* argv[])
{
	std::size_t n;
	std::cin >> n;

	std::vector<round_559::ll> numbers(n);
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}
	std::cout << round_559::GetExpansionCoefficient(numbers) << std::endl;
	return 0;
}
