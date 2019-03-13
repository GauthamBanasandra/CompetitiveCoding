//
// Created by Gautham on 15-10-2018.
//

#include <iostream>
#include <vector>
#include <ios>

void Print(const std::vector<std::vector<int>> &matrix);

using ll = long long;
using Matrix = std::vector<std::vector<ll>>;

void ToCumulativeSumMatrix(Matrix &matrix) {
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

ll MatrixSum(const Matrix &matrix, std::size_t i, std::size_t j, std::size_t k, std::size_t l) {
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

Matrix GetLocalizedSum(Matrix &matrix, std::size_t m) {
  ToCumulativeSumMatrix(matrix);
  Matrix sum_matrix(matrix.size() - m + 1);

  for (std::size_t i = 0, row_len = matrix.size(); i < row_len - m + 1; ++i) {
    sum_matrix[i].resize(row_len - m + 1);

    for (std::size_t j = 0, column_len = matrix[i].size(); j < column_len - m + 1; ++j) {
      auto k = i + m - 1, l = j + m - 1;
      sum_matrix[i][j] = MatrixSum(matrix, i, j, k, l);
    }
  }
  return sum_matrix;
}

int main() {
  std::ios::sync_with_stdio(false);

  auto at_least_once = false;
  std::size_t n, m;
  Matrix matrix;

  while (std::cin >> n >> m, !std::cin.eof()) {
    matrix.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      auto i_row = n - i - 1;
      matrix[i_row].resize(n);
      for (std::size_t j = 0; j < n; ++j) {
        std::cin >> matrix[i_row][j];
      }
    }

    if (at_least_once) {
      std::cout << std::endl;
    }
    auto sum_matrix = GetLocalizedSum(matrix, m);
    n = sum_matrix.size();
    ll sum = 0;
    for (std::size_t i = 0; i < n; ++i) {
      auto i_row = n - i - 1;
      for (std::size_t j = 0, column_len = sum_matrix[i_row].size(); j < column_len; ++j) {
        const auto value = sum_matrix[i_row][j];
        sum += value;
        std::cout << value << std::endl;
      }
    }
    std::cout << sum << std::endl;
    at_least_once = true;
  }
  return 0;
}