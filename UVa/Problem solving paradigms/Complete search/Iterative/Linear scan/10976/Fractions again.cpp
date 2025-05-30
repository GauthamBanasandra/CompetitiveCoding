//
// Created by gauth on 14-01-2018.
//

#include <string>
#include <iostream>
#include <list>

using ui = unsigned int;
using ll = unsigned long long;

int main() {
  ui k;
  ll x, y;
  std::string line;
  std::list<std::pair<ll, ll>> xy_list;

  while (true) {
    std::getline(std::cin, line);
    if (std::cin.eof()) {
      break;
    }

    xy_list.clear();
    k = static_cast<ui>(std::stoi(line));
    x = k + 1;
    while (true) {
      ll nr = k * x;
      ll dr = x - k;
      if (nr % dr == 0) {
        y = nr / dr;
        xy_list.emplace_back(x, y);

        if (x >= y) {
          break;
        }
      }

      ++x;
    }

    std::cout << xy_list.size() << std::endl;
    for (const auto &xy:xy_list) {
      printf("1/%d = 1/%llu + 1/%llu\n", k, xy.second, xy.first);
    }
  }

  return 0;
}