#include <string>
#include <iostream>
#include <ios>

bool IsBeautiful(const std::string &garland)
{
	const auto len = garland.length();
	if (len == 1)
	{
		return true;
	}

	auto rr = 0, gg = 0;
	if (len > 2)
	{
		const auto front = garland.front(), back = garland.back();
		if (front == 'R' && back == 'R')
		{
			++rr;
		}
		else if (front == 'G' && back == 'G')
		{
			++gg;
		}
	}

	for (std::size_t i = 0; i < len - 1; ++i)
	{
		if (garland[i] == 'R' && garland[i + 1] == 'R')
		{
			++rr;
		}
		else if (garland[i] == 'G' && garland[i + 1] == 'G')
		{
			++gg;
		}
	}
	return (rr == 0 && gg == 0) || (rr == 1 && gg == 1);
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t t;
	std::string garland;

	std::cin >> t;
	while (t--)
	{
		std::cin >> garland;
		std::cout << (IsBeautiful(garland) ? "yes" : "no") << std::endl;
	}
	return 0;
}
