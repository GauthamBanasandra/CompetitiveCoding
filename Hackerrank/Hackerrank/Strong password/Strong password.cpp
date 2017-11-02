#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

#define DIGIT 0
#define LOWER_CASE 1
#define UPPER_CASE 2
#define SPECIAL_CHAR 3

#define CLASSIFIER_LEN 1000

char classifier[CLASSIFIER_LEN];

void init_classifier()
{
	for (auto i = 0; i < CLASSIFIER_LEN; ++i)
	{
		classifier[i] = -1;
	}

	const std::string digits = "0123456789";
	const std::string lower_case = "abcdefghijklmnopqrstuvwxyz";
	const std::string upper_case = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string special_char = "!@#$%^&*()-+";

	for (const auto &digit : digits)
	{
		classifier[digit] = DIGIT;
	}

	for (const auto &ch : lower_case)
	{
		classifier[ch] = LOWER_CASE;
	}

	for (const auto &ch : upper_case)
	{
		classifier[ch] = UPPER_CASE;
	}

	for (const auto &ch : special_char)
	{
		classifier[ch] = SPECIAL_CHAR;
	}
}

int get_missing_strength(const std::string &line)
{
	auto missing_strength = 0;

	std::bitset<4> criteria;
	criteria.set();
	for (auto const &c : line)
	{
		if (!criteria.to_ullong())
		{
			break;
		}

		switch (classifier[c])
		{
		case DIGIT:
			criteria.reset(DIGIT);
			break;

		case LOWER_CASE:
			criteria.reset(LOWER_CASE);
			break;

		case UPPER_CASE:
			criteria.reset(UPPER_CASE);
			break;

		case SPECIAL_CHAR:
			criteria.reset(SPECIAL_CHAR);
			break;

		default:
			break;
		}
	}

	for (const auto & c : criteria.to_string())
	{
		if (c == '1')
		{
			++missing_strength;
		}
	}

	return missing_strength;
}

int main(int argc, char* argv[])
{
	init_classifier();

	int n;
	std::string line;
	std::cin >> n;
	std::cin.ignore();
	getline(std::cin, line);
	const auto missing_strength = get_missing_strength(line);
	if (n >= 6)
	{
		std::cout << missing_strength << '\n';
	}
	else
	{
		std::cout << std::max(6 - n, missing_strength) << '\n';
	}

	return 0;
}
