#include <algorithm>
#include <string>
#include <iostream>

namespace round550
{
	bool IsDiverseString(std::string& str)
	{
		std::sort(str.begin(), str.end());
		for (std::size_t i = 0, len = str.size(); i < len - 1; ++i)
		{
			if (str[i + 1] != str[i] + 1)
			{
				return false;
			}
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	int n;
	std::string str;

	std::cin >> n;
	for (auto i = 0; i < n; ++i)
	{
		std::cin >> str;
		std::cout << (round550::IsDiverseString(str) ? "Yes" : "No") << std::endl;
	}
	return 0;
}
