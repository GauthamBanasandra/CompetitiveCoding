//
// Created by gauth on 21-01-2018.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <list>

using ull = unsigned long long;
void Print(const std::list<std::pair<ull, ull>> &one, const std::list<std::pair<ull, ull>> &three);

inline ull ManhattanDistance(const std::pair<ull, ull> &p, const std::pair<ull, ull> &q) {
  return std::max(p.first, q.first) - std::min(p.first, q.first) + std::max(p.second, q.second)
      - std::min(p.second, q.second);
}

int main() {
  ull m;
  std::string line;
  std::list<std::pair<ull, ull>> one, three;

  while (true) {
    one.clear();
    three.clear();
    std::getline(std::cin, line);

    if (std::cin.eof()) {
      break;
    }

    std::istringstream m_tokenizer(line);
    m_tokenizer >> m;

    for (ull i = 0; i < m; ++i) {
      std::getline(std::cin, line);
      for (ull j = 0; j < m; ++j) {
        switch (line[j]) {
          case '1':one.emplace_back(i, j);
            break;

          case '2':break;

          case '3':three.emplace_back(i, j);
            break;

          default:assert(false);
        }
      }
    }

    ull farthest = 0;
    for (const auto &o : one) {
      auto min_steps = ManhattanDistance(o, *three.begin());
      for (const auto &t : three) {
        min_steps = std::min(min_steps, ManhattanDistance(o, t));
      }

      farthest = std::max(farthest, min_steps);
    }

    std::cout << farthest << std::endl;
  }

  return 0;
}