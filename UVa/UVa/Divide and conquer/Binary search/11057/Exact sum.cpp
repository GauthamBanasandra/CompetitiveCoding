//
// Created by gauth on 17-06-2018.
//

#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <iostream>

using ul = unsigned long;

std::pair<ul, ul> GetBooks(const std::unordered_set<ul> &books_price, ul m) {
    auto books_init = false;
    std::pair<ul, ul> books{std::numeric_limits<ul>::max(), std::numeric_limits<ul>::max()};

    for (const auto &price : books_price) {
        if (price > m) {
            continue;
        }

        const auto second_book_price = books_price.find(m - price);
        if (second_book_price == books_price.end()) {
            continue;
        }

        const auto first = std::min(price, *second_book_price);
        const auto second = std::max(price, *second_book_price);

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

    return books;
}

int main() {
    int n;
    ul m = 0, price = 0;
    std::string line;
    std::unordered_set<ul> books_price{40, 40};

    while (std::getline(std::cin, line), !std::cin.eof()) {
        std::istringstream tokenizer(line);
        tokenizer >> n;

        std::getline(std::cin, line);
        std::istringstream price_tokenizer(line);
        books_price.clear();
        for (int i = 0; i < n; ++i) {
            price_tokenizer >> price;
            books_price.insert(price);
        }

        std::getline(std::cin, line);
        std::istringstream money_tokenizer(line);
        money_tokenizer >> m;
        std::cin.ignore();

        auto books = GetBooks(books_price, m);
        std::cout << "Peter should buy books whose prices are " << books.first << " and " << books.second << "."
                  << std::endl << std::endl;
    }

    return 0;
}