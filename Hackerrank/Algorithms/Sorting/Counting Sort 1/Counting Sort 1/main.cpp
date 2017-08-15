#include <iostream>
#include <vector>

#define MAX_NUM 100

int main(int argc, char* argv[])
{
	unsigned long n;
	std::cin >> n;

	std::vector<int> numbers;
	for (unsigned long i = 0; i < MAX_NUM; ++i)
	{
		numbers.push_back(0);
	}

	int number;
	for (unsigned long i = 0; i < n; ++i)
	{
		std::cin >> number;
		++numbers[number];
	}

	for (auto num : numbers)
	{
		std::cout << num << " ";
	}

	return 0;
}
