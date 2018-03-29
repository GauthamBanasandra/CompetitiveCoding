//
// Created by gauth on 29-03-2018.
//

#include <string>
#include <sstream>
#include <deque>
#include <utility>
#include <vector>
#include <iostream>
#include <cassert>

enum class Commands { k_left, k_right, k_forth };

class CobbleStonePath {
 public:
  CobbleStonePath(const std::string &word, std::vector<std::string> path) : word(word + "#"), path(std::move(path)) {}

  void PrintCommands();

  std::string word;
  std::vector<std::string> path;

 private:
  bool Move(int i_word, int row, int column, std::deque<Commands> &commands);
  bool CheckLeft(int i_word, int row, int column);
  bool CheckRight(int i_word, int row, int column);
  bool CheckForth(int i_word, int row, int column);
  void PrintCommands(const std::deque<Commands> &commands);
  std::string CommandToString(Commands command);
};

inline bool CobbleStonePath::CheckLeft(int i_word, int row, int column) {
  if (column <= 0) {
    return false;
  }

  return path[row][column - 1] == word[i_word];
}

inline bool CobbleStonePath::CheckRight(int i_word, int row, int column) {
  if (column >= path[row].length() - 1) {
    return false;
  }

  return path[row][column + 1] == word[i_word];
}

inline bool CobbleStonePath::CheckForth(int i_word, int row, int column) {
  if (row <= 0) {
    return false;
  }

  return path[row - 1][column] == word[i_word];
}

bool CobbleStonePath::Move(int i_word, int row, int column, std::deque<Commands> &commands) {
  if (i_word == word.length()) {
    PrintCommands(commands);
    return true;
  }

  if (CheckLeft(i_word, row, column)) {
    commands.emplace_back(Commands::k_left);
    if (Move(i_word + 1, row, column - 1, commands)) {
      return true;
    }

    commands.pop_back();
  }

  if (CheckRight(i_word, row, column)) {
    commands.emplace_back(Commands::k_right);
    if (Move(i_word + 1, row, column + 1, commands)) {
      return true;
    }

    commands.pop_back();
  }

  if (CheckForth(i_word, row, column)) {
    commands.emplace_back(Commands::k_forth);
    if (Move(i_word + 1, row - 1, column, commands)) {
      return true;
    }

    commands.pop_back();
  }

  return false;
}

void CobbleStonePath::PrintCommands(const std::deque<Commands> &commands) {
  std::ostringstream cmd;
  auto it = commands.begin();
  cmd << CommandToString(*it++);
  for (; it != commands.end(); ++it) {
    cmd << " " << CommandToString(*it);
  }

  std::cout << cmd.str() << std::endl;
}

inline std::string CobbleStonePath::CommandToString(Commands command) {
  switch (command) {
    case Commands::k_left: return "left";
    case Commands::k_right: return "right";
    case Commands::k_forth: return "forth";
  }
}

void CobbleStonePath::PrintCommands() {
  assert(path.size());
  auto c_start = path[path.size() - 1].find('@');
  assert(c_start != std::string::npos);

  std::deque<Commands> commands;
  assert(Move(0, path.size() - 1, c_start, commands));
}

int main() {
  int t, n_row, n_column;
  std::string word = "IEHOVA";
  std::vector<std::string> path;

  std::cin >> t;
  while (t-- > 0) {
    path.clear();
    std::cin >> n_row >> n_column;
    for (int i = 0; i < n_row; ++i) {
      path.emplace_back("");
      std::cin >> path[i];
    }

    CobbleStonePath(word, path).PrintCommands();
  }

  return 0;
}