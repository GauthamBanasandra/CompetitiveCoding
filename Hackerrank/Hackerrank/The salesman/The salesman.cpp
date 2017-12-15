#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <math.h>

int main(int argc, char* argv[])
{
	int t, n, loc;
	long long time = 0;
	std::string line;
	std::priority_queue<int> street;
	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		std::cin.ignore();
		time = 0;
		while (!street.empty())
		{
			street.pop();
		}

		getline(std::cin, line);
		std::istringstream tokenizer(line);
		while (tokenizer >> loc)
		{
			street.push(loc);
		}

		if (street.size() == 1)
		{
			time = 0;
		}
		else
		{
			auto prev = street.top();
			street.pop();
			while (!street.empty())
			{
				time += abs(prev - street.top());
				prev = street.top();
				street.pop();
			}
		}

		std::cout << time << std::endl;
	}

	return 0;
}
