#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <cassert>

namespace uva10496
{
	using Matrix = std::vector<std::vector<int>>;
	using Point = std::pair<int, int>;
	const auto infinity = std::numeric_limits<int>::max();

	void Print(const Matrix &matrix);

	class Collector
	{
	public:
		Collector(const std::vector<Point> &beepers_pos);
		int Collect() { return Collect(0, 1); }

	private:
		int Collect(std::size_t i_pos, int visited);

		const int len_;
		Matrix distance_;
		std::vector<std::vector<int>> memo_;
	};

	Collector::Collector(const std::vector<Point>& beepers_pos) :len_(static_cast<int>(beepers_pos.size()))
	{
		const auto len = beepers_pos.size();
		memo_.resize(len, std::vector<int>(1 << len_, -1));

		distance_.resize(len, std::vector<int>(len));
		for (std::size_t i = 0; i < len; ++i)
		{
			const auto &[pi_x, pi_y] = beepers_pos[i];
			for (auto j = i + 1; j < len; ++j)
			{
				const auto &[pj_x, pj_y] = beepers_pos[j];
				distance_[i][j] = distance_[j][i] = std::abs(pi_x - pj_x) + std::abs(pi_y - pj_y);
			}
		}
	}

	int Collector::Collect(const std::size_t i_pos, const int visited)
	{
		if (visited == (1 << len_) - 1)
		{
			return distance_[i_pos][0];
		}

		auto &memo = memo_[i_pos][visited];
		if (memo != -1)
		{
			return memo;
		}

		auto min_distance = infinity;
		for (auto i = 0; i < len_; ++i)
		{
			if (i == static_cast<int>(i_pos) || visited & 1 << i)
			{
				continue;
			}
			min_distance = std::min(min_distance, distance_[i_pos][static_cast<std::size_t>(i)] +
				Collect(i, visited | 1 << i));
		}
		return memo = min_distance;
	}	
}

int main(int argc, char* argv[])
{
	std::size_t t, num_pos;
	int x, y;

	std::vector<uva10496::Point> pos{
		{1, 1 },
		{2, 3 },
		{5, 5 },
		{9 ,4 },
		{6 ,5 },
	};

	std::cin >> t;
	while (t--)
	{
		std::cin >> x >> y;
		assert(!pos.empty());
		std::cin >> pos[0].first >> pos[0].second;
		std::cin >> num_pos;
		pos.resize(num_pos + 1);
		for (std::size_t i = 0; i < num_pos; ++i)
		{
			std::cin >> pos[i + 1].first >> pos[i + 1].second;
		}

		uva10496::Collector collector(pos);
		std::cout << "The shortest path has length " << collector.Collect() << std::endl;
	}
	return 0;
}