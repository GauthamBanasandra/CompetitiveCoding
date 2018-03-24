//
// Created by gauth on 24-03-2018.
//

#include <string>
#include <iostream>
#include <queue>

using HammingStringContainer = std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>>;

class HammingStringGenerator {
 public:
  explicit HammingStringGenerator(int n) : n(n) {}

  void Generate(int h);

  int n;

 private:
  void Generate(int h, int b_start, std::string &hamming_string, HammingStringContainer &hamming_strings);
};

void HammingStringGenerator::Generate(int h,
                                      int b_start,
                                      std::string &hamming_string,
                                      HammingStringContainer &hamming_strings) {
  if (!h) {
    hamming_strings.emplace(hamming_string);
    return;
  }

  for (int i = b_start; i < n; ++i) {
    if (hamming_string[i] == '1') {
      continue;
    }

    hamming_string[i] = '1';
    Generate(h - 1, i + 1, hamming_string, hamming_strings);
    hamming_string[i] = '0';
  }
}

void HammingStringGenerator::Generate(int h) {
  std::string hamming_string(static_cast<unsigned int>(n), '0');
  HammingStringContainer hamming_strings;

  Generate(h, 0, hamming_string, hamming_strings);

  while (!hamming_strings.empty()) {
    auto s = hamming_strings.top();
    std::cout << s << std::endl;
    hamming_strings.pop();
  }
}

int main() {
  int t, n, h;

  std::cin >> t;
  for (auto i = 0; i < t; ++i) {
    if (i) {
      std::cout << std::endl;
    }

    std::cin >> n >> h;
    HammingStringGenerator(n).Generate(h);
  }

  return 0;
}