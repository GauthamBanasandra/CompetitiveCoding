#include <queue>
#include <cmath>
#include <iostream>

namespace april_cook_off_2019
{
	long GetMinContributions(std::priority_queue<long>& contributors,
		const long init_pied_piper, const long init_hooli,
		const long gain_pied_piper, const long gain_hooli,
		const long win_target)
	{
		const long target = std::ceil((win_target - init_hooli) / static_cast<double>(gain_hooli));
		long target_pied_piper = std::ceil((win_target - init_pied_piper) / static_cast<double>(gain_pied_piper));

		long count = 0;
		long contributions = 0;
		while (!contributors.empty() && target_pied_piper >= target)
		{
			auto contribution = contributors.top();
			contributors.pop();

			contributions += contribution;
			target_pied_piper = std::ceil(
				(win_target - init_pied_piper - contributions) / static_cast<double>(gain_pied_piper));

			contribution >>= 1;
			if (contribution != 0)
			{
				contributors.push(contribution);
			}
			++count;
		}

		if (!contributors.empty() || target_pied_piper < target)
		{
			return count;
		}
		return target_pied_piper >= target ? -1 : count;
	}
}

int main(int argc, char* argv[])
{
	int t;
	long n, a, b, x, y, z, c;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n >> a >> b >> x >> y >> z;
		std::priority_queue<long> contributors;
		while (n--)
		{
			std::cin >> c;
			contributors.push(c);
		}

		const auto min_contributions = april_cook_off_2019::GetMinContributions(
			contributors, a, b, x, y, z);
		if (min_contributions == -1)
		{
			std::cout << "RIP" << std::endl;
		}
		else
		{
			std::cout << min_contributions << std::endl;
		}
	}
	return 0;
}
