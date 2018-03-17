//
// Created by gauth on 17-03-2018.
//

#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

class PasswordGenerator {
 public:
  PasswordGenerator(std::string pattern, std::vector<std::string> dictionary)
      : pattern(std::move(pattern)), dictionary(std::move(dictionary)) {}

  void Generate();
  std::string pattern;
  std::vector<std::string> dictionary;

 private:
  void Generate(size_t i_pattern, std::vector<size_t> &password_indices);
  void PrintPassword(const std::vector<std::size_t> &password_indices);
};

void PasswordGenerator::Generate(std::size_t i_pattern, std::vector<std::size_t> &password_indices) {
  if (i_pattern >= pattern.length()) {
    PrintPassword(password_indices);
    return;
  }

  switch (pattern[i_pattern]) {
    case '#':
      for (std::size_t j = 0; j < dictionary.size(); ++j) {
        password_indices[i_pattern] = j;
        Generate(i_pattern + 1, password_indices);
      }
      break;

    case '0':
      for (std::size_t j = 0; j < 10; ++j) {
        password_indices[i_pattern] = j;
        Generate(i_pattern + 1, password_indices);
      }
      break;

    default:assert(false);
  }
}

void PasswordGenerator::PrintPassword(const std::vector<std::size_t> &password_indices) {
  for (std::size_t i = 0; i < password_indices.size(); ++i) {
    switch (pattern[i]) {
      case '#':std::cout << dictionary[password_indices[i]];
        break;

      case '0':std::cout << password_indices[i];
        break;

      default:assert(false);
    }
  }

  std::cout << std::endl;
}

void PasswordGenerator::Generate() {
  std::vector<std::size_t> password_indices(pattern.length(), 0);
  Generate(0, password_indices);
}

int main() {
  int n, m;
  std::string line;
  std::vector<std::string> dictionary;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    dictionary.clear();
    std::stringstream tokenizer(line);
    tokenizer >> n;
    for (int i = 0; i < n; ++i) {
      std::getline(std::cin, line);
      dictionary.push_back(line);
    }

    std::cin >> m;
    std::cin.ignore();
    std::cout << "--" << std::endl;
    for (int i = 0; i < m; ++i) {
      std::getline(std::cin, line);
      PasswordGenerator(line, dictionary).Generate();
    }
  }

  return 0;
}