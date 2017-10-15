#include <iostream>
#include <algorithm>
#include <vector>
#include <ios>

#define MAX_N 10010

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::vector<long long> list(MAX_N);
	auto n = 0;

	do
	{
		std::cin >> list[n++];
		nth_element(list.begin(), list.begin() + (n >> 1), list.begin() + n);
		if (!(n & 1))
		{
			nth_element(list.begin(), list.begin() + (n >> 1) - 1, list.begin() + n);
		}

		const auto median = n & 1 ? list[n >> 1] : list[n >> 1] + list[(n >> 1) - 1] >> 1;
		if (!std::cin.eof())
		{
			printf("%lld\n", median);
		}
	} while (!std::cin.eof());

	return 0;
}
