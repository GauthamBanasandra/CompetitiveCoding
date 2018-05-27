//
// Created by gauth on 27-05-2018.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>

using Illumination = std::bitset<7>;
using Number = int;

void
Print(std::unordered_map<Illumination, Number> &standard, const std::vector<Illumination> &illuminations) {
    std::cout << "Standard illuminations:" << std::endl;
    for (const auto &item : standard) {
        std::cout << item.first.to_string() << '\t' << item.second << std::endl;
    }

    std::cout << "\nIlluminations :" << std::endl;
    for (const auto &illumination : illuminations) {
        std::cout << illumination.to_string() << '\t' << standard[illumination] << std::endl;
    }
}
