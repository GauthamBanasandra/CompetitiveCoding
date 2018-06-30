#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>

using big_int = unsigned long long;

struct Problem {
    int id;
    bool solved;
    int incorrect_subs;
};

struct Contestant {
    int id;
    int prbs_solved;
    big_int penalty_time;
    std::unordered_map<int, Problem> prb_attempted;
};

inline bool ContestantComparator(const Contestant &a, const Contestant &b) {
    if (a.prbs_solved > b.prbs_solved) {
        return true;
    }

    if (a.prbs_solved < b.prbs_solved) {
        return false;
    }

    if (a.penalty_time < b.penalty_time) {
        return true;
    }

    if (a.penalty_time > b.penalty_time) {
        return false;
    }

    if (a.id < b.id) {
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    big_int n;
    int cnt_num, prb_num, time, c = 0;
    char verdict;
    std::string line;
    std::unordered_map<int, Contestant> cnts;

    scanf("%llu\n\n", &n);
    while (n--) {
        cnts.clear();
        while (getline(std::cin, line), line.length()) {
            std::istringstream buf(line);
            buf >> cnt_num;
            buf >> prb_num;
            buf >> time;
            buf >> verdict;

            auto &contestant = cnts[cnt_num];
            auto &problem = cnts[cnt_num].prb_attempted[prb_num];
            contestant.id = cnt_num;
            if (problem.solved) {
                continue;
            }

            switch (line[line.length() - 1]) {
                case 'C':
                    contestant.penalty_time += time + problem.incorrect_subs * 20;
                    ++contestant.prbs_solved;
                    problem.solved = true;
                    break;
                case 'I':
                    ++problem.incorrect_subs;
                    break;
                case 'R':
                case 'U':
                case 'E':
                    break;
                default:
                    assert(false);
            }
        }

        if (c > 0) {
            printf("\n");
        }

        ++c;
        auto i = 0;
        std::vector<Contestant> cnt_v(cnts.size());
        for (auto &cnt : cnts) {
            cnt_v[i++] = cnt.second;
        }

        sort(cnt_v.begin(), cnt_v.end(), ContestantComparator);
        for (const auto &cnt : cnt_v) {
            printf("%d %d %llu\n", cnt.id, cnt.prbs_solved, cnt.penalty_time);
        }
    }

    return 0;
}
