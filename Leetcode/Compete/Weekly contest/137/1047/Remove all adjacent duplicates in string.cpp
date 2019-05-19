#include <stack>
#include <string>
#include <algorithm>
#include <iostream>

std::string GetUniqueAdj(const std::string& s)
{
	std::stack<char> order;

	for (const auto c : s)
	{
		if (order.empty())
		{
			order.push(c);
			continue;
		}
		if (c == order.top())
		{
			order.pop();
		}
		else
		{
			order.push(c);
		}
	}

	std::string unique;
	unique.reserve(order.size());
	while (!order.empty())
	{
		unique.push_back(order.top());
		order.pop();
	}
	std::reverse(unique.begin(), unique.end());
	return unique;
}

class Solution 
{
public:
	static std::string removeDuplicates(std::string S);
};

std::string Solution::removeDuplicates(std::string S)
{
	return GetUniqueAdj(S);
}

int main(int argc, char* argv[])
{
	std::cout << Solution::removeDuplicates("aaa") << std::endl;
	return 0;
}
