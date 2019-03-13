//
// Created by gautham on 12/8/18.
//

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <ios>

using ull = unsigned long long;

struct TravelInfo {
  TravelInfo() : from(0), to(0) {}
  TravelInfo(ull from, ull to) : from(from), to(to) {}

  ull from;
  ull to;
};

struct TravelInfoHash {
  std::size_t operator()(const TravelInfo &info) const {
    return info.from ^ info.to;
  }
};

struct TravelInfoEquality {
  bool operator()(const TravelInfo &a, const TravelInfo &b) const {
    return (std::min(a.from, a.to) == std::min(b.from, b.to)) && (std::max(a.from, a.to) == std::max(b.from, b.to));
  }
};

int main() {
  std::ios::sync_with_stdio(false);

  int n = 0;
  TravelInfo info;
  std::unordered_set<TravelInfo, TravelInfoHash, TravelInfoEquality> students;

  while (std::cin >> n, n) {
    students.clear();

    while (n-- > 0) {
      std::cin >> info.from >> info.to;
      auto find_it = students.find(info);
      if (find_it != students.end()) {
        students.erase(find_it);
      } else {
        students.emplace_hint(find_it, info);
      }
    }

    std::cout << (students.empty() ? "YES" : "NO") << std::endl;
  }

  return 0;
}