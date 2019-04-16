#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

namespace round_552
{
	std::tuple<long, long, long> GetNumbers(std::vector<long>& numbers)
	{
		std::sort(numbers.begin(), numbers.end());
		const auto abc = numbers.back();
		const auto ab = numbers[0];
		const auto ac = numbers[1];
		const auto bc = numbers[2];

		const auto c = abc - ab;
		const auto a = ac - c;
		const auto b = bc - c;
		return std::make_tuple(a, b, c);
	}
}

int main(int argc, char* argv[])
{
	std::vector<long> numbers(4);
	std::cin >> numbers[0];
	std::cin >> numbers[1];
	std::cin >> numbers[2];
	std::cin >> numbers[3];

	const auto [a, b, c] = round_552::GetNumbers(numbers);
	std::cout << a << ' ' << b << ' ' << c << std::endl;
	return 0;
}
