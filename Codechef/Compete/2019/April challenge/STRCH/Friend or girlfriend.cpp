#include <string>
#include <iostream>


namespace april_challenge_2019
{
	std::size_t Count(const std::string& s, const char x)
	{
		std::size_t count = 0;
		std::size_t i = 0;
		std::size_t j = 0;

		while (j = s.find(x, i), j != std::string::npos)
		{
			const auto n = j - i;
			count += n * (n + 1) / 2;
			i = j + 1;
		}
		if (i < s.size())
		{
			const auto n = s.size() - i;
			count += n * (n + 1) / 2;
		}

		const auto n = s.size();
		count = n * (n + 1) / 2 - count;
		return count;
	}
}

int main(int argc, char* argv[])
{
	int t;
	std::size_t len;
	std::string s = "cc";
	char x = 'c';

	std::cin >> t;
	while (t--)
	{
		std::cin >> len;
		std::cin >> s >> x;
		std::cout << april_challenge_2019::Count(s, x) << std::endl;
	}
	return 0;
}
