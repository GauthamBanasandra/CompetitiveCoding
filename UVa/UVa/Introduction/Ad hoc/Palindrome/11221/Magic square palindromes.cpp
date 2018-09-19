#include <string>
#include <iostream>
#include <math.h>

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  unsigned long long test_cases, c = 1;
  std::string line;
  std::string input;

  scanf("%llu\n", &test_cases);
  while (test_cases--) {
    line.clear();
    getline(std::cin, input);
    for (auto ch : input) {
      if (isalpha(ch)) {
        line += ch;
      }
    }

    auto is_palindrome = true;
    const unsigned long long len = line.length();
    const long double n = sqrt(len);
    if (len > 1) {
      if (!(n - truncl(n))) {
        unsigned long long mid;
        if (len & 1) {
          mid = static_cast<unsigned long long>(floor(len / 2));
        } else {
          mid = len / 2;
        }

        for (unsigned long long i = 0; i < mid; ++i) {
          if (line[i] != line[len - i - 1]) {
            is_palindrome = false;
            break;
          }
        }
      } else {
        is_palindrome = false;
      }
    }

    if (is_palindrome) {
      printf("Case #%llu:\n%llu\n", c++, static_cast<unsigned long long>(truncl(n)));
    } else {
      printf("Case #%llu:\nNo magic :(\n", c++);
    }
  }

  return 0;
}
