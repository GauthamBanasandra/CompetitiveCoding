#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_map>

int main(int argc, char *argv[]) {
    int qnum, period, k;
    std::priority_queue<std::pair<long long, int>> scheduler;
    std::unordered_map<int, int> timers;
    std::string line;

    while (getline(std::cin, line), line[0] != '#') {
        std::istringstream tokenizer(line);
        tokenizer.ignore(8);
        tokenizer >> qnum;
        tokenizer >> period;
        timers[qnum] = period;
        scheduler.emplace(-period, -qnum);
    }

    std::cin >> k;
    while (k--) {
        auto query = scheduler.top();
        scheduler.pop();
        std::cout << -query.second << std::endl;
        query.first -= timers[-query.second];
        scheduler.emplace(query);
    }

    return 0;
}
