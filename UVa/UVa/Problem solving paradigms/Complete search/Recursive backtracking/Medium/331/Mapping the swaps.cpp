//
// Created by gauth on 20-04-2018.
//

#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <cassert>
#include <iostream>

using ull = unsigned long long;

class SwapMap {
public:
    std::size_t CountUniqueSwapMaps(std::vector<ull> &numbers);

private:
    void
    SwapNext(std::vector<ull> &numbers, std::list<std::size_t> &swap_map,
             std::unordered_set<std::string> &unique_swap_maps);

    std::string HashSwapMap(const std::list<std::size_t> &swap_map) const;

    bool IsSorted(const std::vector<ull> &numbers) const;
};

std::string SwapMap::HashSwapMap(const std::list<std::size_t> &swap_map) const {
    std::string hash;
    for (const auto &i_number : swap_map) {
        hash += i_number + " ";
    }

    return hash;
}

void SwapMap::SwapNext(std::vector<ull> &numbers, std::list<std::size_t> &swap_map,
                       std::unordered_set<std::string> &unique_swap_maps) {
    if (IsSorted(numbers) && !swap_map.empty()) {
        unique_swap_maps.insert(HashSwapMap(swap_map));
        return;
    }

    assert(!numbers.empty());
    for (std::size_t i = 0; i < numbers.size() - 1; ++i) {
        if (numbers[i] <= numbers[i + 1]) {
            continue;
        }

        std::swap(numbers[i], numbers[i + 1]);
        swap_map.emplace_back(i);

        SwapNext(numbers, swap_map, unique_swap_maps);

        std::swap(numbers[i], numbers[i + 1]);
        swap_map.pop_back();
    }
}

bool SwapMap::IsSorted(const std::vector<ull> &numbers) const {
    const auto n = numbers.size();
    for (std::size_t i = 1; i < n; ++i) {
        if (numbers[i - 1] > numbers[i]) {
            return false;
        }
    }

    return true;
}

std::size_t SwapMap::CountUniqueSwapMaps(std::vector<ull> &numbers) {
    std::list<std::size_t> swap_map;
    std::unordered_set<std::string> unique_swap_maps;
    SwapNext(numbers, swap_map, unique_swap_maps);
    return unique_swap_maps.size();
}

int main() {
    int n, number;
    std::vector<ull> numbers;

    for (ull i = 1; std::cin >> n, n; ++i) {
        numbers.clear();
        numbers.resize(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> number;
            numbers.emplace_back(number);
        }

        printf("There are %zu swap maps for input data set %llu.\n", SwapMap().CountUniqueSwapMaps(numbers), i);
    }

    return 0;
}