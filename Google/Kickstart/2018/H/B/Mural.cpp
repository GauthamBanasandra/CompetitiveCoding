//
// Created by Gautham on 18-11-2018.
//

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using ll = long long;

ll MaxScore(const std::string &walls) {
  ll max_score = 0;
  std::size_t i = 0, j = 0, walls_len = walls.length();

  auto num_paint = walls_len & 1 ? (walls_len + 1) / 2 : walls_len / 2;
  for (; j < num_paint; ++j) {
    max_score += walls[j] - '0';
  }

  for (auto running_score = max_score; j < walls_len; ++i, ++j) {
    auto walls_i = walls[i] - '0';
    auto walls_j = walls[j] - '0';
    running_score = running_score - walls_i + walls_j;
    max_score = std::max(max_score, running_score);
  }
  return max_score;
}

int main() {
  int t;
  ll n;
  std::string walls;

  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    std::cin >> n >> walls;
    std::cout << "Case #" << i << ": " << MaxScore(walls) << std::endl;
  }
  return 0;
}