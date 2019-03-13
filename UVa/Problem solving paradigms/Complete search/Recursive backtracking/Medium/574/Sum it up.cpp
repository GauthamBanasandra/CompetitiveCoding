//
// Created by gauth on 22-04-2018.
//

#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <cassert>

const int MAX_N = 12;
using Numbers = std::vector<int>;
using DescendingNumbersList = std::set<Numbers, std::greater<Numbers>>;

class CombinationGenerator {
public:
    explicit CombinationGenerator(const int total, const Numbers &numbers_)
            : numbers_(numbers_), n_(numbers_.size()), total_(total) {}

    void PrintCombinations() const;

private:
    void Generate(Numbers &combination, std::size_t i_num, DescendingNumbersList &numbers_total) const;

    bool IsEqualToTotal(const Numbers &combination) const;

    const int total_;
    const std::size_t n_;
    const Numbers numbers_;

    void Print(const Numbers &combination) const;

    void Print(const DescendingNumbersList &numbers_total) const;
};

void
CombinationGenerator::Generate(Numbers &combination, std::size_t i_num, DescendingNumbersList &numbers_total) const {
    if (i_num == n_) {
        if (IsEqualToTotal(combination)) {
            numbers_total.insert(combination);
        }

        return;
    }

    combination.emplace_back(numbers_[i_num]);
    Generate(combination, i_num + 1, numbers_total);
    combination.pop_back();

    Generate(combination, i_num + 1, numbers_total);
}

void CombinationGenerator::Print(const Numbers &combination) const {
    static int count = 0;
    std::cout << ++count << " : ";

    for (const auto number : combination) {
        std::cout << number << " ";
    }

    std::cout << std::endl;
}

void CombinationGenerator::PrintCombinations() const {
    Numbers combination;
    combination.reserve(n_);
    DescendingNumbersList numbers_total;

    Generate(combination, 0, numbers_total);
    Print(numbers_total);
}

bool CombinationGenerator::IsEqualToTotal(const Numbers &combination) const {
    int total = 0;

    for (const auto number : combination) {
        if (total + number > total_) {
            return false;
        }

        total += number;
    }

    return total == total_;
}

void CombinationGenerator::Print(const DescendingNumbersList &numbers_total) const {
    printf("Sums of %d:\n", total_);

    if (numbers_total.empty()) {
        std::cout << "NONE" << std::endl;
        return;
    }

    for (const auto &numbers : numbers_total) {
        assert(!numbers.empty());

        std::cout << numbers[0];
        for (std::size_t i = 1; i < numbers.size(); ++i) {
            std::cout << "+" << numbers[i];
        }

        std::cout << std::endl;
    }
}

int main() {
    int t, n, number;
    Numbers numbers;
    numbers.reserve(MAX_N);

    while (std::cin >> t >> n, n) {
        numbers.clear();

        for (int i = 0; i < n; ++i) {
            std::cin >> number;
            numbers.emplace_back(number);
        }

        CombinationGenerator(t, numbers).PrintCombinations();
    }

    return 0;
}