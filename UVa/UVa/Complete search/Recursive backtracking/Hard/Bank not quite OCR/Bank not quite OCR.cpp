//
// Created by gauth on 26-05-2018.
//

#include <string>
#include <vector>
#include <list>
#include <bitset>
#include <unordered_map>
#include <iostream>
#include <cassert>

using Illumination = std::bitset<7>;
using Number = int;
using ll = long long;

enum class RecognitionStatus {
    kValid, kFailure, kAmbiguous
};

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

struct RecognitionInfo {
    RecognitionInfo() : status(RecognitionStatus::kFailure), checksum(0) {}

    RecognitionStatus status;
    std::string account_num;
    ll checksum;
};

void Print(const DigitsInfo &info);

void
Print(std::unordered_map<Illumination, Number> &standard, const std::vector<Illumination> &illuminations);

class OCR {
public:
    OCR();

    static DigitsInfo GetDigits(const std::vector<Illumination> &illuminations);

    static std::vector<Illumination> Scan(std::size_t num_digits);

    static std::unordered_map<Illumination, Number> standard_;
private:

    static bool IsPowerOf2(const Illumination &illumination);

    static std::list<Number> GetGarbledNumbers(const Illumination &illumination);

    static void InitializeStandard();

    static void NormalizeInput(std::string &line);

    static bool IsValidSegment(std::size_t row, std::size_t column, char c);

    static std::size_t GetSegmentIndex(std::size_t row, std::size_t column);
};

std::unordered_map<Illumination, Number> OCR::standard_;

std::vector<Illumination> OCR::Scan(std::size_t num_digits) {
    InitializeStandard();
    std::string line;
    std::vector<Illumination> illuminations(num_digits);

    for (std::size_t i = 0; i < 3; ++i) {
        auto row = i;
        std::getline(std::cin, line);
        NormalizeInput(line);
        assert(line.length() % 3 == 0);

        for (std::size_t j = 0, i_illumination = 0; j < line.length(); ++j, i_illumination = j / 3) {
            auto column = j % 3;
            if (IsValidSegment(row, column, line[j])) {
                illuminations[i_illumination] |= (1 << GetSegmentIndex(row, column));
            }
        }
    }

    return illuminations;
}

bool OCR::IsValidSegment(std::size_t row, std::size_t column, char c) {
    if (row == 0) {
        if ((column == 1) && (c == '_')) {
            return true;
        }
    }

    if ((row == 1) || (row == 2)) {
        if ((column == 0) && (c == '|')) {
            return true;
        }

        if ((column == 1) && (c == '_')) {
            return true;
        }

        if ((column == 2) && (c == '|')) {
            return true;
        }
    }

    return false;
}

std::size_t OCR::GetSegmentIndex(std::size_t row, std::size_t column) {
    if ((row == 0) && (column == 1)) {
        return 6;
    }

    if ((row == 1) && (column == 2)) {
        return 5;
    }

    if ((row == 2) && (column == 2)) {
        return 4;
    }

    if ((row == 2) && (column == 1)) {
        return 3;
    }

    if ((row == 2) && (column == 0)) {
        return 2;
    }

    if ((row == 1) && (column == 0)) {
        return 1;
    }

    if ((row == 1) && (column == 1)) {
        return 0;
    }

    assert(false);
    return 0;
}

OCR::OCR() {
    InitializeStandard();
}

void OCR::NormalizeInput(std::string &line) {
    if (line.length() % 3 == 0) {
        return;
    }

    if (line.length() == 28) {
        line.pop_back();
        return;
    }

    line += std::string(" ", 27 - line.length());
}

void OCR::InitializeStandard() {
    if (standard_.empty()) {
        standard_[Illumination("1111110")] = 0;
        standard_[Illumination("0110000")] = 1;
        standard_[Illumination("1101101")] = 2;
        standard_[Illumination("1111001")] = 3;
        standard_[Illumination("0110011")] = 4;
        standard_[Illumination("1011011")] = 5;
        standard_[Illumination("1011111")] = 6;
        standard_[Illumination("1110000")] = 7;
        standard_[Illumination("1111111")] = 8;
        standard_[Illumination("1111011")] = 9;
    }
}

DigitsInfo OCR::GetDigits(const std::vector<Illumination> &illuminations) {
    DigitsInfo info;

    auto garbled_digit_seen = false;
    for (const auto &illumination : illuminations) {
        Digit digit;
        auto num_it = standard_.find(illumination);
        if (num_it != standard_.end()) {
            digit.exact = num_it->second;
        } else {
            if (garbled_digit_seen) {
                return info;
            }

            digit.is_garbled = true;
            garbled_digit_seen = true;
        }

        digit.garbled = GetGarbledNumbers(illumination);
        info.digits.emplace_back(digit);
    }

    info.is_valid = true;
    return info;
}

std::list<Number> OCR::GetGarbledNumbers(const Illumination &illumination) {
    std::list<Number> garbled_nums;

    for (const auto &item : standard_) {
        auto burnout = item.first ^illumination;
        if (IsPowerOf2(burnout) && ((burnout & item.first) == burnout)) {
            garbled_nums.emplace_back(item.second);
        }
    }

    return garbled_nums;
}

bool OCR::IsPowerOf2(const Illumination &illumination) {
    auto x = illumination.to_ulong();
    return (x > 0) && !(x & (x - 1));
}

int main() {
    auto illuminations = OCR::Scan(9);
//    Print(OCR::standard_, illuminations);
    auto digits = OCR::GetDigits(illuminations);
    Print(digits);
    return 0;
}