#include <vector>
#include <algorithm>
#include <iostream>

namespace round_554
{
	long NumOpenChests(const std::vector<long>& chests,
	                   const std::vector<long>& keys, const int num_chests, const int num_keys)
	{
		const auto num_chests_odd = std::count_if(chests.begin(), chests.end(),
		                                          [](const long& number)->bool
		                                          {
			                                          return number & 1;
		                                          });
		const auto num_chests_even = num_chests - num_chests_odd;

		const auto num_keys_odd = std::count_if(keys.begin(), keys.end(),
		                                        [](const long& number)->bool
		                                        {
			                                        return number & 1;
		                                        });
		const auto num_keys_even = num_keys - num_keys_odd;

		return std::min(num_chests_even, num_keys_odd) +
			std::min(num_chests_odd, num_keys_even);
	}
}

int main(int argc, char* argv[])
{
	int num_chests;
	int num_keys;

	std::cin >> num_chests >> num_keys;

	std::vector<long> chests(num_chests);
	std::vector<long> keys(num_keys);
	for (auto i = 0; i < num_chests; ++i)
	{
		std::cin >> chests[i];
	}
	for (auto i = 0; i < num_keys; ++i)
	{
		std::cin >> keys[i];
	}

	std::cout << round_554::NumOpenChests(chests, keys, num_chests, num_keys) << std::endl;
	return 0;
}
