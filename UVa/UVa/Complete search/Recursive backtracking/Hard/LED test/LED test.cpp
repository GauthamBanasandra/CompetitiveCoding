//
// Created by gauth on 19-05-2018.
//

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <iostream>

using Digit = int;
using Illumination = int;

void PrintPossibilities(const std::vector<std::pair<int, std::unordered_set<int>>> &possibilities);

class Display {
public:
    Display();

    bool IsCountDown(const std::list<std::string> &sequences);

private:
    bool IsCountDown(std::size_t i_possibilities,
                     const std::vector<std::pair<Illumination, std::unordered_set<Digit>>> &possibilities,
                     Digit expected, Illumination burnout);

    std::vector<std::pair<Illumination, std::unordered_set<Digit>>>
    GetPossibleDigits(const std::list<Illumination> &illuminations) const;

    Illumination GetIllumination(const std::string &segments) const;

    std::unordered_map<Digit, Illumination> digits_;
};

Display::Display() {
    digits_[0] = GetIllumination("YYYYYYN");
    digits_[1] = GetIllumination("NYYNNNN");
    digits_[2] = GetIllumination("YYNYYNY");
    digits_[3] = GetIllumination("YYYYNNY");
    digits_[4] = GetIllumination("NYYNNYY");
    digits_[5] = GetIllumination("YNYYNYY");
    digits_[6] = GetIllumination("YNYYYYY");
    digits_[7] = GetIllumination("YYYNNNN");
    digits_[8] = GetIllumination("YYYYYYY");
    digits_[9] = GetIllumination("YYYYNYY");
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

std::vector<std::pair<Illumination, std::unordered_set<Digit>>>
Display::GetPossibleDigits(const std::list<Illumination> &illuminations) const {
    std::vector<std::pair<Illumination, std::unordered_set<Digit>>> possibilities;
    possibilities.reserve(illuminations.size());

    for (const auto illumination : illuminations) {
        std::unordered_set<Digit> digits;
        for (const auto &digit : digits_) {
            if ((digit.second & illumination) == illumination) {
                digits.insert(digit.first);
            }
        }

        possibilities.emplace_back(illumination, digits);
    }

    return possibilities;
}

bool Display::IsCountDown(const std::list<std::string> &sequences) {
    std::list<Illumination> illuminations;
    for (const auto &sequence : sequences) {
        illuminations.emplace_back(GetIllumination(sequence));
    }

    auto possibilities = GetPossibleDigits(illuminations);
    assert(!possibilities.empty());
    assert(!possibilities[0].second.empty());

    PrintPossibilities(possibilities);
    for (const auto &digit : possibilities[0].second) {
        if (IsCountDown(1, possibilities, digit - 1, digits_[digit] ^ possibilities[0].first)) {
            return true;
        }
    }

    return false;
}

bool Display::IsCountDown(std::size_t i_possibilities,
                          const std::vector<std::pair<Illumination, std::unordered_set<Digit>>> &possibilities,
                          Digit expected, Illumination burnout) {
    if (i_possibilities >= possibilities.size()) {
        return true;
    }

    const auto &possible_digits = possibilities[i_possibilities].second;
    if (possible_digits.find(expected) == possible_digits.end()) {
        return false;
    }

    const auto illumination = possibilities[i_possibilities].first;
    const auto expected_digit_burnout = illumination ^digits_[expected];
    if ((burnout & expected_digit_burnout) != burnout) {
        return false;
    }

    return IsCountDown(i_possibilities + 1, possibilities, expected - 1, burnout | expected_digit_burnout);
}

int main() {
    int n;
    std::string sequence;
    std::list<std::string> sequences{
            "NNNNNNN",
            "YNNNNNN",
            "NNNNYNN"
    };

    std::cout << (Display().IsCountDown(sequences) ? "MATCH" : "MISMATCH") << std::endl;

    /*while (std::cin >> n, n) {
        sequences.clear();
        while (n-- > 0) {
            std::cin >> sequence;
            sequences.emplace_back(sequence);
        }

        std::cout << (Display().IsCountDown(sequences) ? "MATCH" : "MISMATCH") << std::endl;
    }*/

    return 0;
}