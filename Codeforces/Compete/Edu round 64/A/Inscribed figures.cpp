// WA

#include <vector>
#include <iostream>

namespace edu_round_64
{
	const auto circle = 1;
	const auto triangle = 2;
	const auto square = 3;

	int CountIntersectingPoints(const std::vector<int>& figures,
		const int num_figures)
	{
		auto count = 0;
		for (auto i = num_figures - 1; i > 0; --i)
		{
			if (figures[i] == circle && figures[i - 1] == square ||
				figures[i] == square && figures[i - 1] == circle)
			{
				count += 4;
			}
			else if (figures[i] == circle && figures[i - 1] == triangle ||
				figures[i] == triangle && figures[i - 1] == circle)
			{
				count += 3;
			}
			else if (figures[i] == square && figures[i - 1] == triangle ||
				figures[i] == triangle && figures[i - 1] == square)
			{
				return -1;
			}
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	int num_figures;

	std::cin >> num_figures;
	std::vector<int> figures(num_figures);
	for (auto i = 0; i < num_figures; ++i)
	{
		std::cin >> figures[i];
	}

	const auto count = edu_round_64::CountIntersectingPoints(figures, num_figures);
	if (count == -1)
	{
		std::cout << "Infinite" << std::endl;
	}
	else
	{
		std::cout << "Finite" << std::endl << count << std::endl;
	}
	return 0;
}
