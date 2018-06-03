#include <iostream>
#include <string>
#include <sstream>
#include <set>

int main(int argc, char *argv[]) {
    long int n, promotion_cost = 0, bill = 0, k = 0;
    std::string line;
    std::multiset<unsigned long long> urn;
    while (std::cin >> n, n) {
        std::cin.ignore();
        promotion_cost = 0;
        urn.clear();
        while (n--) {
            getline(std::cin, line);
            std::istringstream tokenizer(line);
            tokenizer >> k;
            while (k-- > 0) {
                tokenizer >> bill;
                urn.insert(bill);
            }

            const auto least_it = urn.begin();
            const auto greatest_it = urn.rbegin();

            promotion_cost += *greatest_it - *least_it;
            urn.erase(prev(urn.end()));
            urn.erase(least_it);
        }

        std::cout << promotion_cost << std::endl;
    }

    return 0;
}
