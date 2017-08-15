#include <iostream>
#include <string>
#include <set>
#include <cstdint>

void JarvisAndLoneInteger()
{
	int test_cases;
	std::cin >> test_cases;
	while (test_cases--)
	{
		int n_len;
		std::cin >> n_len;
		std::set<uint_fast64_t> n_set;
		for (int i = 0; i < n_len; ++i)
		{
			uint_fast64_t n;
			std::cin >> n;
			auto key = n_set.find(n);
			if (key == n_set.end())
			{
				n_set.insert(n);
			}
			else
			{
				n_set.erase(key);
			}
		}

		if (n_set.size())
		{
			std::cout << *n_set.begin() << '\n';
		}
		else
		{
			std::cout << -1 << '\n';
		}
	}
}