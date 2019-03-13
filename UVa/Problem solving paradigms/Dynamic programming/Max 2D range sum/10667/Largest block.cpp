//
// Created by Gautham on 17-10-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <ios>

void Print(const std::vector<std::vector<int>> &matrix);

using Matrix = std::vector<std::vector<int>>;
using Rectangle = std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>;

struct MatrixInfo {
  MatrixInfo(bool all_zeros, int zeros_count) : all_zeros(all_zeros), zeros_count(zeros_count) {}

  bool all_zeros;
  int zeros_count;
};

class SubMatrix {
 public:
  SubMatrix(std::size_t s, const std::vector<Rectangle> &rectangles);
  int LargestArea() const;

 private:
  MatrixInfo GetMatrixInfo(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const;
  void ToCumulativeMatrix();

  Matrix cum_matrix_;
};

SubMatrix::SubMatrix(std::size_t s, const std::vector<Rectangle> &rectangles) {
  cum_matrix_.resize(s);
  for (auto &row : cum_matrix_) {
    row.resize(s, 1);
  }

  for (const auto &rectangle : rectangles) {
    for (std::size_t i = std::get<0>(rectangle) - 1; i < std::get<2>(rectangle); ++i) {
      for (std::size_t j = std::get<1>(rectangle) - 1; j < std::get<3>(rectangle); ++j) {
        cum_matrix_[i][j] = 0;
      }
    }
  }

  ToCumulativeMatrix();
}

void SubMatrix::ToCumulativeMatrix() {
  for (std::size_t i = 0, row_len = cum_matrix_.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = cum_matrix_[i].size(); j < column_len; ++j) {
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
          auto info = GetMatrixInfo(i, j, k, l);
          if (info.all_zeros) {
            max_area = std::max(max_area, info.zeros_count);
          }
        }
      }
    }
  }
  return max_area;
}

MatrixInfo SubMatrix::GetMatrixInfo(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const {
  auto sum = cum_matrix_[k][l];
  if (i > 0) {
    sum -= cum_matrix_[i - 1][l];
  }
  if (j > 0) {
    sum -= cum_matrix_[k][j - 1];
  }
  if (i > 0 && j > 0) {
    sum += cum_matrix_[i - 1][j - 1];
  }

  auto rows = k - i + 1, columns = l - j + 1;
  return {rows * columns == sum, sum};
}

int main() {
  std::ios::sync_with_stdio(false);

  int r1, c1, r2, c2;
  std::size_t p, s, b;
  std::vector<Rectangle> rectangles;

  std::cin >> p;
  while (p--) {
    std::cin >> s >> b;
    rectangles.resize(b);
    for (std::size_t i = 0; i < b; ++i) {
      std::cin >> r1 >> c1 >> r2 >> c2;
      rectangles[i] = std::make_tuple(r1, c1, r2, c2);
    }

    std::cout << SubMatrix(s, rectangles).LargestArea() << std::endl;
  }
  return 0;
}