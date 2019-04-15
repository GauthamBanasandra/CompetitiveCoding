// WA

#include <string>
#include <iostream>

using ll = long long;

ll SubstringSum(const std::string& num_str)
{
	ll sum = 0;
	for (std::size_t i = 0, len = num_str.size(); i < len; ++i)
	{
		for (auto j = i + 1; j <= len; ++j)
		{
			auto str = std::string(
				num_str.begin() + i, num_str.begin() + j);
			std::cout << i << ' ' << j << ' ' << str << std::endl;
			const auto number = std::stoi(str);
			sum += number;
			sum %= 1000000007;
		}
	}
	return sum;
}

int main(int argc, char* argv[])
{
	std::string num_str;
	std::cin >> num_str;
	std::cout << SubstringSum(num_str) << std::endl;
	return 0;
}
