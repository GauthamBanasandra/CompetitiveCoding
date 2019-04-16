// WA

#include <vector>
#include <iostream>

namespace round_552
{
	int GetMinimumD(std::vector<int>& numbers)
	{
		std::vector<int> adj_diff(numbers.size());
		std::vector<int> adj_add(numbers.size());
		std::vector<int> adj_sub(numbers.size());
		std::vector<int> adj_nothing(numbers.size());

		int d;
		for (d = 0; d < 101; d++)
		{
			adj_nothing[0] = numbers[0];
			adj_add[0] = numbers[0] + d;
			adj_sub[0] = numbers[0] - d;

			std::size_t i;
			const auto len = numbers.size();
			for (i = 1; i < len; ++i)
			{
				adj_nothing[i] = numbers[i];
				adj_add[i] = numbers[i] + d;
				adj_sub[i] = numbers[i] - d;

				if (adj_nothing[i] == adj_add[i - 1] || adj_nothing[i] == adj_sub[i - 1] || adj_nothing[i] == adj_nothing[i - 1])
				{
					continue;
				}

				if (adj_add[i] == adj_add[i - 1] || adj_add[i] == adj_sub[i - 1] || adj_add[i] == adj_nothing[i - 1])
				{
					continue;
				}

				if (adj_sub[i] == adj_add[i - 1] || adj_sub[i] == adj_sub[i - 1] || adj_sub[i] == adj_nothing[i - 1])
				{
					continue;
				}
				break;
			}
			if (i == len)
			{
				break;
			}
		}
		return d;
	}
}

int main(int argc, char* argv[])
{
	int n;
	std::cin >> n;

	std::vector<int> numbers(n);

	for (auto i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}
	std::cout << round_552::GetMinimumD(numbers) << std::endl;
	return 0;
}
