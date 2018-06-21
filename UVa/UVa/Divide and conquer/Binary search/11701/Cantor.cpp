//
// Created by Gautham Banasandra on 20/06/18.
//

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

inline bool IsEqual(long double a, long double b, long double epsilon = 0.00000000001) {
  return std::abs(a - b) < epsilon;
}

bool IsMember(long double p) {
  long double l = 0.0, h = 1.0, p1 = 0.0, p2 = 0.0;
  auto is_member = false;

  while (l <= p && p <= h) {
    if (IsEqual(l, p) || IsEqual(p, h)) {
      is_member = true;
      break;
    }

    p1 = (h + 2 * l) / 3.0f;
    p2 = (2 * h + l) / 3.0f;

    if (l <= p && p <= p1) {
      h = p1;
    } else if (p2 <= p && p <= h) {
      l = p2;
    } else {
      break;
    }
  }

  return is_member;
}

int main() {
  long double p = 1.0;
  std::string line;

  while (std::getline(std::cin, line), line[0] != 'E') {
    std::istringstream tokenizer(line);
    tokenizer >> p;
    std::cout << (IsMember(p) ? "MEMBER" : "NON-MEMBER") << std::endl;
  }

  return 0;
}