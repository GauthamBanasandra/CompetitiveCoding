//
// Created by gauth on 09-03-2018.
//

#include <iostream>
#include <vector>
#include <cmath>

using vi = std::vector<int>;
using ll = long long;

const int max_rows = 8;
const int max_columns = 8;

void Print(const std::vector<vi> &board_values);

bool IsSafePos(const vi &n_queens_pos, int row, int column) {
  for (auto _column = 0; _column < column; ++_column) {
    if (n_queens_pos[_column] == row || (abs(n_queens_pos[_column] - row) == abs(_column - column))) {
      return false;
    }
  }

  return true;
}

void Recurse(const std::vector<vi> &board_values, vi &n_queens_pos, ll &max_sum, int column) {
  if (column == max_columns) {
    ll _sum = 0;
    for (auto _column = 0; _column < max_columns; ++_column) {
      _sum += board_values[n_queens_pos[_column]][_column];
    }

    max_sum = _sum > max_sum ? _sum : max_sum;
  }

  for (auto row = 0; row < max_rows; ++row) {
    if (IsSafePos(n_queens_pos, row, column)) {
      n_queens_pos[column] = row;
      Recurse(board_values, n_queens_pos, max_sum, column + 1);
    }
  }
}

int main() {
  int k;

  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::vector<vi> board_values(max_rows);

    for (auto row = 0; row < max_rows; ++row) {
      board_values[row].assign(max_columns, 0);
      for (auto column = 0; column < max_columns; ++column) {
        std::cin >> board_values[row][column];
      }
    }

    ll max_sum = 0;
    vi n_queens_pos(max_columns, 0);
    Recurse(board_values, n_queens_pos, max_sum, 0);

    printf("%5lld\n", max_sum);
  }

  return 0;
}
