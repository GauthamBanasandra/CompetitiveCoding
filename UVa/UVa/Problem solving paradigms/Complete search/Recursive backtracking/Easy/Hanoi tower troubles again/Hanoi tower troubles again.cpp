//
// Created by gauth on 26-03-2018.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

using ul = unsigned long;
using ui = unsigned int;

inline bool IsPerfectSquare(int n) {
  double r = sqrt(n);
  return !(r - trunc(r));
}

class HanoiTowers {
 public:
  explicit HanoiTowers(int n_towers) : n_towers(n_towers) {}

  int Solve();

  int n_towers;

 private:
  int GetPole(int v, const std::vector<std::stack<int>> &poles);
  int Solve(int v, std::vector<std::stack<int>> &poles);
};

int HanoiTowers::Solve(int v, std::vector<std::stack<int>> &poles) {
  auto p = GetPole(v, poles);
  if (p == -1) {
    return v - 1;
  }

  poles[p].emplace(v);
  return std::max(v, Solve(v + 1, poles));
}

int HanoiTowers::GetPole(int v, const std::vector<std::stack<int>> &poles) {
  for (int i = 0; i < n_towers; ++i) {
    if (poles[i].empty() || IsPerfectSquare(poles[i].top() + v)) {
      return i;
    }
  }

  return -1;
}

int HanoiTowers::Solve() {
  std::vector<std::stack<int>> poles(static_cast<ui>(n_towers), std::stack<int>());
  return Solve(1, poles);
}

int main() {
  int n, t;

  std::cin >> t;
  while (t-- > 0) {
    std::cin >> n;
    std::cout << HanoiTowers(n).Solve() << std::endl;
  }

  return 0;
}