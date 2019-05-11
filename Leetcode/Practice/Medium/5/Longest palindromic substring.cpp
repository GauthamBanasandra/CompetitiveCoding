#include <string>
#include <iostream>
#include <cassert>

std::string LongestPalindrome(const std::string& str)
{
	const auto is_palindrome = [&str](const int i_start, const int i_end)->bool
	{
		for (auto i = i_start, rev_idx = 1; i < i_end - rev_idx; ++i, ++rev_idx)
		{
			// Just check if the mirror element is the same
			if (str[i] != str[i_end - rev_idx])
			{
				return false;
			}
		}
		return true;
	};

	const auto str_len = static_cast<int>(str.size());
	for (auto len = str_len; len > 0; --len)
	{
		// Keep checking if a palindrome of length str_len exists
		// If not, then check if a palindrome of length str_len - 1, str_len - 2 exists and so on
		for (auto i = 0; i <= str_len - len; ++i)
		{
			if (is_palindrome(i, i + len))
			{
				return str.substr(i, len);
			}
		}
	}

	//assert(false && "Smallest palindrome must be of length 1");
	return "";
}

class Solution {
public:
	static std::string longestPalindrome(std::string s);
};

std::string Solution::longestPalindrome(std::string s)
{
	return LongestPalindrome(s);
}

int main(int argc, char* argv[])
{
	std::cout << Solution::longestPalindrome("bb") << std::endl;
	return 0;
}
