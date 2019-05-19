// RE

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

bool CheckDiff(const std::string& w1, const std::string& w2)
{
	std::unordered_map<char, int> f;
	for (const auto c : w2)
	{
		++f[c];
	}

	auto tolerate = true;
	for (const auto c : w1)
	{
		const auto find_it = f.find(c);
		if (find_it == f.end())
		{
			if (tolerate)
			{
				tolerate = false;
				continue;
			}
			return false;
		}

		--f[c];
		if (f[c] == 0)
		{
			f.erase(c);
		}
	}
	return f.size() == 1;
}

int Next(const std::string& current_word,
	const std::vector<std::vector<std::string>>& words_size, const int len_so_far)
{
	const auto len = current_word.size();
	if (len >= 17)
	{
		return len_so_far;
	}

	for (const auto& word : words_size[len+1])
	{
		if (!CheckDiff(current_word, word))
		{
			continue;
		}
		return Next(word, words_size, len_so_far + 1);
	}
	return len_so_far;
}

int GetLongestStringChainLen(const std::vector<std::string> & words)
{
	std::vector<std::vector<std::string>> words_size(17);
	for (const auto& word : words)
	{
		words_size[word.size()].emplace_back(word);
	}

	auto max_len = 0;
	for (const auto& word : words)
	{
		auto len = Next(word, words_size, 1);
		max_len = std::max(max_len, len);
	}
	return max_len;
}

class Solution
{
public:
	static int longestStrChain(
		std::vector<std::string>& words);
};

int Solution::longestStrChain(
	std::vector<std::string> & words)
{
	return GetLongestStringChainLen(words);
}

int main(int argc, char* argv[])
{
	std::vector<std::string> words{ "a","b","ba","bca","bda","bdca" };
	std::cout << Solution::longestStrChain(words) << std::endl;
	return 0;
}
