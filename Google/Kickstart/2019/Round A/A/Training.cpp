#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using ll = long long;

const auto infinity = std::numeric_limits<ll>::max();

ll GetMinHoursRequired(std::vector<int> &skill, const int num_select)
{
	std::sort(skill.begin(), skill.end());
	const auto len = skill.size();

	std::vector<ll> cum_sum(len);
	cum_sum[0] = skill[0];
	for (std::size_t i = 1; i < len; ++i)
	{
		cum_sum[i] = skill[i] + cum_sum[i - 1];
	}

	auto min_hours = infinity;
	for (std::size_t i = 0, j = num_select - 1; j < len; ++i, ++j)
	{
		const auto sum = cum_sum[j] - (i == 0 ? 0 : cum_sum[i - 1]);
		const auto diff_sum = num_select * skill[j] - sum;
		min_hours = std::min(min_hours, diff_sum);
	}
	return min_hours;
}

int main(int argc, char* argv[])
{
	int t;
	ll n;
	ll p;
	std::vector<int> skill;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> n >> p;
		skill.resize(n);
		for (long j = 0; j < n; ++j)
		{
			std::cin >> skill[j];
		}

		std::cout << "Case #" << i << ": " << GetMinHoursRequired(skill, p) << std::endl;
	}
	return 0;
}
