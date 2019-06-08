//
// Created by gauth on 24-03-2018.
//

#include <string>
#include <queue>
#include <iostream>

using FriendlyQueens = std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>>;

class ChessBoard {
 public:
  ChessBoard(int m, std::pair<int, int> first_queen_pos) : m(m), first_queen_pos(std::move(first_queen_pos)) {}

  void PlaceQueens();

  int m;
  std::pair<int, int> first_queen_pos;

 private:
  void PlaceQueen(int column, std::vector<int> &queens_pos, FriendlyQueens &friendly_queens);
  bool IsSafe(int row, int column, const std::vector<int> &queens_pos);
  void PrintIfValid(const std::vector<int> &queens_pos, FriendlyQueens &friendly_queens);
};

void ChessBoard::PlaceQueen(int column, std::vector<int> &queens_pos, FriendlyQueens &friendly_queens) {
  if (column == m) {
    PrintIfValid(queens_pos, friendly_queens);
    return;
  }

  for (int row = 0; row < m; ++row) {
    if (!IsSafe(row, column, queens_pos)) {
      continue;
    }

    queens_pos[column] = row;
    PlaceQueen(column + 1, queens_pos, friendly_queens);
  }
}

bool ChessBoard::IsSafe(int row, int column, const std::vector<int> &queens_pos) {
  for (int c = 0; c < column; ++c) {
    if ((queens_pos[c] == row) || (abs(queens_pos[c] - row) == abs(c - column))) {
      return false;
    }
  }

  return true;
}

void ChessBoard::PrintIfValid(const std::vector<int> &queens_pos, FriendlyQueens &friendly_queens) {
  if (queens_pos[first_queen_pos.second] != first_queen_pos.first) {
    return;
  }

  std::string pos_str = std::to_string(queens_pos[0] + 1);
  for (std::size_t i = 1; i < queens_pos.size(); ++i) {
    pos_str += " " + std::to_string(queens_pos[i] + 1);
  }

  friendly_queens.emplace(pos_str);
}

void ChessBoard::PlaceQueens() {
  std::vector<int> queens_pos(m, 0);
  FriendlyQueens friendly_queens;

  PlaceQueen(0, queens_pos, friendly_queens);

  std::cout << "SOLN       COLUMN" << std::endl;
  std::cout << " #      1 2 3 4 5 6 7 8" << std::endl << std::endl;

  std::size_t i = 1;
  while (!friendly_queens.empty()) {
    const auto pos_str = friendly_queens.top();
    printf("%2d      %s\n", i++, pos_str.c_str());
    friendly_queens.pop();
  }
}

int main() {
  int n, row, column;

  std::cin >> n;
  for (auto i = 0; i < n; ++i) {
    if (i > 0) {
      std::cout << std::endl;
    }

    std::cin >> row >> column;
    ChessBoard(8, std::make_pair(row - 1, column - 1)).PlaceQueens();
  }

  return 0;
}
