#include <iostream>
#include <string>

void SubhamAndBinaryStrings()
{
	int test_cases;
	std::cin >> test_cases;
	while (test_cases--)
	{
		int bin_str_len;
		std::cin >> bin_str_len;
		std::string bin_str;
		std::cin >> bin_str;
		int ones = 0;
		for (char c : bin_str)
		{
			ones += c - '0';
		}
		
		std::cout << (bin_str_len - ones) << '\n';
	}
}