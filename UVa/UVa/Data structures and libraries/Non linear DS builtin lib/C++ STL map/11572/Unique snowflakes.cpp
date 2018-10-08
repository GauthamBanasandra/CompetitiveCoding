#include <algorithm>
#include <iostream>
#include <unordered_map>

using big_int = unsigned long long;

int main(int argc, char *argv[]) {
    big_int t, n, id, current_run = 0, longest_run = 0;
    std::unordered_map<big_int, big_int> snowflake_index;

    std::cin >> t;
    while (t--) {
        snowflake_index.clear();
        current_run = longest_run = 0;
        std::cin >> n;
        for (big_int i = 0; i < n; ++i) {
            std::cin >> id;
            const auto index = snowflake_index.find(id);
            if (index != snowflake_index.end() && index->second >= i - current_run) {
                longest_run = std::max(longest_run, current_run);
                current_run = i - index->second;
            } else {
                ++current_run;
            }

            snowflake_index[id] = i;
        }

        std::cout << std::max(longest_run, current_run) << std::endl;
    }

    return 0;
}
