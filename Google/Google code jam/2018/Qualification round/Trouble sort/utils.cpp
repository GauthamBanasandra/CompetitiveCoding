//
// Created by gauth on 07-04-2018.
//

#include <vector>
#include <iostream>
#include <algorithm>

using ll = long long;

void Print(const std::vector<ll> &numbers) {
    std::for_each(numbers.begin(), numbers.end(), [](ll n) {
        std::cout << n << " ";
    });
    std::cout << std::endl;
}