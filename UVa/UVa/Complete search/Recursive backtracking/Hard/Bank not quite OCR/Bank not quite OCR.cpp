//
// Created by gauth on 26-05-2018.
//

// WA

#include <algorithm>
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
    RecognitionInfo() : status(RecognitionStatus::kFailure) {}

    RecognitionStatus status;
    std::string account_num;
};

void Print(const DigitsInfo &info);

void
Print(std::unordered_map<Illumination, Number> &standard, const std::vector<Illumination> &illuminations);

class OCR {
public:
    OCR(const std::vector<Illumination> &illuminations);

    std::string Recognize();

    static std::vector<Illumination> Scan(std::size_t num_digits);

    static std::unordered_map<Illumination, Number> standard_;
    std::vector<Digit> digits_;

private:
    void
    RecognizeNext(std::size_t i_digit, RecognitionInfo &info, std::string &account_num, size_t checksum,
                  bool use_exact);

    DigitsInfo GetDigits(const std::vector<Illumination> &illuminations);

    bool IsPowerOf2(const Illumination &illumination);

    std::list<Number> GetGarbledNumbers(const Illumination &illumination);

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

OCR::OCR(const std::vector<Illumination> &illuminations) {
    InitializeStandard();
    auto info = GetDigits(illuminations);
    if (info.is_valid) {
        std::reverse_copy(info.digits.begin(), info.digits.end(), std::back_inserter(digits_));
    }
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

void OCR::RecognizeNext(std::size_t i_digit, RecognitionInfo &info, std::string &account_num, size_t checksum,
                        bool use_exact) {
    if (i_digit == digits_.size()) {
        assert(info.status != RecognitionStatus::kAmbiguous);

        if (checksum % 11 == 0) {
            if (info.status == RecognitionStatus::kValid) {
                info.status = RecognitionStatus::kAmbiguous;
                return;
            }

            info.status = RecognitionStatus::kValid;
            info.account_num = account_num;
        }

        return;
    }

    if (info.status == RecognitionStatus::kAmbiguous) {
        return;
    }

    const auto &digit = digits_[i_digit];
    if (!digit.is_garbled) {
        account_num.push_back(static_cast<char>(digit.exact + '0'));
        RecognizeNext(i_digit + 1, info, account_num, ((i_digit + 1) * digit.exact) + checksum, use_exact);
        account_num.pop_back();
    }

    if (use_exact) {
        return;
    }

    for (const auto number : digit.garbled) {
        if (info.status == RecognitionStatus::kAmbiguous) {
            return;
        }

        account_num.push_back(static_cast<char>(number + '0'));
        RecognizeNext(i_digit + 1, info, account_num, ((i_digit + 1) * number) + checksum, true);
        account_num.pop_back();
    }
}

std::string OCR::Recognize() {
    if (digits_.empty()) {
        return "failure";
    }

    std::string account_num;
    RecognitionInfo info;
    RecognizeNext(0, info, account_num, 0, false);

    switch (info.status) {
        case RecognitionStatus::kValid:
            return std::string(info.account_num.crbegin(), info.account_num.crend());

        case RecognitionStatus::kFailure:
            return "failure";

        case RecognitionStatus::kAmbiguous:
            return "ambiguous";
    }
}

int main() {
    ll t;

    std::cin >> t;
    std::cin.ignore();
    while (t-- > 0) {
        auto illuminations = OCR::Scan(9);
//    Print(OCR::standard_, illuminations);
        OCR ocr(illuminations);
        std::cout << ocr.Recognize() << std::endl;
    }

    return 0;
}