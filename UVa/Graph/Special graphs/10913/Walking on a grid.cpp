// WIP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace uva_10913 {
using Sum = int;
const auto infinity = std::numeric_limits<Sum>::max();

class Maximizer {
public:
  Maximizer(int n, int rem_neg, const std::vector<std::vector<int>> &matrix);

  std::pair<bool, Sum> Maximize();

private:
  enum Direction {
    kDown,
    kLeft,
    kRight,
    Count // Not a direction
  };

  bool IsOutside(const std::pair<int, int> &pos) const {
    return pos.first < 0 || pos.first >= n_ || pos.second < 0 ||
           pos.second >= n_;
  }
  int GetIndex(const std::pair<int, int> &pos) const {
    return pos.first * n_ + pos.second;
  }

  Sum Maximize(Direction direction, std::pair<int, int> pos, int rem_neg);
  Sum MaximumSum(Sum a, Sum b) const;

  const int n_;
  const int rem_neg_;
  const std::vector<std::vector<int>> &matrix_;
  std::vector<std::vector<std::vector<Sum>>> memo_;
};

Maximizer::Maximizer(const int n, const int rem_neg,
                     const std::vector<std::vector<int>> &matrix)
    : n_{n}, rem_neg_{rem_neg}, matrix_{matrix} {
  memo_.resize(Direction::Count,
               std::vector<std::vector<Sum>>(
                   n_ * n_ + 1, std::vector<Sum>(rem_neg_ + 1, -1)));
}

std::pair<bool, Sum> Maximizer::Maximize() {
  auto sum = Maximize(Direction::kLeft, {0, 0}, rem_neg_);
  return {sum != infinity, sum};
}

Sum Maximizer::Maximize(const Direction direction, std::pair<int, int> pos,
                        int rem_neg) {
  if (IsOutside(pos)) {
    return infinity;
  }

  auto &memo = memo_[direction][GetIndex(pos)][rem_neg];
  if (memo != -1) {
    return memo;
  }

  if (matrix_[pos.first][pos.second] < 0) {
    if (rem_neg <= 0) {
      return memo = infinity;
    }
    --rem_neg;
  }

  if (pos.first == n_ - 1 && pos.second == n_ - 1) {
    return matrix_[pos.first][pos.second];
  }

  auto down = Maximize(Direction::kDown, {pos.first + 1, pos.second}, rem_neg);
  down = down == infinity ? infinity : down + 1;

  auto left_or_right = infinity;
  switch (direction) {
  case kDown: {
    const auto left =
        Maximize(Direction::kLeft, {pos.first, pos.second - 1}, rem_neg);
    const auto right =
        Maximize(Direction::kRight, {pos.first, pos.second + 1}, rem_neg);
    left_or_right = MaximumSum(left, right);
  } break;

  case kLeft:
    left_or_right =
        Maximize(Direction::kRight, {pos.first, pos.second + 1}, rem_neg);
    break;

  case kRight:
    left_or_right =
        Maximize(Direction::kLeft, {pos.first, pos.second - 1}, rem_neg);
    break;

  case Count:
  default:
    assert(false);
  }
  return memo = MaximumSum(down, left_or_right);
}

Sum Maximizer::MaximumSum(const Sum a, const Sum b) const {
  if (a == infinity && b != infinity) {
    return b;
  }
  if (a != infinity && b == infinity) {
    return a;
  }
  if (a != infinity && b != infinity) {
    return std::max(a, b);
  }
  return infinity;
}
} // namespace uva_10913

int main(int argc, char *argv[]) {
  int n;
  int rem_neg;
  size_t c = 0;
  std::vector<std::vector<int>> matrix;

  while (std::cin >> n >> rem_neg, n || rem_neg) {
    matrix.resize(n);
    for (auto i = 0; i < n; ++i) {
      matrix[i].resize(n);
      for (auto j = 0; j < n; ++j) {
        std::cin >> matrix[i][j];
      }
    }

    auto [is_possible, sum] =
        uva_10913::Maximizer(n, rem_neg, matrix).Maximize();
    if (is_possible) {
      std::cout << "Case " << ++c << ": " << sum << std::endl;
    } else {
      std::cout << "Case " << ++c << ": impossible" << std::endl;
    }
  }
  return 0;
}
