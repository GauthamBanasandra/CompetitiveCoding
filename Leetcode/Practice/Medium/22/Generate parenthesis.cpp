#include <string>
#include <list>
#include <vector>
#include <iostream>

class Solution {
private:
	static std::list<std::string> GenerateParenthesis(const std::size_t n);
	static void Next(std::size_t i, std::size_t n, std::size_t num_open, std::size_t num_close, std::string &possibility, std::list<std::string> &possibilities);

public:
	static std::vector<std::string> generateParenthesis(const std::size_t n);
};

std::list<std::string> Solution::GenerateParenthesis(const std::size_t n)
{
	std::string possibility(n * 2, ' ');
	std::list<std::string> possibilities;

	Next(0, n, 0, 0, possibility, possibilities);
	return possibilities;
}

void Solution::Next(std::size_t i, std::size_t n, std::size_t num_open, std::size_t num_close,
	std::string& possibility, std::list<std::string>& possibilities)
{
	if (i == possibility.length())
	{
		possibilities.emplace_back(possibility);
		return;
	}

	if (num_open < n)
	{
		possibility[i] = '(';
		Next(i + 1, n, num_open + 1, num_close, possibility, possibilities);
	}

	if (num_close < num_open)
	{
		possibility[i] = ')';
		Next(i + 1, n, num_open, num_close + 1, possibility, possibilities);
	}
}

std::vector<std::string> Solution::generateParenthesis(const std::size_t n)
{
	auto possibilities = GenerateParenthesis(n);
	return std::vector<std::string>(possibilities.begin(), possibilities.end());
}

int main(int argc, char* argv[])
{
	for (const auto& possibility : Solution::generateParenthesis(2))
	{
		std::cout << possibility << std::endl;
	}
	return 0;
}
