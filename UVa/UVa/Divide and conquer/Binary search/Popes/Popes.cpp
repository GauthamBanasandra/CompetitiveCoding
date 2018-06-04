//
// Created by Gautham Banasandra on 04/06/18.
//

#include <ios>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using vl = std::vector<long>;

struct PopeInfo {
  PopeInfo() : num_popes(0) {}

  vl::iterator i_begin;
  vl::iterator i_end;
  long num_popes;
};

PopeInfo GetMaxPopes(vl &years, const long y) {
  PopeInfo info;

  for (auto i = years.begin(); std::distance(i, years.end()) >= y; ++i) {
    auto j = std::lower_bound(i, years.end(), *i + y);

    if (std::distance(i, j) > info.num_popes) {
      info.num_popes = std::distance(i, j);
      info.i_begin = i;
      --j;
      info.i_end = j;
    }
  }

  return info;
}

int main() {
  long y, p, year;
  vl years;
  std::string line;

  std::ios::sync_with_stdio(false);

  do {
    years.clear();
    std::cin >> y >> p;
    years.reserve(static_cast<std::size_t >(p));

    for (long i = 0; i < p; ++i) {
      std::cin >> year;
      years.emplace_back(year);
    }

    std::cin.ignore();
    auto info = GetMaxPopes(years, y);
    std::cout << info.num_popes << " " << *info.i_begin << " " << *info.i_end << std::endl;
  } while (std::getline(std::cin, line), !std::cin.eof());

  return 0;
}