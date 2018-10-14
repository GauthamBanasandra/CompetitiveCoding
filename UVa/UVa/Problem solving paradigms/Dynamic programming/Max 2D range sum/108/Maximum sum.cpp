//
// Created by Gautham on 14-10-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

void Print(const std::vector<std::vector<int>> &matrix);

void ToCumulativeSumMatrix(std::vector<std::vector<int>> &matrix) {
  for (std::size_t i = 0; i < matrix.size(); ++i) {
    for (std::size_t j = 0; j < matrix[i].size(); ++j) {
      if (j > 0) {
        matrix[i][j] += matrix[i][j - 1];
      }
      if (i > 0) {
        matrix[i][j] += matrix[i - 1][j];
      }
      if (i > 0 && j > 0) {
        matrix[i][j] -= matrix[i - 1][j - 1];
      }
    }
  }
}

int MaximumSubRectangle(std::vector<std::vector<int>> &matrix) {
  ToCumulativeSumMatrix(matrix);

  int max_sum = std::numeric_limits<int>::min();
  for (std::size_t i = 0; i < matrix.size(); ++i) {
    for (std::size_t j = 0; j < matrix[i].size(); ++j) {
      for (auto k = i; k < matrix.size(); ++k) {
        for (auto l = j; l < matrix[k].size(); ++l) {
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

          max_sum = std::max(max_sum, sum);
        }
      }
    }
  }
  return max_sum;
}

int main() {
  std::size_t n;
  std::vector<std::vector<int>> matrix{
      {0, -2, -7, 0},
      {9, 2, -6, 2},
      {-4, 1, -4, 1},
      {-1, 8, 0, -2}
  };

  while (std::cin >> n, !std::cin.eof()) {
    matrix.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      matrix[i].resize(n);
      for (std::size_t j = 0; j < n; ++j) {
        std::cin >> matrix[i][j];
      }
    }

    std::cout << MaximumSubRectangle(matrix) << std::endl;
  }
  return 0;
}