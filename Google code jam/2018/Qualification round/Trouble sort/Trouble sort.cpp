//
// Created by gauth on 07-04-2018.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using ll = long long;

void Print(const std::vector<ll> &numbers);

struct SortInfo {
    SortInfo(bool is_valid, size_t i_error) : is_sorted(is_valid), i_error(i_error) {}

    bool is_sorted;
    std::size_t i_error;
};

void TroubleSort(std::vector<ll> &numbers) {
    std::vector<ll> i_even_num, i_odd_num;
    for (std::size_t i = 0; i < numbers.size(); ++i) {
        (i & 1 ? i_odd_num : i_even_num).emplace_back(numbers[i]);
    }

    std::sort(i_even_num.begin(), i_even_num.end());
    std::sort(i_odd_num.begin(), i_odd_num.end());
    for (std::size_t i = 0, i_odd = 0, i_even = 0; i < numbers.size(); ++i) {
        numbers[i] = (i & 1 ? i_odd_num[i_odd++] : i_even_num[i_even++]);
    }
}

SortInfo IsSorted(const std::vector<ll> &numbers) {
    assert(!numbers.empty());
    for (std::size_t i = 0; i < numbers.size() - 1; ++i) {
        if (numbers[i] > numbers[i + 1]) {
            return SortInfo{false, i};
        }
    }

    return SortInfo{true, numbers.size() + 1};
}

int main() {
    int t, n;
    ll number;
    std::vector<ll> numbers;

    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
        std::cin >> n;
        numbers.clear();
        for (int j = 0; j < n; ++j) {
            std::cin >> number;
            numbers.emplace_back(number);
        }

        TroubleSort(numbers);
        auto sort_info = IsSorted(numbers);
        printf("Case #%d: ", i);
        if (sort_info.is_sorted) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << sort_info.i_error << std::endl;
        }
    }

    return 0;
}