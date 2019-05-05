//
// Created by Gautham Banasandra on 20/09/18.
//

#include <algorithm>
#include <string>
#include <unordered_map>
#include <iostream>

using ll = long long;

class Solution {
 public:
  std::size_t lengthOfLongestSubstring(const std::string &s) const;

 private:
  std::size_t FindLongestLength(const std::string &s) const;
  void Delete(std::size_t i, const std::string &s, std::unordered_map<char, std::size_t> &longest) const;
};

std::size_t Solution::lengthOfLongestSubstring(const std::string &s) const {
  return FindLongestLength(s);
}

std::size_t Solution::FindLongestLength(const std::string &s) const {
  std::size_t count = 0, current_count = 0;
  std::unordered_map<char, std::size_t> longest;

  for (std::size_t i = 0; i < s.length(); ++i) {
    auto it = longest.find(s[i]);
    if (it == longest.end()) {
      longest[s[i]] = i;
      ++current_count;
      continue;
    }

    Delete(it->second, s, longest);
    longest[s[i]] = i;
    count = std::max(count, current_count);
    current_count = longest.size();
  }

  return std::max(count, current_count);
}

void Solution::Delete(std::size_t i, const std::string &s, std::unordered_map<char, std::size_t> &longest) const {
  for (auto j = static_cast<ll>(i); j >= 0; --i, --j) {
    auto it = longest.find(s[i]);
    if (it == longest.end() || it->second != i) {
      break;
    }
    longest.erase(it);
  }
}

int main() {
  std::cout << Solution().lengthOfLongestSubstring("pwwkew") << std::endl;
  return 0;
}
