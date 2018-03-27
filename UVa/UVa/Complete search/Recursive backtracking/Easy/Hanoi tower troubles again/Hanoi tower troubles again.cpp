//
// Created by gauth on 26-03-2018.
//

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <string>

using ul = unsigned long;
using ui = unsigned int;

inline bool IsPerfectSquare(int n) {
  double r = sqrt(n);
  return !(r - trunc(r));
}

inline std::string Hash(int a, int b) {
  return a > b ? std::to_string(a) + " " + std::to_string(b) : std::to_string(b) + " " + std::to_string(a);
}

class HanoiTowers {
 public:
  explicit HanoiTowers(int n_towers) : n_towers(n_towers) {}

  int Solve();

  int n_towers;

 private:
  int GetPole(int v,
              int i_pole,
              const std::vector<std::stack<int>> &poles,
              std::unordered_set<std::string> &poles_tried);
  int Solve(int v,
            std::vector<std::stack<int>> &poles,
            std::unordered_set<std::string> &poles_tried);
};

int HanoiTowers::Solve(int v,
                       std::vector<std::stack<int>> &poles,
                       std::unordered_set<std::string> &poles_tried) {
  int max_balls = 0;
  for (int i = 0; i < n_towers; ++i) {
    auto p = GetPole(v, i, poles, poles_tried);
    if (p != -1) {
      poles[p].emplace(v);
      max_balls = std::max(max_balls, Solve(v + 1, poles, poles_tried));
      poles[p].pop();
    }
  }

  return std::max(v - 1, max_balls);
}

int HanoiTowers::GetPole(int v,
                         int i_pole,
                         const std::vector<std::stack<int>> &poles,
                         std::unordered_set<std::string> &poles_tried) {
  for (int i = i_pole; i < n_towers; ++i) {
    auto neighbouring_balls = Hash(v, poles[i].empty() ? -1 : poles[i].top());
    if ((poles[i].empty() || IsPerfectSquare(poles[i].top() + v))
        && (poles_tried.find(neighbouring_balls) == poles_tried.end())) {
      poles_tried.insert(neighbouring_balls);
      return i;
    }
  }

  return -1;
}

int HanoiTowers::Solve() {
  std::vector<std::stack<int>> poles(static_cast<ui>(n_towers), std::stack<int>());
  std::unordered_set<std::string> poles_tried;
  return Solve(1, poles, poles_tried);
}

int main() {
  for (int i = 1; i <= 50; ++i) {
    std::cout << i << " : " << HanoiTowers(i).Solve() << std::endl;
  }

  return 0;
}