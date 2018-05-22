//
// Created by gauth on 19-05-2018.
//

#include <algorithm>
#include <bitset>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <iostream>

using Digit = int;
using Illumination = std::bitset<7>;

void PrintPossibilities(const std::vector<std::pair<int, std::unordered_set<int>>> &possibilities);

class Display {
public:
    Display();

    bool IsCountDown(const std::list<std::string> &sequences);

    static std::unordered_map<Digit, Illumination> digits_;

private:

    bool IsCountDown(std::size_t i_possibilities,
                     const std::vector<std::pair<Illumination, std::unordered_set<Digit>>> &possibilities,
                     Digit expected, Illumination burnout);

    std::vector<std::pair<Illumination, std::unordered_set<Digit>>>
    GetPossibleDigits(const std::list<Illumination> &illuminations) const;

    static Illumination GetIllumination(const std::string &segments);
};

std::unordered_map<Digit, Illumination> Display::digits_;

Display::Display() {
    if (digits_.empty()) {
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
}

Illumination Display::GetIllumination(const std::string &segments) {
    const auto num_segments = segments.length();
    assert(num_segments == 7);

    Illumination illumination = 0;
    for (std::size_t i = 0; i < num_segments; ++i) {
        if (segments[i] == 'Y') {
            illumination |= (1 << (num_segments - i - 1));
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
    std::transform(sequences.begin(), sequences.end(), std::back_inserter(illuminations), GetIllumination);

    auto possibilities = GetPossibleDigits(illuminations);
    assert(!possibilities.empty());
    assert(!possibilities[0].second.empty());

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
    if ((burnout & illumination) != 0) {
        return false;
    }

    const auto expected_digit_burnout = illumination ^digits_[expected];
    return IsCountDown(i_possibilities + 1, possibilities, expected - 1, burnout | expected_digit_burnout);
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