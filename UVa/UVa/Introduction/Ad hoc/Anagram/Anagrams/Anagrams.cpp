#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

typedef unsigned long long big_int;

int main(int argc, char *argv[]) {
  big_int test_cases, c = 0;
  std::string line, key, word;
  std::unordered_map<std::string, std::vector<std::string>> an;
  std::unordered_set<std::string> an_keys;
  std::set<std::string> op_sorted;

  scanf("%llu\n", &test_cases);
  while (test_cases--) {
    an.clear();
    an_keys.clear();
    op_sorted.clear();
    if (c > 0) {
      printf("\n");
    }

    while (getline(std::cin, line), line != "") {
      key.clear();
      word.clear();

      std::istringstream buf(line);
      while (buf >> word) {
        transform(word.begin(), word.end(), word.begin(), toupper);
        key += word;
      }

      sort(key.begin(), key.end());
      if (an.find(key) != an.end()) {
        an_keys.insert(key);
      }

      an[key].push_back(line);
    }

    for (const auto an_key : an_keys) {
      sort(an[an_key].begin(), an[an_key].end());

      for (big_int i = 0, len = an[an_key].size(); i < len - 1; ++i) {
        for (big_int j = i + 1; j < len; ++j) {
          op_sorted.insert(an[an_key][i] + " = " + an[an_key][j]);
        }
      }
    }

    for (auto an_pair : op_sorted) {
      printf("%s\n", an_pair.c_str());
    }

    ++c;
  }
}
