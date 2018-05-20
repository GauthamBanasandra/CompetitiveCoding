//
// Created by gauth on 19-05-2018.
//

#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <cassert>
#include <iostream>

using Digit = int;
using Illumination = int;

void PrintPossibilities(const std::vector<std::unordered_set<int>> &possibilities);

class Display {
public:
    Display();

    bool IsCountDown(const std::list<std::string> &sequences) const;

private:
    bool IsCountDown(std::size_t i_possibilities, const std::vector<std::unordered_set<Digit>> &possibilities,
                     Digit expected) const;

    std::vector<std::unordered_set<Digit>> GetPossibleDigits(const std::list<Illumination> &illuminations) const;

    Illumination GetIllumination(const std::string &segments) const;

    std::list<std::pair<Digit, Illumination>> digits_;
};

Display::Display() {
    digits_.emplace_back(0, GetIllumination("YYYYYYN"));
    digits_.emplace_back(1, GetIllumination("NYYNNNN"));
    digits_.emplace_back(2, GetIllumination("YYNYYNY"));
    digits_.emplace_back(3, GetIllumination("YYYYNNY"));
    digits_.emplace_back(4, GetIllumination("NYYNNYY"));
    digits_.emplace_back(5, GetIllumination("YNYYNYY"));
    digits_.emplace_back(6, GetIllumination("YNYYYYY"));
    digits_.emplace_back(7, GetIllumination("YYYNNNN"));
    digits_.emplace_back(8, GetIllumination("YYYYYYY"));
    digits_.emplace_back(9, GetIllumination("YYYYNYY"));
}

Illumination Display::GetIllumination(const std::string &segments) const {
    assert(segments.length() == 7);

    Illumination illumination = 0;
    for (auto i = static_cast<int>(segments.length() - 1); i >= 0; --i) {
        if (segments[i] == 'Y') {
            illumination |= (1 << i);
        } else {
            assert(segments[i] == 'N');
        }
    }

    return illumination;
}

std::vector<std::unordered_set<Digit>> Display::GetPossibleDigits(const std::list<Illumination> &illuminations) const {
    std::vector<std::unordered_set<Digit>> possibilities;
    possibilities.reserve(illuminations.size());

    for (const auto illumination : illuminations) {
        std::unordered_set<Digit> digits;
        for (const auto &digit : digits_) {
            if ((digit.second & illumination) == illumination) {
                digits.insert(digit.first);
            }
        }

        possibilities.emplace_back(digits);
    }

    return possibilities;
}

bool Display::IsCountDown(const std::list<std::string> &sequences) const {
    std::list<Illumination> illuminations;
    for (const auto &sequence : sequences) {
        illuminations.emplace_back(GetIllumination(sequence));
    }

    auto possibilities = GetPossibleDigits(illuminations);
    assert(!possibilities.empty());
    assert(!possibilities[0].empty());

    PrintPossibilities(possibilities);
    for (const auto &digit : possibilities[0]) {
        if (IsCountDown(1, possibilities, digit - 1)) {
            return true;
        }
    }

    return false;
}

bool Display::IsCountDown(std::size_t i_possibilities, const std::vector<std::unordered_set<Digit>> &possibilities,
                          Digit expected) const {
    if (i_possibilities >= possibilities.size()) {
        return true;
    }

    if (possibilities[i_possibilities].find(expected) == possibilities[i_possibilities].end()) {
        return false;
    }

    return IsCountDown(i_possibilities + 1, possibilities, expected - 1);
}

int main() {
    int n;
    std::string sequence;
    std::list<std::string> sequences;

    while (std::cin >> n, n) {
        sequences.clear();
        while (n-- > 0) {
            std::cin >> sequence;
            sequences.emplace_back(sequence);
        }

        std::cout << (Display().IsCountDown(sequences) ? "MATCH" : "MISMATCH") << std::endl;
    }

    return 0;
}