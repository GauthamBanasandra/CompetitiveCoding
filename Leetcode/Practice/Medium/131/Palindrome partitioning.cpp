#include <vector>
#include <string>

class Palindrome
{
public:
	explicit Palindrome(const std::string& str) : len_(static_cast<int>(str.size())), str_(str) {}

	std::vector<std::vector<std::string>> All() const;

private:
	void Partition(int i_start, std::vector<std::string>& palindromes,
		std::vector<std::vector<std::string>>& all_palindromes) const;
	bool IsPalindrome(int i, int j) const;

	const int len_;
	const std::string& str_;
};

std::vector<std::vector<std::string>> Palindrome::All() const
{
	std::vector<std::string> palindromes;
	std::vector<std::vector<std::string>> all_palindromes;

	Partition(0, palindromes, all_palindromes);
	return all_palindromes;
}

void Palindrome::Partition(const int i_start, std::vector<std::string>& palindromes,
	std::vector<std::vector<std::string>>& all_palindromes) const
{
	if (i_start >= len_)
	{
		if (!palindromes.empty())
		{
			all_palindromes.emplace_back(palindromes);
		}
		return;
	}

	for (auto i = i_start; i < len_; ++i)
	{
		if (!IsPalindrome(i_start, i))
		{
			continue;
		}

		palindromes.emplace_back(str_.substr(i_start, i - i_start + 1));
		Partition(i + 1, palindromes, all_palindromes);
		palindromes.pop_back();
	}
}

bool Palindrome::IsPalindrome(int i, int j) const
{
	while (i < j)
	{
		if (str_[i] != str_[j])
		{
			return false;
		}
		++i;
		--j;
	}
	return true;
}

class Solution
{
public:
	static std::vector<std::vector<std::string>> partition(std::string s);
};

std::vector<std::vector<std::string>> Solution::partition(std::string s)
{
	return Palindrome(s).All();
}

int main(int argc, char* argv[])
{
	auto v = Solution::partition("aab");
	return 0;
}
