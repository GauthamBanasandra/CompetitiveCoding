#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

namespace round_551
{
	int GetNextBusTime(const std::vector<std::pair<int, int>>& bus_times, const int t)
	{
		auto index = 0;
		auto i_min_next_bus = -1;
		auto min_next_bus = std::numeric_limits<int>::max();
		for (const auto& bus_time : bus_times)
		{
			++index;
			const auto& [a, d] = bus_time;
			if (t <= a)
			{
				if (a < min_next_bus)
				{
					min_next_bus = a;
					i_min_next_bus = index;
				}
				min_next_bus = std::min(min_next_bus, a);
				continue;
			}

			const auto n = static_cast<int>(std::ceil(
				(t - a) / static_cast<double>(d))) + 1;
			const auto next_bus = a + (n - 1) * d;
			if (next_bus < min_next_bus)
			{
				min_next_bus = next_bus;
				i_min_next_bus = index;
			}
		}
		return i_min_next_bus;
	}
}

int main(int argc, char* argv[])
{
	int num_buses;
	int t;
	std::vector<std::pair<int, int>> bus_times;

	std::cin >> num_buses >> t;
	bus_times.resize(num_buses);
	for (auto i = 0; i < num_buses; ++i)
	{
		std::cin >> bus_times[i].first >> bus_times[i].second;
	}
	std::cout << round_551::GetNextBusTime(bus_times, t) << std::endl;
	return 0;
}
