//
// Created by gauth on 27-05-2018.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <list>
#include <unordered_map>

using Illumination = std::bitset<7>;
using Number = int;

struct Digit {
    Digit() : is_garbled(false), exact(-1) {}

    bool is_garbled;
    Number exact;
    std::list<Number> garbled;
};

struct DigitsInfo {
    DigitsInfo() : is_valid(false) {}

    bool is_valid;
    std::vector<Digit> digits;
};

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

void Print(const DigitsInfo &info) {
    if (!info.is_valid) {
        std::cout << "Invalid" << std::endl;
    }

    for (const auto &digit : info.digits) {
        std::cout << "IsGarbled : " << digit.is_garbled << "\tExact : " << digit.exact << "\tGarbled :";
        for (const auto &garbled_num : digit.garbled) {
            std::cout << ' ' << garbled_num;
        }

        std::cout << std::endl;
    }
}