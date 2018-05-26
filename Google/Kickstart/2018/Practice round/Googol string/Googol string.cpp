//
// Created by gauth on 25-02-2018.
//

#include <iostream>
#include <algorithm>

using ui = unsigned int;
using ull = unsigned long long;

int main() {
  const ull lim = 1000000;
  std::string str = "0";
  while (str.length() < lim) {
    std::string rev_str;
    for (auto i = str.crbegin(); i != str.crend(); ++i) {
      rev_str += *i == '0' ? '1' : '0';
    }

    str += '0';
    str += rev_str;
  }

  ui t;
  ull k;

  std::cin >> t;
  for (ui c = 1; c <= t; ++c) {
    std::cin >> k;
    printf("Case #%d: %c\n", c, str[k - 1]);
  }

  return 0;
}