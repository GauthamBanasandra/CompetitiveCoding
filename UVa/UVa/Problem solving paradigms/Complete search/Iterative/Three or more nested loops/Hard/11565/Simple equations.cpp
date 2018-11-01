//
// Created by gauth on 17-02-2018.
//

#include <iostream>

struct Solution {
  bool sol_exists;
  int x;
  int y;
  int z;
};

Solution Solve(int a, int b, int c) {
  Solution solution{false, 0, 0, 0};
  for (int i = -100; i <= 100; ++i) {
    for (int j = -100; j <= 100; ++j) {
      for (int k = -100; k <= 100; ++k) {
        if ((i != j) && (i != k) && (k != j) && (i + j + k == a) && (i * j * k == b) && (i * i + j * j + k * k == c)) {
          solution.x = i;
          solution.y = j;
          solution.z = k;
          solution.sol_exists = true;
          return solution;
        }
      }
    }
  }

  return solution;
}

int main() {
  int n, a, b, c;
  std::cin >> n;
  while (n-- > 0) {
    std::cin >> a >> b >> c;
    auto solution = Solve(a, b, c);
    if (solution.sol_exists) {
      std::cout << solution.x << " " << solution.y << " " << solution.z << std::endl;
    } else {
      std::cout << "No solution." << std::endl;
    }
  }

  return 0;
}