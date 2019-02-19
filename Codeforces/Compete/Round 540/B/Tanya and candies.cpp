#include <vector>
#include <iostream>

int CountGoodCandies(const std::vector<int> &candies)
{
	auto num_good_candies = 0;
	long long odd_weight = 0, even_weight = 0;

	const auto len = candies.size();
	for (std::size_t i = 0; i < len; ++i)
	{
		if (i & 1)
		{
			odd_weight += candies[i];
		}
		else
		{
			even_weight += candies[i];
		}
	}

	for (std::size_t i = 0; i < len; ++i)
	{
		auto odd = odd_weight;
		auto even = even_weight;
		if (i & 1)
		{
			odd -= candies[i];
		}
		else
		{
			even -= candies[i];
		}

		if (odd == even)
		{
			++num_good_candies;
		}
	}

	return num_good_candies;
}

int main(int argc, char* argv[])
{
	//std::vector<int> candies{ 4, 8, 8, 7, 8, 4, 4, 5 };
	std::vector<int> candies{ 2, 3, 4, 2, 2, 3, 2, 2, 4 };
	std::cout << CountGoodCandies(candies) << std::endl;
	return 0;
}
