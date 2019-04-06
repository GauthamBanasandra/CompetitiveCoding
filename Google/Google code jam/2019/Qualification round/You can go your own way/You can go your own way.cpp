#include <string>
#include <iostream>

namespace q2019
{
	std::string GetOwnPath(const std::string& path_lydia)
	{
		std::string path_own(path_lydia.size(), '\0');
		for (std::size_t i = 0, len = path_lydia.size(); i < len; ++i)
		{
			path_own[i] = path_lydia[i] == 'E' ? 'S' : 'E';
		}
		return path_own;
	}
}

int main(int argc, char* argv[])
{
	int t;
	std::size_t len;
	std::string path_lydia;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> len >> path_lydia;
		std::cout << "Case #" << i << ": " << q2019::GetOwnPath(path_lydia) << std::endl;
	}
	return 0;
}
