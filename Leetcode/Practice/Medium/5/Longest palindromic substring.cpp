//
// Created by Gautham Banasandra on 21/09/18.
//

// WA

#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

struct PalindromeInfo {
  PalindromeInfo() : length(0) {}
  PalindromeInfo(size_t length) : length(length) {}
  PalindromeInfo(size_t length,
                 std::string::iterator begin,
                 std::string::iterator end)
      : length(length), begin(begin), end(end) {}

  std::size_t length;
  std::string::iterator begin;
  std::string::iterator end;
};

class Solution {
 public:
  std::string longestPalindrome(std::string s) const;

 private:
  std::string LongestPalindrome(std::string &s) const;
  PalindromeInfo TryEven(std::string &s, std::string::iterator &it) const;
  PalindromeInfo TryOdd(std::string &s, std::string::iterator &it) const;
  PalindromeInfo Expand(std::string::iterator &f_it,
                        std::string::reverse_iterator &r_it,
                        std::string &s,
                        std::size_t initial_length) const;
};

std::string Solution::longestPalindrome(std::string s) const {
  return LongestPalindrome(s);
}

std::string Solution::LongestPalindrome(std::string &s) const {
  PalindromeInfo info;
  for (auto it = s.begin(); it != s.end(); ++it) {
    auto even_info = TryEven(s, it);
    if (even_info.length > info.length) {
      info = even_info;
    }

    auto odd_info = TryOdd(s, it);
    if (odd_info.length > info.length) {
      info = odd_info;
    }
  }
  return std::string(info.begin, info.end);
}

PalindromeInfo Solution::TryEven(std::string &s, std::string::iterator &it) const {
  std::string::iterator f_it(it);
  ++f_it;
  if (f_it == s.end()) {
    return {1, it, f_it};
  }

  std::string::reverse_iterator r_it(f_it);
  assert(r_it != s.rend());
  assert(*r_it == *it);
  if (*f_it != *r_it) {
    return {1, it, f_it};
  }

  return Expand(f_it, r_it, s, 2);
}

PalindromeInfo Solution::TryOdd(std::string &s, std::string::iterator &it) const {
  std::string::iterator f_it(it);
  std::advance(f_it, 2);
  if (f_it == s.end()) {
    return {1, it, f_it};
  }

  std::string::reverse_iterator r_it(f_it);
  assert(r_it != s.rend());
  ++r_it;
  assert(*r_it == *it);
  if (*f_it != *r_it) {
    return {1, it, f_it};
  }

  return Expand(f_it, r_it, s, 3);
}

PalindromeInfo Solution::Expand(std::string::iterator &f_it,
                                std::string::reverse_iterator &r_it,
                                std::string &s,
                                std::size_t initial_length) const {
  std::size_t length = 0;
  for (length = 0; (f_it != s.end()) && (r_it != s.rend()) && (*f_it == *r_it); length += 2) {
    ++f_it;
    ++r_it;
  }

  return {initial_length + length, f_it, (++r_it).base()};
}

int main() {
  std::cout << Solution().longestPalindrome("abcddc") << std::endl;
  return 0;
}