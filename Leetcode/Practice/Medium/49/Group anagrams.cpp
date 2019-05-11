#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

std::vector<std::vector<std::string>> GroupAnagrams(const std::vector<std::string>& strings)
{
	std::unordered_map<std::string, std::vector<std::string>> anagrams;
	for (const auto& s : strings)
	{
		auto key(s);
		std::sort(key.begin(), key.end());
		anagrams[key].emplace_back(s);
	}

	std::vector<std::vector<std::string>> anagrams_group;
	anagrams_group.reserve(anagrams.size());
	for (const auto& group : anagrams)
	{
		anagrams_group.emplace_back(group.second);
	}
	return anagrams_group;
}

class Solution {
public:
	static std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
};

std::vector<std::vector<std::string>> Solution::groupAnagrams(std::vector<std::string>& strs)
{
	return GroupAnagrams(strs);
}

int main(int argc, char* argv[])
{
	return 0;
}
