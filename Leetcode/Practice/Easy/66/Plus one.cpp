#include <vector>
#include <algorithm>

std::vector<int> PlusOne(const std::vector<int>& digits)
{
	std::vector<int> result(digits.rbegin(), digits.rend());
	auto is_carry = true;
	for (auto i = 0, len = static_cast<int>(digits.size()); i < len && is_carry; ++i)
	{
		if (result[i] == 9)
		{
			result[i] = 0;
		}
		else
		{
			++result[i];
			is_carry = false;
		}
	}
	if (is_carry)
	{
		result.push_back(1);
	}
	std::reverse(result.begin(), result.end());
	return result;
}

class Solution
{
public:
	static std::vector<int> plusOne(
		std::vector<int>& digits);
};

std::vector<int> Solution::plusOne(std::vector<int>& digits)
{
	return PlusOne(digits);
}

int main(int argc, char* argv[])
{
	return 0;
}
