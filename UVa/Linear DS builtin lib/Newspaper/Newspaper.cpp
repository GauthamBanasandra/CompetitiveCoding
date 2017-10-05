#include <iostream>
#include <ios>
#include <unordered_map>
#include <string>

using big_int = unsigned long long;

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n, k, cost;
	char ch;
	big_int total_cost, m;
	std::string line;
	std::unordered_map<char, int> char_cost;

	scanf("%d\n", &n);
	while (n--)
	{
		char_cost.clear();
		total_cost = 0;
		scanf("%d\n", &k);
		while (k--)
		{
			scanf("%c %d\n", &ch, &cost);
			char_cost[ch] = cost;
		}

		scanf("%llu\n", &m);
		while (m--)
		{
			getline(std::cin, line);
			for (const auto c : line)
			{
				total_cost += char_cost[c];
			}
		}

		printf("%0.2lf$\n", total_cost / 100.0);
	}

	return 0;
}
