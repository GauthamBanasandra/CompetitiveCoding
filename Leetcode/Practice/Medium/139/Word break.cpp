// TLE

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

class WordSplitter
{
public:
	explicit WordSplitter(const std::string& str, const std::vector<std::string>& dictionary);

	bool Split() const { return Split(0); }

private:
	bool Split(std::size_t i) const;
	bool IsMatch(std::size_t i, const std::string& word) const;

	const std::size_t len_;
	const std::string& str_;
	std::unordered_map<char, std::vector<std::string>> dictionary_;
};

WordSplitter::WordSplitter(const std::string& str,
	const std::vector<std::string>& dictionary) :len_(str.size()), str_(str)
{
	for (const auto& word : dictionary)
	{
		dictionary_[word.front()].emplace_back(word);
	}
	for (auto& words : dictionary_)
	{
		std::sort(words.second.begin(), words.second.end(),
			[](const std::string& a, const std::string& b)->bool
			{
				return a.size() > b.size();
			});
	}
}

bool WordSplitter::Split(const std::size_t i) const
{
	if (i >= len_)
	{
		return true;
	}

	const auto find_it = dictionary_.find(str_[i]);
	if (find_it == dictionary_.end())
	{
		return false;
	}

	for (const auto& word : find_it->second)
	{
		if (!IsMatch(i, word))
		{
			continue;
		}
		if (Split(i + word.size()))
		{
			return true;
		}
	}
	return false;
}

bool WordSplitter::IsMatch(const std::size_t i, const std::string& word) const
{
	if (len_ - i + 1 < word.size())
	{
		return false;
	}
	return str_.compare(i, word.size(), word) == 0;
}

class Solution
{
public:
	static bool wordBreak(std::string s, std::vector<std::string>& wordDict);
};

bool Solution::wordBreak(std::string s, std::vector<std::string>& wordDict)
{
	return WordSplitter(s, wordDict).Split();
}

int main(int argc, char* argv[])
{
	std::vector<std::string> dictionary{ "a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa" };
	std::cout << Solution::wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", dictionary) << std::endl;
	return 0;
}
