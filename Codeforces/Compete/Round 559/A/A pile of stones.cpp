#include <string>
#include <iostream>
#include <cassert>

namespace round_559
{
	int GetMinimumPossibleStones(const std::string& ops)
	{
		auto a = 0;
		auto b = 0;

		for (const auto op : ops)
		{
			if (op == '-' && a == 0)
			{
				++b;
			}
			else if (op == '-' && a != 0)
			{
				--a;
				++b;
			}
			else if (op == '+' && b == 0)
			{
				++a;
			}
			else if (op == '+' && b != 0)
			{
				--b;
				++a;
			}
			else
			{
				assert(false && "Not handled");
			}
		}
		return a;
	}
}

int main(int argc, char* argv[])
{
	int n;
	std::string ops;

	std::cin >> n >> ops;
	std::cout << round_559::GetMinimumPossibleStones(ops) << std::endl;
	return 0;
}
