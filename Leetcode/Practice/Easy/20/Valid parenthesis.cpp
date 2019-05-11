#include <string>
#include <stack>
#include <iostream>

bool IsValidParenthesis(const std::string& parenthesis)
{
	std::stack<char> s;
	for (const auto bracket : parenthesis)
	{
		if (bracket == '(' || bracket == '{' || bracket == '[')
		{
			s.push(bracket);
			continue;
		}

		if (s.empty())
		{
			return false;
		}

		const auto top = s.top();
		if (bracket == ')' && top != '(')
		{
			return false;
		}
		if (bracket == '}' && top != '{')
		{
			return false;
		}
		if (bracket == ']' && top != '[')
		{
			return false;
		}
		s.pop();
	}
	return s.empty();
}

class Solution {
public:
	static bool isValid(std::string s);
};

bool Solution::isValid(std::string s)
{
	return IsValidParenthesis(s);
}

int main(int argc, char* argv[])
{
	std::cout << Solution::isValid("(}") << std::endl;
	return 0;
}
