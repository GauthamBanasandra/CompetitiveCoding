#include <vector>
#include <iostream>
#include <unordered_map>

void print(const std::vector<int> &data) {
    for (const auto &value : data) {
        std::cout << value << " ";
    }

    std::cout << std::endl;
}

void print(const std::unordered_map<int, int> &pairs) {
    for (const auto &kv : pairs) {
        std::cout << kv.first << " : " << kv.second << std::endl;
    }
}