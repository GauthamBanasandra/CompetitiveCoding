#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <iostream>

namespace round550
{
	struct Info
	{
		Info(const bool is_possible) :is_possible(is_possible) {}
		Info(const std::unordered_set<long> &increasing, const std::unordered_set<long> &decreasing);

		bool is_possible{ false };
		std::vector<long> increasing;
		std::vector<long> decreasing;
	};

	Info::Info(const std::unordered_set<long>& increasing,
		const std::unordered_set<long>& decreasing) :is_possible(true)
	{
		this->increasing = std::vector<long>(increasing.begin(), increasing.end());
		this->decreasing = std::vector<long>(decreasing.begin(), decreasing.end());

		std::sort(this->increasing.begin(), this->increasing.end());
		std::sort(this->decreasing.begin(), this->decreasing.end(), std::greater<>());
	}

	Info SplitSequence(const std::vector<long> &numbers)
	{
		std::unordered_set<long> increasing, decreasing;

		for (const auto number : numbers)
		{
			if (increasing.find(number) == increasing.end())
			{
				increasing.insert(number);
				continue;
			}

			if (decreasing.find(number) == decreasing.end())
			{
				decreasing.insert(number);
				continue;
			}
			return { false };
		}
		return { increasing, decreasing };
	}
}

int main(int argc, char* argv[])
{
	std::size_t n;
	std::cin >> n;

	std::vector<long> numbers(n);
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}

	const auto info = round550::SplitSequence(numbers);
	if (info.is_possible)
	{
		const auto print_numbers = [](const std::vector<long> &numbers)->void
		{
			std::cout << numbers.size() << std::endl;
			auto separator = "";
			for (const auto number : numbers)
			{
				std::cout << separator << number;
				separator = " ";
			}
			std::cout << std::endl;
		};
		std::cout << "YES" << std::endl;
		print_numbers(info.increasing);
		print_numbers(info.decreasing);
	}
	else
	{
		std::cout << "NO" << std::endl;
	}
	return 0;
}
