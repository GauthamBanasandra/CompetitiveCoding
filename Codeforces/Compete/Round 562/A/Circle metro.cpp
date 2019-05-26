#include <algorithm>
#include <cmath>
#include <iostream>

namespace round_562
{
	bool IsPossibleToMeet(const int n, const int v_start, const int v_end,
		const int d_start, const int d_end)
	{
		auto v_len = v_end - v_start;
		v_len = v_len < 0 ? v_len + n : v_len;

		auto d_len = d_end - d_start;
		d_len = d_len > 0 ? n - d_len : d_len;
		d_len = std::abs(d_len);

		const auto len = std::min(v_len, d_len);
		for (auto i = 0, v = v_start, d = d_start; i <= len; ++i)
		{
			if (v == d)
			{
				return true;
			}

			++v;
			--d;
			v = v > n ? 1 : v;
			d = d < 1 ? n : d;
		}
		return false;
	}
}

int main(int argc, char* argv[])
{
	int n, v_start, v_end, d_start, d_end;
	std::cin >> n >> v_start >> v_end >> d_start >> d_end;
	std::cout << (round_562::IsPossibleToMeet(n, v_start, v_end, d_start, d_end) ? "YES" : "NO") << std::endl;
	return 0;
}
