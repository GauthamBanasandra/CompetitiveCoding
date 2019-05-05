#include <vector>
#include <iostream>

namespace week_135
{
	int GCD(const int x, const int y)
	{
		auto gcd = 1;
		for (auto i = 1; i <= x && i <= y; i++)
		{
			if (x % i == 0 && y % i == 0)
				gcd = i;
		}
		return gcd;
	}

	class Solution {
	public:
		bool isBoomerang(std::vector<std::vector<int>>& points) {
			const auto a = points[0];
			const auto b = points[1];
			const auto c = points[2];

			if ((a[0] == b[0] && a[1] == b[1]) ||
				(b[0] == c[0] && b[1] == c[1]) ||
				(a[0] == c[0] && a[1] == c[1]))
			{
				return false;
			}

			auto s1 = std::make_pair(b[1] - a[1], b[0] - a[0]);
			auto s2 = std::make_pair(c[1] - b[1], c[0] - b[0]);
			const auto s1_gcd = GCD(s1.first, s1.second);
			const auto s2_gcd = GCD(s2.first, s2.second);

			s1.first /= s1_gcd;
			s1.second /= s1_gcd;
			s2.first /= s2_gcd;
			s2.second /= s2_gcd;

			if (s1.first == 0 && s2.first == 0)
			{
				return false;
			}

			return !((s1.first == s2.first) && (s1.second == s2.second));
		}
	};
}

int main(int argc, char* argv[])
{
	std::vector<std::vector<int>> points{
		{0,0}, {1, 1}, {1, 1}
	};
	std::cout << week_135::Solution().isBoomerang(points) << std::endl;
	return 0;
}
