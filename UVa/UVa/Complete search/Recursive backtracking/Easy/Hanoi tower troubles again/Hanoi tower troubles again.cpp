//
// Created by gauth on 26-03-2018.
//

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
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
  void Solve(int v, int &max_balls, std::vector<std::stack<int>> &poles);
};

void HanoiTowers::Solve(int v, int &max_balls, std::vector<std::stack<int>> &poles) {
  auto p = GetPole(v, poles);
  if (p == -1) {
    return;
  }

  poles[p].emplace(v);
  max_balls = std::max(max_balls, v);
  Solve(v + 1, max_balls, poles);
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
  int max_balls = 0;
  Solve(1, max_balls, poles);
  return max_balls;
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