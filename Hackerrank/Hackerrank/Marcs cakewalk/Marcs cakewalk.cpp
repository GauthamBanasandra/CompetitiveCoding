//
// Created by gauth on 19-02-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

using ui = unsigned int;
using ull = unsigned long long;

ull pow(ull b, ull e) {
  ull p = 1;
  while (e--) {
    p *= b;
  }

  return p;
}

int main() {
  ui n, c;
  std::vector<ui> calories;

  std::cin >> n;
  for (ui i = 0; i < n; ++i) {
    std::cin >> c;
    calories.emplace_back(c);
  }

  std::sort(calories.begin(), calories.end());
  std::reverse(calories.begin(), calories.end());

  ull miles = 0;
  for (ui i = 0; i < n; ++i) {
    miles += calories[i] * pow(2, i);
  }

  std::cout << miles << std::endl;
  return 0;
}