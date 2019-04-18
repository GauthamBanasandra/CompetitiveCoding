#include <string>
#include <limits>
#include <algorithm>
#include <iostream>

namespace round_553
{
	int GetMinimumOperations(const std::string& s)
	{
		auto min_operations = std::numeric_limits<int>::max();
		for (auto i = 0, len = static_cast<int>(s.size()); i <= len - 4; ++i)
		{
			auto operations = std::min(s[i] - 'A', 'Z' - s[i] + 1);
			if (s[i + 1] <= 'C')
			{
				operations += std::min('C' - s[i + 1], s[i + 1] - 'A' + 'Z' - 'C' + 1);
			}
			else
			{
				operations += std::min(s[i + 1] - 'C', 'Z' - s[i + 1] + 'C' - 'A' + 1);
			}

			if (s[i + 2] <= 'T')
			{
				operations += std::min('T' - s[i + 2], s[i + 2] - 'A' + 'Z' - 'T' + 1);
			}
			else
			{
				operations += std::min(s[i + 2] - 'T', 'Z' - s[i + 2] + 'T' - 'A' + 1);
			}

			if (s[i + 3] <= 'G')
			{
				operations += std::min('G' - s[i + 3], s[i + 3] - 'A' + 'Z' - 'G' + 1);
			}
			else
			{
				operations += std::min(s[i + 3] - 'G', 'Z' - s[i + 3] + 'G' - 'A' + 1);
			}

			min_operations = std::min(min_operations, operations);
		}
		return min_operations;
	}
}

int main(int argc, char* argv[])
{
	int n;
	std::string s;

	std::cin >> n >> s;
	std::cout << round_553::GetMinimumOperations(s) << std::endl;
	return 0;
}
