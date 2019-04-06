#include <string>
#include <algorithm>
#include <iostream>

namespace q2019
{
	std::pair<std::string, std::string> Split(const std::string& number)
	{
		std::string a(number.size(), '0');
		std::string b(number.size(), '0');

		for (std::size_t i = 0, len = number.size(); i < len; ++i)
		{
			if (number[i] != '4')
			{
				a[i] = number[i];
			}
			else
			{
				a[i] = '3';
				b[i] = '1';
			}
		}

		std::string new_b(std::find_if(b.begin(), b.end(),
			[](const char& x)->bool {return x != '0'; }), b.end());
		return { a, new_b };
	}
}

int main(int argc, char* argv[])
{
	int t;
	std::string number;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> number;
		auto ab = q2019::Split(number);
		std::cout << "Case #" << i << ": " << ab.first << ' ' << ab.second << std::endl;
	}
	return 0;
}
