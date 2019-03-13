#include <iostream>
#include <queue>
#include <sstream>

int main(int argc, char *argv[]) {
    int n, number;
    long long cost = 0;
    std::string line;
    std::priority_queue<long long> numbers;
    while (std::cin >> n, n) {
        std::cin.ignore();
        cost = 0;

        getline(std::cin, line);
        std::istringstream tokenizer(line);
        while (tokenizer >> number) {
            numbers.push(-number);
        }

        while (numbers.size() > 1) {
            auto res = numbers.top();
            numbers.pop();
            res += numbers.top();
            numbers.pop();

            cost += res;

            numbers.push(res);
        }

        numbers.pop();
        std::cout << -cost << std::endl;
    }

    return 0;
}
