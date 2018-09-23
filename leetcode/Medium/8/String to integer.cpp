//
// Created by Gautham Banasandra on 22/09/18.
//

#include <string>
#include <iostream>
#include <cassert>

int int_max = (1 << 31) - 1;
int int_min = -(1 << 31);

enum class Sign { kPositive, kNegative };
enum class State { kSkip, kRead };

class Solution {
 public:
  int myAtoi(const std::string &str) const;

 private:
  int Atoi(const std::string &str) const;
  static bool IsMulOverflow(int n, int m) { return n > int_max / m; }
  static bool IsMulUnderflow(int n, int m) { return n < int_min / m; }
  static bool IsAddOverflow(int n, int m) { return n > int_max - m; }
  static bool IsSubUnderflow(int n, int m) { return n < int_min + m; }
};

int Solution::myAtoi(const std::string &str) const {
  return Atoi(str);
}

int Solution::Atoi(const std::string &str) const {
  int number = 0;
  auto state = State::kSkip;
  auto sign = Sign::kPositive;

  for (char c : str) {
    if (c == ' ') {
      if (state == State::kSkip) {
        continue;
      } else {
        return number;
      }
    }

    switch (state) {
      case State::kSkip:
        if (c == '+' || c == '-') {
          sign = c == '+' ? Sign::kPositive : Sign::kNegative;
          state = State::kRead;
          continue;
        }

        if (c >= '0' && c <= '9') {
          assert(number == 0);
          number = c - '0';
          number = sign == Sign::kPositive ? number : -number;
          state = State::kRead;
        } else {
          return number;
        }
        break;

      case State::kRead:
        if (c < '0' || c > '9') {
          return number;
        }

        switch (sign) {
          case Sign::kPositive:
            if (Solution::IsMulOverflow(number, 10)) {
              return int_max;
            } else {
              number *= 10;
            }

            if (Solution::IsAddOverflow(number, c - '0')) {
              return int_max;
            } else {
              number += c - '0';
            }
            break;

          case Sign::kNegative:
            if (Solution::IsMulUnderflow(number, 10)) {
              return int_min;
            } else {
              number *= 10;
            }

            if (Solution::IsSubUnderflow(number, c - '0')) {
              return int_min;
            } else {
              number -= c - '0';
            }
            break;
        }
        break;
    }
  }
  return number;
}

int main() {
  std::cout << Solution().myAtoi("  -2147483649") << std::endl;
  return 0;
}