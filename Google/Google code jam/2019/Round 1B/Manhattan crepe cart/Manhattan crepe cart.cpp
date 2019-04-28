// WA

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

struct Pos
{
	Pos() = default;
	Pos(const int x, const int y, const char direction)
		: x(x), y(y), direction(direction) {}

	int x{ -1 };
	int y{ -1 };
	char direction{ '\0' };
};

std::pair<int, int> GetPos(const std::vector<Pos>& people)
{
	std::vector<int> heading_north;
	std::vector<int> heading_south;
	std::vector<int> heading_east;
	std::vector<int> heading_west;

	for (const auto& person : people)
	{
		switch (person.direction)
		{
		case 'N':
			heading_north.emplace_back(person.y + 1);
			break;

		case 'S':
			heading_south.emplace_back(person.y - 1);
			break;

		case 'E':
			heading_east.emplace_back(person.x + 1);
			break;

		case 'W':
			heading_west.emplace_back(person.x - 1);
			break;

		default:
			assert(false);
		}
	}

	std::sort(heading_north.begin(), heading_north.end());
	std::sort(heading_south.begin(), heading_south.end());
	std::sort(heading_east.begin(), heading_east.end());
	std::sort(heading_west.begin(), heading_west.end());

	auto x = heading_east.empty() ? 0 : heading_east.back();
	auto y = heading_north.empty() ? 0 : heading_north.back();
	auto x_confidence = static_cast<int>(heading_east.size());
	auto y_confidence = static_cast<int>(heading_north.size());

	if (!heading_north.empty())
	{
		for (auto it = heading_south.begin(); it != heading_south.end(); ++it)
		{
			auto find_north_it = std::upper_bound(
				heading_north.begin(), heading_north.end(), *it);
			const auto find_south_it = std::lower_bound(heading_south.begin(),
				it, *heading_north.begin());


			const auto confidence = std::distance(heading_north.begin(), find_north_it) +
				std::distance(find_south_it, it);
			if (confidence > y_confidence)
			{
				y_confidence = confidence;
				y = *(find_north_it - 1);
			}
		}
	}


	for (auto i = 0, len = static_cast<int>(heading_west.size()); i < len; ++i)
	{
		auto find_it = std::upper_bound(
			heading_east.begin(), heading_east.end(), heading_west[i]);
		const auto confidence = std::distance(heading_east.begin(), find_it) + i + 1;
		if (confidence > x_confidence)
		{
			x_confidence = confidence;
			x = heading_east.empty() ? 0 : *(find_it - 1);
		}
	}
	return std::make_pair(x, y);
}

int main(int argc, char* argv[])
{
	int t;
	int p;
	int q;
	std::vector<Pos> people;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> p >> q;
		people.resize(p);
		for (auto j = 0; j < p; ++j)
		{
			std::cin >> people[j].x >> people[j].y >> people[j].direction;
		}

		const auto pos = GetPos(people);
		std::cout << pos.first << " " << pos.second << std::endl;
	}
	return 0;
}
