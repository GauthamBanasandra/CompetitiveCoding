#include <iostream>
#include <vector>

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

	int number;
	for (unsigned long i = 0; i < n; ++i)
	{
		std::cin >> number;
		++frequencies[number];
	}

	for (int i = 0; i < frequencies.size(); ++i)
	{
		for (int j = 0; j < frequencies[i]; ++j)
		{
			std::cout << i << " ";
		}
	}

	return 0;
}
