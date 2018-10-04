//
// Created by gautham on 3/10/18.
//

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

class Solution {
 public:
  Solution();
  std::string intToRoman(int num);

 private:
  std::vector<std::pair<int, std::string>> symbols_;
};

Solution::Solution() {
  symbols_ = {
      {1, "I"},
      {4, "IV"},
      {5, "V"},
      {9, "IX"},
      {10, "X"},
      {40, "XL"},
      {50, "L"},
      {90, "XC"},
      {100, "C"},
      {400, "CD"},
      {500, "D"},
      {900, "CM"},
      {1000, "M"}
  };
}

std::string Solution::intToRoman(int num) {
  std::string roman;
  while (num > 0) {
    for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it) {
      if (num < it->first) {
        continue;
      }

      roman += it->second;
      num -= it->first;
      break;
    }
  }
  assert(num == 0);
  return roman;
}

int main() {
  for (int i = 1; i <= 3999; ++i) {
    std::cout << i << " " << Solution().intToRoman(i) << std::endl;
  }
  return 0;
}