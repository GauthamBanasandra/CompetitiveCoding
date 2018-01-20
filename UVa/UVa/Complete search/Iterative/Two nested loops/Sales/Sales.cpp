//
// Created by gauth on 15-01-2018.
//

#include <iostream>
#include <sstream>
#include <vector>

using ll = unsigned long long;

int main() {
  ll t, s;
  int n;
  std::string line;
  std::vector<int> sales;

  std::cin >> t;
  while (t--) {
    std::cin >> n;
    std::cin.ignore();
    sales.clear();
    sales.assign(n, 0);

    std::getline(std::cin, line);
    std::istringstream tokenizer(line);
    for (int i = 0; i < n; ++i) {
      tokenizer >> sales[i];
    }

    s = 0;
    for (int i = 1; i < n; ++i) {
      for (int j = i - 1; j >= 0; --j) {
        if (sales[j] <= sales[i]) {
          ++s;
        }
      }
    }

    std::cout << s << std::endl;
  }

  return 0;
}