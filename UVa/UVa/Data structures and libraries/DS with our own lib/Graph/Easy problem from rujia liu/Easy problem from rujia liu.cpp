#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

int main(int argc, char *argv[]) {
    int n, m, k;
    long long v;
    std::string line;
    std::unordered_map<long long, std::vector<long long>> adj_list;

    while (true) {
        std::cin >> n >> m;
        if (std::cin.eof()) {
            break;
        }

        std::cin.ignore();
        adj_list.clear();
        getline(std::cin, line);
        std::istringstream tokenizer(line);
        for (long long i = 1; i <= n; ++i) {
            tokenizer >> v;
            adj_list[v].push_back(i);
        }

        while (m-- > 0) {
            std::cin >> k >> v;
            const auto find = adj_list.find(v);
            if (find != adj_list.end() && k <= find->second.size()) {
                std::cout << find->second[k - 1] << std::endl;
            } else {
                std::cout << 0 << std::endl;
            }
        }
    }

    return 0;
}
