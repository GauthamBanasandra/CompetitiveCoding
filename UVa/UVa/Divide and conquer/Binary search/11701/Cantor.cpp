//
// Created by Gautham Banasandra on 20/06/18.
//

#include <string>
#include <sstream>
#include <iostream>

bool IsMember(long double p) {
  long double l = 0.0, h = 1.0, p1 = 0.0, p2 = 0.0;
  auto is_member = false;

  while (l <= p && p <= h) {
    if (l == p || p == h) {
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