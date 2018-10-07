//
// Created by gautham on 7/10/18.
//

#include <iostream>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <vector>
#include <cassert>

class Solution {
 private:
  std::forward_list<std::string> LetterCombinations(const std::string &digits) const;
  void Next(std::size_t i_digit,
            const std::string &digits,
            std::string &possibility,
            std::forward_list<std::string> &possibilities,
            std::unordered_map<char, std::string> &key_letters) const;

 public:
  std::vector<std::string> letterCombinations(const std::string &digits) const;
};

std::forward_list<std::string> Solution::LetterCombinations(const std::string &digits) const {
  std::forward_list<std::string> possibilities;
  std::unordered_map<char, std::string> key_letters{
      {'2', "abc"},
      {'3', "def"},
      {'4', "ghi"},
      {'5', "jkl"},
      {'6', "mno"},
      {'7', "pqrs"},
      {'8', "tuv"},
      {'9', "wxyz"},
  };

  std::string possibility;
  Next(0, digits, possibility, possibilities, key_letters);
  return possibilities;
}

void Solution::Next(std::size_t i_digit,
                    const std::string &digits,
                    std::string &possibility,
                    std::forward_list<std::string> &possibilities,
                    std::unordered_map<char, std::string> &key_letters) const {
  assert(i_digit <= digits.length());
  if (i_digit == digits.length()) {
    if (digits.empty()) {
      return;
    }

    possibilities.emplace_front(possibility);
    return;
  }

  for (auto letter : key_letters[digits[i_digit]]) {
    possibility += letter;
    Next(i_digit + 1, digits, possibility, possibilities, key_letters);
    possibility.pop_back();
  }
}

std::vector<std::string> Solution::letterCombinations(const std::string &digits) const {
  auto possibilities = LetterCombinations(digits);
  return std::vector<std::string>(possibilities.begin(), possibilities.end());
}

int main() {
  std::string digits = "";
  for (auto &possibility : Solution().letterCombinations(digits)) {
    std::cout << possibility << std::endl;
  }
  return 0;
}