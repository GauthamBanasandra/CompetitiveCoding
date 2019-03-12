#include <iostream>

#include "ab.h"

int main(int argc, char* argv[])
{
	int n, k;
	std::cin >> n >> k;
	std::cout << AB::createString(n, k) << std::endl;
	return 0;
}
