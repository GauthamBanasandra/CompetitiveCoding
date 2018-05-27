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

void
Print(std::unordered_map<Illumination, Number> &standard, const std::vector<Illumination> &illuminations);

enum class RecognitionStatus {
    kValid, kFailure, kAmbiguous
};

struct Digit {
    Digit() : exact(0) {}

    Number exact;
    std::list<Number> garbled;
};

struct RecognitionInfo {
    RecognitionInfo() : status(RecognitionStatus::kFailure), checksum(0) {}

    RecognitionStatus status;
    std::string account_num;
    ll checksum;
};

class OCR {
public:
    OCR();

    static std::vector<Illumination> Scan(std::size_t num_digits);

    static std::unordered_map<Illumination, Number> standard_;

private:
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

int main() {
    auto illuminations = OCR::Scan(9);
    Print(OCR::standard_, illuminations);
    return 0;
}