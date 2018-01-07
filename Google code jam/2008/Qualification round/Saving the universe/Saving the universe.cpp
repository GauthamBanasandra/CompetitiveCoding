//
// Created by gauth on 07-01-2018.
//

#include <iostream>
#include <unordered_set>

int main() {
  int n, s, q, switches;
  std::string line;
  std::unordered_set<std::string> search_engines;

  std::cin >> n;
  for (int c = 1; c <= n; ++c) {
    std::cin >> s;
    std::cin.ignore();
    for (int i = 0; i < s; ++i) {
      std::getline(std::cin, line);
    }

    std::cin >> q;
    std::cin.ignore();
    switches = 0;
    search_engines.clear();
    while (q-- > 0) {
      std::getline(std::cin, line);
      if (search_engines.find(line) == search_engines.end()) {
        if (search_engines.size() + 1 == s) {
          ++switches;
          search_engines.clear();
        }

        search_engines.insert(line);
      }
    }

    printf("Case #%d: %d\n", c, switches);
  }

  return 0;
}