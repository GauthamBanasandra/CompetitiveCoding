// TLE
#include <iostream>
#include <vector>
#include <limits>

using ll = long long;

std::vector<ll> MaxSubArraySum(const std::vector<ll>& numbers, const std::vector<std::pair<std::size_t, std::size_t>> & queries)
{
	const auto queries_len = queries.size();
	std::vector<ll> max_sub_array_sum(queries_len);
	for (std::size_t j = 0; j < queries_len; ++j)
	{
		const auto &l = queries[j].first, &r = queries[j].second;
		auto max_sum = std::numeric_limits<ll>::min();
		ll current_sum = 0;
		for (std::size_t i = 0, numbers_len = numbers.size(); i < numbers_len; ++i)
		{
			auto current = numbers[i];
			if ((l <= i) && (i <= r))
			{
				current = numbers[r - i + l];
			}

			current_sum += current;
			if (current_sum > max_sum)
			{
				max_sum = current_sum;
			}
			if (current_sum < 0)
			{
				current_sum = 0;
			}
		}
		max_sub_array_sum[j] = max_sum;
	}
	return max_sub_array_sum;
}

int main(int argc, char* argv[])
{
	std::size_t n, q, l, r;
	std::vector<ll> numbers;
	std::vector<std::pair<std::size_t, std::size_t>> queries;

	std::cin >> n >> q;
	numbers.resize(n);
	queries.resize(q);

	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}
	for (std::size_t i = 0; i < q; ++i)
	{
		std::cin >> l >> r;
		queries[i] = std::make_pair(l - 1, r - 1);
	}

	for (const auto& sum : MaxSubArraySum(numbers, queries))
	{
		std::cout << sum << std::endl;
	}
	return 0;
}
