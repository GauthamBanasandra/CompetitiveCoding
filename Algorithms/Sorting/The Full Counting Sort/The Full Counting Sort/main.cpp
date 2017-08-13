#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <math.h>

#define MAX_NUM 100

int main(int argc, char* argv[])
{
	unsigned long n;
	std::cin >> n;

	std::vector<int> frequencies;
	for (unsigned long i = 0; i < MAX_NUM; ++i)
	{
		frequencies.push_back(0);
	}

	unsigned long half_point = floor(n / 2.0);
	std::map<int, std::queue<std::string>> kv;
	int number;
	std::string str_value;
	for (unsigned long i = 0; i < n; ++i)
	{
		std::cin >> number;
		++frequencies[number];

		std::cin >> str_value;
		if (i < half_point)
		{
			kv[number].push("-");
		}
		else
		{
			kv[number].push(str_value);
		}
	}

	for (int i = 0; i < frequencies.size(); ++i)
	{
		for (int j = 0; j < frequencies[i]; ++j)
		{
			std::cout << kv[i].front() << " ";
			kv[i].pop();
		}
	}

	return 0;
}
