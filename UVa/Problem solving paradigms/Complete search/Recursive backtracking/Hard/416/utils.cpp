//
// Created by gauth on 19-05-2018.
//

#include <iostream>
#include <vector>
#include <unordered_set>

void PrintPossibilities(const std::vector<std::pair<int, std::unordered_set<int>>> &possibilities) {
    for (const auto &possibility : possibilities) {
        std::cout << possibility.first << "\t";
        for (const auto digit : possibility.second) {
            std::cout << digit << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}