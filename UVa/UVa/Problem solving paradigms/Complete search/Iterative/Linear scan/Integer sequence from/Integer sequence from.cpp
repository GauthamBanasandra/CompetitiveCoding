//
// Created by gauth on 10-01-2018.
//

#include <iostream>
#include <sstream>
#include <list>

using ui = unsigned int;
using ll = unsigned long long;

ll pow(ll b, ll e) {
  ll p = 1;
  for (ll i = 0; i < e; ++i) {
    p *= b;
  }

  return p;
}

int main() {
  int c;
  ui i, cf, d;
  ll k, n, t;
  std::string line;
  std::list<std::pair<ui, ui>> p;

  std::cin >> c;
  while (c-- > 0) {
    std::cin.ignore();
    std::getline(std::cin, line);
    std::istringstream tokenizer(line);

    tokenizer >> i;
    p.clear();
    for (int j = 0; j <= i; ++j) {
      tokenizer >> cf;
      if (cf != 0) {
        p.emplace_back(cf, j);
      }
    }

    std::cin >> d >> k;
    n = 0;
    for (size_t r = 0; r < k; ++n) {
      r += (n + 1) * d;
    }

    if (n == 0) {
      n = 1;
    }

    t = 0;
    for (const auto &pi : p) {
      t += pi.first * pow(n, pi.second);
    }

    std::cout << t << std::endl;
  }

  return 0;
}