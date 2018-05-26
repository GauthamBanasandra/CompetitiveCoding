//
// Created by gauth on 19-05-2018.
//

#include <limits>
#include <iostream>
#include <vector>
#include <string>

void PrintCostMap(const std::vector<std::vector<int>> &cost_map) {
    for (const auto &row : cost_map) {
        for (const auto cost : row) {
            std::cout << (cost == std::numeric_limits<int>::max() ? "inf" : std::to_string(cost)) << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}