//
// Created by Gautham on 14-10-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <ios>

void Print(const std::vector<std::vector<int>> &matrix);

using Matrix = std::vector<std::vector<int>>;

struct MatrixInfo {
  MatrixInfo(bool all_ones, int size) : all_ones(all_ones), ones_count(size) {}

  bool all_ones;
  int ones_count;
};

class MatrixSize {
 public:
  explicit MatrixSize(const std::vector<std::string> &data);

  int Largest() const;

 private:
  MatrixInfo GetMatrixInfo(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const;

  Matrix cum_matrix_;
};

MatrixSize::MatrixSize(const std::vector<std::string> &data) {
  auto matrix_len = data.size();
  cum_matrix_.resize(matrix_len);

  for (std::size_t i = 0; i < matrix_len; ++i) {
    auto row_len = data[i].length();
    cum_matrix_[i].resize(row_len);

    for (std::size_t j = 0; j < row_len; ++j) {
      cum_matrix_[i][j] = data[i][j] - '0';
      if (j > 0) {
        cum_matrix_[i][j] += cum_matrix_[i][j - 1];
      }
      if (i > 0) {
        cum_matrix_[i][j] += cum_matrix_[i - 1][j];
      }
      if (i > 0 && j > 0) {
        cum_matrix_[i][j] -= cum_matrix_[i - 1][j - 1];
      }
    }
  }
}

MatrixInfo MatrixSize::GetMatrixInfo(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const {
  auto sum = cum_matrix_[k][l];
  if (j > 0) {
    sum -= cum_matrix_[k][j - 1];
  }
  if (i > 0) {
    sum -= cum_matrix_[i - 1][l];
  }
  if (i > 0 && j > 0) {
    sum += cum_matrix_[i - 1][j - 1];
  }

  auto rows = k - i + 1, columns = l - j + 1;
  assert(sum <= rows * columns);
  return {rows * columns == sum, sum};
}

int MatrixSize::Largest() const {
  auto max_ones = 0;
  for (std::size_t i = 0, matrix_len = cum_matrix_.size(); i < matrix_len; ++i) {
    for (std::size_t j = 0, row_len = cum_matrix_[i].size(); j < row_len; ++j) {
      for (std::size_t k = i; k < matrix_len; ++k) {
        for (std::size_t l = j; l < row_len; ++l) {
          auto info = GetMatrixInfo(i, j, k, l);
          if (!info.all_ones) {
            continue;
          }

          max_ones = std::max(max_ones, info.ones_count);
        }
      }
    }
  }
  return max_ones;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t t;
  std::string line;
  std::vector<std::string> data;

  std::cin >> t;
  for (std::size_t i = 0; i < t; ++i) {
    std::cin >> line;
    auto n = line.length();

    data.resize(n);
    assert(n > 0);
    data[0] = line;

    for (int j = 1; j < n; ++j) {
      std::cin >> data[j];
    }

    if (i > 0) {
      std::cout << std::endl;
    }
    std::cout << MatrixSize(data).Largest() << std::endl;
  }
  return 0;
}