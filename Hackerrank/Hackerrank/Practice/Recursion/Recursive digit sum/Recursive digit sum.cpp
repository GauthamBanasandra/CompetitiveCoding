//
// Created by gauth on 02-05-2018.
//

#include <string>
#include <iostream>
#include <utility>

using ull = unsigned long long;

class SuperDigit {
public:
    SuperDigit(std::string number_, const ull k) : k_(k), number_(std::move(number_)) {}

    ull GetSuperDigit() const;

private:
    ull GetSuperDigit(ull number) const;

    const ull k_;
    const std::string number_;
};

ull SuperDigit::GetSuperDigit() const {
    ull sum = 0;
    for (const auto digit : number_) {
        sum += digit - '0';
    }

    return GetSuperDigit(sum * k_);
}

ull SuperDigit::GetSuperDigit(ull number) const {
    if (number < 10) {
        return number;
    }

    ull sum = 0;
    while (number) {
        sum += number % 10;
        number /= 10;
    }

    return GetSuperDigit(sum);
}

int main() {
    std::string number;
    ull k;

    std::cin >> number >> k;
    std::cout << SuperDigit(number, k).GetSuperDigit() << std::endl;
    return 0;
}