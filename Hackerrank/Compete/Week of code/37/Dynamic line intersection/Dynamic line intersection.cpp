//
// Created by gauth on 22-04-2018.
//

// WA, TLE

#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cassert>

int main() {
    char operation;
    int n, k, q;
    std::string line;
    std::unordered_map<std::string, std::pair<int, int>> unique_lines;

    std::cin >> n;
    std::cin.ignore();
    while (n-- > 0) {
        std::getline(std::cin, line);
        std::istringstream tokenizer(line);

        tokenizer >> operation;
        switch (operation) {
            case '+': {
                tokenizer >> k >> q;
                auto hash = std::to_string(k) + " " + std::to_string(q);
                unique_lines[hash] = std::make_pair(k, q);
            }
                break;

            case '-': {
                tokenizer >> k >> q;
                auto hash = std::to_string(k) + " " + std::to_string(q);
                unique_lines.erase(hash);
            }
                break;

            case '?': {
                int x_int_count = 0;
                tokenizer >> q;
                for (const auto &kv : unique_lines) {
                    x_int_count = std::abs(q - kv.second.second) % kv.second.first == 0 ? x_int_count + 1 : x_int_count;
                }

                std::cout << x_int_count << std::endl;
            }
                break;

            default:
                assert(false);
        }
    }

    return 0;
}