//
// Created by Gautham on 16-10-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <ios>

void Print(const std::vector<std::vector<int>> &matrix);

using Matrix = std::vector<std::vector<int>>;

struct MatrixInfo {
  MatrixInfo(bool all_zeros, int zeros_count) : all_zeros(all_zeros), zeros_count(zeros_count) {}

  bool all_zeros;
  int zeros_count;
};

class SubMatrix {
 public:
  explicit SubMatrix(const Matrix &matrix);

  int LargestArea() const;

 private:
  MatrixInfo ComputeArea(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const;

  Matrix cum_matrix_;
};

SubMatrix::SubMatrix(const Matrix &matrix) {
  auto row_len = matrix.size();
  cum_matrix_.resize(row_len);

  for (std::size_t i = 0; i < row_len; ++i) {
    auto column_len = matrix[i].size();
    cum_matrix_[i].resize(column_len);

    for (std::size_t j = 0; j < column_len; ++j) {
      cum_matrix_[i][j] = !matrix[i][j];
      if (i > 0) {
        cum_matrix_[i][j] += cum_matrix_[i - 1][j];
      }
      if (j > 0) {
        cum_matrix_[i][j] += cum_matrix_[i][j - 1];
      }
      if (i > 0 && j > 0) {
        cum_matrix_[i][j] -= cum_matrix_[i - 1][j - 1];
      }
    }
  }
}

int SubMatrix::LargestArea() const {
  auto max_area = 0;

  for (std::size_t i = 0, row_len = cum_matrix_.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = cum_matrix_[i].size(); j < column_len; ++j) {
      for (std::size_t k = i; k < row_len; ++k) {
        for (std::size_t l = j; l < column_len; ++l) {
          auto info = ComputeArea(i, j, k, l);
          if (info.all_zeros) {
            max_area = std::max(max_area, info.zeros_count);
          }
        }
      }
    }
  }
  return max_area;
}

MatrixInfo SubMatrix::ComputeArea(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const {
  auto area = cum_matrix_[k][l];
  if (i > 0) {
    area -= cum_matrix_[i - 1][l];
  }
  if (j > 0) {
    area -= cum_matrix_[k][j - 1];
  }
  if (i > 0 && j > 0) {
    area += cum_matrix_[i - 1][j - 1];
  }

  auto rows = k - i + 1, columns = l - j + 1;
  return {rows * columns == area, area};
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t m, n;
  Matrix matrix;

  while (std::cin >> m >> n, m || n) {
    matrix.resize(m);
    for (std::size_t i = 0; i < m; ++i) {
      matrix[i].resize(n);
      for (std::size_t j = 0; j < n; ++j) {
        std::cin >> matrix[i][j];
      }
    }
    std::cout << SubMatrix(matrix).LargestArea() << std::endl;
  }
  return 0;
}