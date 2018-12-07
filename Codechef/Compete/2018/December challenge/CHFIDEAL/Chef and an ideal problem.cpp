#include <iostream>

void Interact()
{
	std::cout << 1 << std::endl;
	int y;
	std::cin >> y;
	std::cout << (y == 2 ? 3 : 2) << std::endl;
}

int main(int argc, char* argv[])
{
	Interact();
	return 0;
}
