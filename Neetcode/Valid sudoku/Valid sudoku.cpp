#include <bitset>
#include <iostream>
#include <vector>

class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>> &board);

private:
  static bool validateElement(std::bitset<9> &validity, char element);
};

bool Solution::isValidSudoku(std::vector<std::vector<char>> &board) {
  std::bitset<9> row_validity, col_validity, box_validity;

  for (std::size_t i = 0; i < board.size(); ++i) {
    row_validity.reset();
    col_validity.reset();
    for (std::size_t j = 0; j < board[i].size(); ++j) {
      if (!validateElement(row_validity, board[i][j])) {
        return false;
      }
      if (!validateElement(col_validity, board[j][i])) {
        return false;
      }
    }
  }

  for (std::size_t i_box_row = 0; i_box_row < board.size(); i_box_row += 3) {
    for (std::size_t j_box_row = 0; j_box_row < board.size(); j_box_row += 3) {
      box_validity.reset();
      for (std::size_t i = i_box_row; i < i_box_row + 3; ++i) {
        for (std::size_t j = j_box_row; j < j_box_row + 3; ++j) {
          if (!validateElement(box_validity, board[i][j])) {
            return false;
          }
        }
      }
    }
  }

  return true;
}

bool Solution::validateElement(std::bitset<9> &validity, const char element) {
  if (element == '.') {
    return true;
  }

  const auto num = element - '1';
  if (validity.test(num)) {
    return false;
  }

  validity.set(num);
  return true;
}

int main(int argc, char *argv[]) {
  std::vector<std::vector<char>> board{
      {'1', '2', '.', '.', '3', '.', '.', '.', '.'},
      {'4', '.', '.', '5', '.', '.', '.', '.', '.'},
      {'.', '9', '1', '.', '.', '.', '.', '.', '3'},
      {'5', '.', '.', '.', '6', '.', '.', '.', '4'},
      {'.', '.', '.', '8', '.', '3', '.', '.', '5'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '.', '.', '.', '.', '.', '2', '.', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '8'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  std::cout << Solution().isValidSudoku(board) << std::endl;
  return 0;
}
