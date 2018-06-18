//
// Created by gauth on 17-06-2018.
//

#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <cassert>

using ul = unsigned long;

std::pair<ul, ul> GetBooks(std::unordered_map<ul, int> &price_frequency, ul m) {
  auto books_init = false;
  std::pair<ul, ul> books;

  auto start_size = price_frequency.size();

  for (auto &first_book : price_frequency) {
    if (first_book.first > m) {
      continue;
    }

    --first_book.second;
    auto second_book = price_frequency.find(m - first_book.first);
    if (second_book == price_frequency.end() || second_book->second == 0) {
      ++first_book.second;
      continue;
    }

    ++first_book.second;
    const auto first = std::min(first_book.first, second_book->first);
    const auto second = std::max(first_book.first, second_book->first);

    if (!books_init) {
      books.first = first;
      books.second = second;
      books_init = true;
      continue;
    }

    if ((second - first) < (books.second - books.first)) {
      books.first = first;
      books.second = second;
    }
  }

  assert(start_size == price_frequency.size());

  return books;
}

int main() {
  std::ios::sync_with_stdio(false);

  int n;
  ul m = 0, price = 0;
  std::string line;
  std::unordered_map<ul, int> price_frequency;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    std::istringstream tokenizer(line);
    tokenizer >> n;

    std::getline(std::cin, line);
    std::istringstream price_tokenizer(line);
    price_frequency.clear();
    for (int i = 0; i < n; ++i) {
      price_tokenizer >> price;
      ++price_frequency[price];
    }

    std::getline(std::cin, line);
    std::istringstream money_tokenizer(line);
    money_tokenizer >> m;
    std::cin.ignore();

    auto books = GetBooks(price_frequency, m);
    std::cout << "Peter should buy books whose prices are " << books.first << " and " << books.second << "."
              << std::endl << std::endl;
  }

  return 0;
}