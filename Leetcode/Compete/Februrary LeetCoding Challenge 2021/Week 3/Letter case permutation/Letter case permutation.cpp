#include <cctype>
#include <iostream>
#include <locale>
#include <ostream>
#include <string>
#include <vector>

namespace LeetCodeCodingChallenge_02_2021 {
class Permutation {
public:
  Permutation() : unicode_{"en_US.UTF8"} {}

  std::vector<std::string> GetPermutations(std::string &s) const;

private:
  void Transform(size_t i, std::string &s,
                 std::vector<std::string> &result) const;

  const std::locale unicode_;
};

std::vector<std::string> Permutation::GetPermutations(std::string &s) const {
  std::vector<std::string> result;
  Transform(0, s, result);
  return result;
}

void Permutation::Transform(const size_t i, std::string &s,
                            std::vector<std::string> &result) const {
  if (i >= s.length()) {
    result.emplace_back(s);
    return;
  }

  if (!std::isalpha(s[i])) {
    Transform(i + 1, s, result);
  } else if (std::isupper(s[i], unicode_)) {
    s[i] = static_cast<char>(std::tolower(s[i]));
    Transform(i + 1, s, result);
    s[i] = static_cast<char>(std::toupper(s[i]));
    Transform(i + 1, s, result);
  } else {
    s[i] = static_cast<char>(std::toupper(s[i]));
    Transform(i + 1, s, result);
    s[i] = static_cast<char>(std::tolower(s[i]));
    Transform(i + 1, s, result);
  }
}
} // namespace LeetCodeCodingChallenge_02_2021

class Solution {
public:
  std::vector<std::string> letterCasePermutation(std::string s);
};

std::vector<std::string> Solution::letterCasePermutation(std::string s) {
  return LeetCodeCodingChallenge_02_2021::Permutation().GetPermutations(s);
}

int main(int argc, char *argv[]) {
  for (const auto &word : Solution().letterCasePermutation("a1b2")) {
    std::cout << word << std::endl;
  }
  return 0;
}
