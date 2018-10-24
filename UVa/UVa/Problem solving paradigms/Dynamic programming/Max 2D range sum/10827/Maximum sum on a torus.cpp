//
// Created by Gautham on 24-10-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

void Print(const std::vector<std::vector<int>> &matrix);

using ll = long long;
using Matrix = std::vector<std::vector<int>>;

class WrappedMatrix {
 public:
  explicit WrappedMatrix(const Matrix &matrix);

 private:
  void ExtendHorizontal();
  void ExtendVertical();
  void ToCumulativeSumMatrix(Matrix &matrix);
  ll MaxTorus(Matrix &matrix) const;

  Matrix horizontal_;
  Matrix vertical_;
};

WrappedMatrix::WrappedMatrix(const Matrix &matrix) : horizontal_(matrix), vertical_(matrix) {
  ExtendHorizontal();
  ExtendVertical();
  ToCumulativeSumMatrix(horizontal_);
  ToCumulativeSumMatrix(vertical_);

  std::cout << "Horizontal :" << std::endl;
  Print(horizontal_);
  std::cout << "\nVertical :" << std::endl;
  Print(vertical_);
}

void WrappedMatrix::ExtendHorizontal() {
  for (auto &row : horizontal_) {
    auto t_size = row.size();
    row.resize(t_size * 2);
    for (int i = 0; i < t_size; ++i) {
      row[i + t_size] = row[i];
    }
  }
}

void WrappedMatrix::ExtendVertical() {
  auto t_size = vertical_.size();
  vertical_.resize(t_size * 2);
  for (int i = 0; i < t_size; ++i) {
    vertical_[i + t_size] = vertical_[i];
  }
}

void WrappedMatrix::ToCumulativeSumMatrix(Matrix &matrix) {
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

ll WrappedMatrix::MaxTorus(Matrix &matrix) const {
  auto t_size = vertical_.size() / 2;
  for (std::size_t i = 0, row_len = vertical_.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = matrix[i].size(); j < column_len; ++j) {
      for (auto k = i, torus_row_size = std::min(i + t_size, row_len); k < torus_row_size; ++k) {

      }
    }
  }
  return 0;
}

int main() {
  Matrix matrix{
      /*{1, -1, 0, 0, -4},
      {2, 3, -2, -3, 2},
      {4, 1, -1, 5, 0},
      {3, -2, 1, -3, 2},
      {-3, 2, 4, 1, -4},*/

      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1}
  };

  WrappedMatrix wrapped_matrix(matrix);
  return 0;
}