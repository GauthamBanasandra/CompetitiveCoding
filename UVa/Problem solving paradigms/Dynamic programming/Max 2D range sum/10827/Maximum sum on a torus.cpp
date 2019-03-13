//
// Created by Gautham on 24-10-2018.
//

// WA

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>

void Print(const std::vector<std::vector<int>> &matrix);

using ll = long long;
using Matrix = std::vector<std::vector<int>>;

class ExtendedMatrix {
 public:
  explicit ExtendedMatrix(const Matrix &matrix);

  ll MaxTorus();

 private:
  void ExtendHorizontal();
  void ExtendVertical();
  void ToCumulativeSumMatrix(Matrix &matrix);
  ll MaxTorus(Matrix &matrix) const;
  ll TorusSum(const Matrix &matrix, std::size_t i, std::size_t j, std::size_t k, std::size_t l) const;

  Matrix horizontal_;
  Matrix vertical_;
};

ExtendedMatrix::ExtendedMatrix(const Matrix &matrix) : horizontal_(matrix), vertical_(matrix) {
  ExtendHorizontal();
  ExtendVertical();
  ToCumulativeSumMatrix(horizontal_);
  ToCumulativeSumMatrix(vertical_);

  /*std::cout << "Horizontal :" << std::endl;
  Print(horizontal_);
  std::cout << "\nVertical :" << std::endl;
  Print(vertical_);*/
}

void ExtendedMatrix::ExtendHorizontal() {
  for (auto &row : horizontal_) {
    auto t_size = row.size();
    row.resize(t_size * 2);
    for (int i = 0; i < t_size; ++i) {
      row[i + t_size] = row[i];
    }
  }
}

void ExtendedMatrix::ExtendVertical() {
  auto t_size = vertical_.size();
  vertical_.resize(t_size * 2);
  for (int i = 0; i < t_size; ++i) {
    vertical_[i + t_size] = vertical_[i];
  }
}

void ExtendedMatrix::ToCumulativeSumMatrix(Matrix &matrix) {
  for (std::size_t i = 0, row_len = matrix.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = matrix[i].size(); j < column_len; ++j) {
      if (i > 0) {
        matrix[i][j] += matrix[i - 1][j];
      }
      if (j > 0) {
        matrix[i][j] += matrix[i][j - 1];
      }
      if (i > 0 && j > 0) {
        matrix[i][j] -= matrix[i - 1][j - 1];
      }
    }
  }
}

ll ExtendedMatrix::MaxTorus(Matrix &matrix) const {
  assert(!vertical_.empty());
  assert(!horizontal_.empty());

  ll max_sum = std::numeric_limits<ll>::min();
  auto actual_row_size = vertical_.size() / 2;
  auto actual_column_size = horizontal_[0].size() / 2;

  for (std::size_t i = 0, row_len = matrix.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = matrix[i].size(); j < column_len; ++j) {
      for (auto k = i, torus_row_size = std::min(i + actual_row_size, row_len); k < torus_row_size; ++k) {
        for (auto l = j, torus_column_size = std::min(j + actual_column_size, column_len); l < torus_column_size; ++l) {
          max_sum = std::max(max_sum, TorusSum(matrix, i, j, k, l));
        }
      }
    }
  }
  return max_sum;
}

ll ExtendedMatrix::TorusSum(const Matrix &matrix, std::size_t i, std::size_t j, std::size_t k, std::size_t l) const {
  auto sum = matrix[k][l];
  if (i > 0) {
    sum -= matrix[i - 1][l];
  }
  if (j > 0) {
    sum -= matrix[k][j - 1];
  }
  if (i > 0 && j > 0) {
    sum += matrix[i - 1][j - 1];
  }
  return sum;
}

ll ExtendedMatrix::MaxTorus() {
  return std::max(MaxTorus(horizontal_), MaxTorus(vertical_));
}

int main() {
  int t;
  std::size_t n;

  Matrix matrix{
      /*{1, -1, 0, 0, -4},
      {2, 3, -2, -3, 2},
      {4, 1, -1, 5, 0},
      {3, -2, 1, -3, 2},
      {-3, 2, 4, 1, -4},*/

      /*{1, 1, 1},
      {1, 1, 1},
      {1, 1, 1}*/

      /*{1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},*/
      {1, 0, 0, 1},
      {0, -1, -1, 0},
      {0, 4, -1, 0},
      {1, 0, 0, 2},
  };

  std::cin >> t;
  while (t-- > 0) {
    std::cin >> n;
    matrix.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      matrix[i].resize(n);
      for (std::size_t j = 0; j < n; ++j) {
        std::cin >> matrix[i][j];
      }
    }

    std::cout << ExtendedMatrix(matrix).MaxTorus() << std::endl;
  }
//  std::cout << ExtendedMatrix(matrix).MaxTorus() << std::endl;
  return 0;
}