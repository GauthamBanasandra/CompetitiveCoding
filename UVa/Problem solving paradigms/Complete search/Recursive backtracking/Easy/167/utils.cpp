//
// Created by gauth on 09-03-2018.
//

#include <iostream>
#include <vector>

using ui = unsigned int;
using vi = std::vector<ui>;

const ui max_rows = 8;
const ui max_columns = 8;

void Print(const std::vector<vi> &board_values) {
  for (ui row = 0; row < max_rows; ++row) {
    for (ui column = 0; column < max_columns; ++column) {
      std::cout << board_values[row][column] << ' ';
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}