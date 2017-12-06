#include <map>
#include <string>
#include <iostream>
#include <iomanip>

using big_int = long long;

int main(int argc, char* argv[])
{
	big_int n, tree_count = 0, c = 0;
	std::string line;
	std::map<std::string, long long> species_count;

	scanf("%lld\n", &n);
	while (n--)
	{
		tree_count = 0;
		species_count.clear();
		while (getline(std::cin, line), line.length() != 0)
		{
			++tree_count;
			++species_count[line];
		}

		if (c++ > 0)
		{
			printf("\n");
		}

		for (const auto &species : species_count)
		{
			const auto percentage = 100.0 * species.second / tree_count;
			std::cout << species.first << " " << std::setprecision(4) << std::fixed << percentage << std::endl;
		}
	}

	return 0;
}
