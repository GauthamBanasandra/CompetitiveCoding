#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
public:
  std::vector<std::vector<std::string>>
  groupAnagrams(std::vector<std::string> &strs);

private:
  bool AreAnagrams(const std::string &a, const std::string &b);
};

std::vector<std::vector<std::string>>
Solution::groupAnagrams(std::vector<std::string> &strs) {
  std::vector<std::vector<std::string>> anagram_groups;
  std::unordered_set<std::size_t> grouped_anagram_iterators;

  for (auto i_it = strs.begin(); i_it != strs.end(); ++i_it) {
    if (grouped_anagram_iterators.find(std::distance(strs.begin(), i_it)) !=
        grouped_anagram_iterators.end()) {
      continue;
    }

    grouped_anagram_iterators.emplace(std::distance(strs.begin(), i_it));

    std::vector<std::string> anagram_group{*i_it};
    for (auto j_it = i_it + 1; j_it != strs.end(); ++j_it) {
      if (AreAnagrams(*i_it, *j_it)) {
        anagram_group.emplace_back(*j_it);
        grouped_anagram_iterators.emplace(std::distance(strs.begin(), j_it));
      }
    }

    anagram_groups.emplace_back(anagram_group);
  }

  return anagram_groups;
}

bool Solution::AreAnagrams(const std::string &a, const std::string &b) {
  std::vector<int> freq_table(26, 0);

  for (const auto c : a) {
    ++freq_table[c - 'a'];
  }

  for (const auto c : b) {
    --freq_table[c - 'a'];
  }

  return std::all_of(freq_table.begin(), freq_table.end(),
                     [](const auto &e) { return e == 0; });
}

int main(int argc, char *argv[]) {
  std::vector<std::string> strs{""};
  auto anagram_groups = Solution().groupAnagrams(strs);
  for (const auto &anagrams : anagram_groups) {
    for (const auto &anagram : anagrams) {
      std::cout << anagram << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
