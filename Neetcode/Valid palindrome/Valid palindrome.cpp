#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

class Solution {
public:
  bool isPalindrome(std::string s);
};

bool Solution::isPalindrome(std::string s) {
  s.erase(std::remove_if(s.begin(), s.end(),
                         [](const auto &e) { return !std::isalnum(e); }),
          s.end());

  auto i_it = s.begin();
  auto j_it = s.rbegin();
  for (; (j_it + 1).base() >= i_it; ++i_it, ++j_it) {
    if (std::tolower(*i_it) != std::tolower(*j_it)) {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[]) {
  std::string s("tab a cat");
  std::cout << Solution().isPalindrome(s) << std::endl;
  return 0;
}
