#include <vector>
#include <algorithm>
#include <iostream>

namespace round548
{
	using ll = long long;
	ll Count(std::vector<ll> &chocolates)
	{
		auto count = chocolates.back();
		for (auto i = static_cast<long>(chocolates.size()) - 2; i >= 0; --i)
		{
			if (chocolates[i] < chocolates[i + 1] || chocolates[i] == 0)
			{
				count += chocolates[i];
				continue;
			}

			chocolates[i] = std::max(0ll, chocolates[i + 1] - 1);
			count += chocolates[i];
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	std::size_t num_chocolates;
	std::cin >> num_chocolates;
	std::vector<round548::ll> chocolates(num_chocolates);
	for (std::size_t i = 0; i < num_chocolates; ++i)
	{
		std::cin >> chocolates[i];
	}
	std::cout << round548::Count(chocolates) << std::endl;
	return 0;
}
