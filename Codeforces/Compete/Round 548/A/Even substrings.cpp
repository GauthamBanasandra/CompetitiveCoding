#include <string>
#include <iostream>

namespace round548
{
	int Count(const std::string &number)
	{
		std::size_t count = 0;
		for (std::size_t r = 0, len = number.size(); r < len; ++r)
		{
			if ((number[r] - '0') & 1)
			{
				continue;
			}

			count += r + 1;
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	std::string number;
	std::cin >> number >> number;
	std::cout << round548::Count(number) << std::endl;
	return 0;
}
