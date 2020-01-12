#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace lc_5144 {
class Matrix {
public:
  explicit Matrix(const std::vector<std::vector<int>> &matrix);

  std::vector<std::vector<int>> GetBlockSum(int k) const;

private:
  bool IsOutside(const int x, const int y) const {
    return x < 0 || x >= num_rows_ || y < 0 || y >= num_columns_;
  }

  std::pair<int, int> GetTopLeft(const int x, const int y) const {
    return {std::max(0, x), std::max(0, y)};
  }
  std::pair<int, int> GetBottomRight(const int x, const int y) const {
    return {std::min(num_rows_ - 1, x), std::min(num_columns_ - 1, y)};
  }

  int GetSubMatrixSum(const std::pair<int, int> &top_left,
                      const std::pair<int, int> &bottom_right) const;

  const int num_rows_;
  const int num_columns_;
  std::vector<std::vector<int>> cumulative_sum_;
};

Matrix::Matrix(const std::vector<std::vector<int>> &matrix)
    : num_rows_{static_cast<int>(matrix.size())}, num_columns_{static_cast<int>(
                                                      matrix.front().size())} {
  cumulative_sum_ = matrix;

  for (auto i = 0; i < num_rows_; ++i) {
    for (auto j = 0; j < num_columns_; ++j) {
      if (i > 0) {
        cumulative_sum_[i][j] += cumulative_sum_[i - 1][j];
      }
      if (j > 0) {
        cumulative_sum_[i][j] += cumulative_sum_[i][j - 1];
      }
      if (i > 0 && j > 0) {
        cumulative_sum_[i][j] -= cumulative_sum_[i - 1][j - 1];
      }
    }
  }
}

std::vector<std::vector<int>> Matrix::GetBlockSum(int k) const {
  std::vector<std::vector<int>> block_sum(num_rows_,
                                          std::vector<int>(num_columns_));

  for (auto i = 0; i < num_rows_; ++i) {
    for (auto j = 0; j < num_columns_; ++j) {
      block_sum[i][j] = GetSubMatrixSum(GetTopLeft(i - k, j - k),
                                        GetBottomRight(i + k, j + k));
    }
  }
  return block_sum;
}

int Matrix::GetSubMatrixSum(const std::pair<int, int> &top_left,
                            const std::pair<int, int> &bottom_right) const {
  assert(!IsOutside(top_left.first, top_left.second) &&
         !IsOutside(bottom_right.first, bottom_right.second));

  auto sum = cumulative_sum_[bottom_right.first][bottom_right.second];
  if (top_left.first > 0) {
    sum -= cumulative_sum_[top_left.first - 1][bottom_right.second];
  }
  if (top_left.second > 0) {
    sum -= cumulative_sum_[bottom_right.first][top_left.second - 1];
  }
  if (top_left.first > 0 && top_left.second > 0) {
    sum += cumulative_sum_[top_left.first - 1][top_left.second - 1];
  }
  return sum;
}
} // namespace lc_5144

class Solution {
public:
  std::vector<std::vector<int>>
  matrixBlockSum(std::vector<std::vector<int>> &mat, int K);
};

std::vector<std::vector<int>>
Solution::matrixBlockSum(std::vector<std::vector<int>> &mat, int K) {
  return lc_5144::Matrix(mat).GetBlockSum(K);
}

int main(int argc, char *argv[]) { return 0; }
