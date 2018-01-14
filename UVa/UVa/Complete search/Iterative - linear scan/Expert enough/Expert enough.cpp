//
// Created by gauth on 11-01-2018.
//

#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <list>

using ull = unsigned long long;
using mlh = std::tuple<std::string, ull, ull>;

int main() {
  int t, d, q, c = 0, d_;
  ull l, h, p;
  std::string line, m;
  std::list<mlh> database;

  std::cin >> t;
  while (t-- > 0) {
    std::cin >> d;
    std::cin.ignore();

    database.clear();
    while (d-- > 0) {
      std::getline(std::cin, line);
      std::istringstream tokenizer(line);
      tokenizer >> m >> l >> h;
      database.emplace_back(m, l, h);
    }

    if (c++ > 0) {
      printf("\n");
    }

    std::cin >> q;
    while (q-- > 0) {
      std::cin >> p;
      d_ = 0;
      for (const auto &i: database) {
        if (std::get<1>(i) <= p && p <= std::get<2>(i)) {
          m = std::get<0>(i);
          ++d_;

          if (d_ > 1) {
            break;
          }
        }
      }

      if (d_ != 1) {
        printf("UNDETERMINED\n");
      } else {
        std::cout << m << std::endl;
      }
    }
  }

  return 0;
}