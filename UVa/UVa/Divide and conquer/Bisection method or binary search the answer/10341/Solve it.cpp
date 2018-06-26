//
// Created by Gautham Banasandra on 24/06/18.
//

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using ld = double;

struct Solution {
  Solution() : exists(true), x(0.0) {}
  explicit Solution(bool exists) : exists(exists), x(0.0) {}
  Solution(bool exists, ld x) : exists(exists), x(x) {}

  bool exists;
  ld x;
};

inline bool IsEqual(ld a, ld b, ld epsilon = 0.001) {
  return std::fabs(a - b) <= ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

inline bool GreaterThan(ld a, ld b, ld epsilon = 0.001) {
  return (a - b) > ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

inline bool LessThan(ld a, ld b, ld epsilon = 0.001) {
  return (b - a) > ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

class Equation {
 public:
  Equation(int p, int q, int r, int s, int t, int u) : p_(p), q_(q), r_(r), s_(s), t_(t), u_(u) {}

  Solution Solve();

 private:
  ld F(ld x) const;

  int p_;
  int q_;
  int r_;
  int s_;
  int t_;
  int u_;
};

inline ld Round(ld val) {
  if (val < 0) return std::ceil(val - 0.5);
  return std::floor(val + 0.5);
}

inline ld Equation::F(ld x) const {
  auto d =
      (p_ / std::exp(x)) + (q_ * std::sin(x)) + (r_ * std::cos(x)) + (s_ * std::tan(x)) + (t_ * std::pow(x, 2.0)) + u_;
  d = Round(d * 10000.0) / 10000.0;
  return d;
}

Solution Equation::Solve() {
  auto d1 = F(0), d2 = F(1);

  if (IsEqual(d1, 0)) {
    return Solution{true, 0.0};
  }

  if (IsEqual(d2, 0)) {
    return Solution{true, 1.0};
  }

  if ((GreaterThan(d1, 0) && GreaterThan(d2, 0)) || (LessThan(d1, 0) && LessThan(d2, 0))) {
    return Solution{false};
  }

  ld l = 0.0, h = 1.0, x;

  for (int i = 0; i < 60; ++i) {
    x = (l + h) / 2.0f;
    if (F(x) > 0) {
      l = x;
    } else {
      h = x;
    }
  }

  return Solution{true, x};
}

int main() {
  ld p, q, r, s, t, u;
  std::string line;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    std::istringstream tokenizer(line);
    tokenizer >> p >> q >> r >> s >> t >> u;

    auto solution = Equation(p, q, r, s, t, u).Solve();
    if (solution.exists) {
//      std::cout << std::setprecision(4) << std::fixed << solution.x << std::endl;
      std::cout << std::round(solution.x * 10000.0) / 10000.0 << std::endl;
    } else {
      std::cout << "No solution" << std::endl;
    }
  }

  return 0;
}