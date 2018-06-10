//
// Created by gauth on 10-06-2018.
//

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

using ll = long long;
using Country = char;
using Candidates = std::vector<ll>;

struct CandidatesInfo {
    CandidatesInfo() : matched(true), begin_serial(0), end_serial(0) {}

    bool matched;
    ll begin_serial;
    ll end_serial;
};

class CandidatesSelection {
public:
    CandidatesSelection(const std::string &candidates_line);

    CandidatesInfo GetCandidates(const std::string &pattern);

private:
    std::unordered_map<Country, Candidates> country_candidates_;
};

CandidatesSelection::CandidatesSelection(const std::string &candidates_line) {
    for (std::size_t i = 0; i < candidates_line.size(); ++i) {
        country_candidates_[candidates_line[i]].emplace_back(i);
    }
}

CandidatesInfo CandidatesSelection::GetCandidates(const std::string &pattern) {
    CandidatesInfo info;

    ll find_i = -1;
    for (size_t i = 0; i < pattern.length(); ++i, ++find_i) {
        auto find_country = country_candidates_.find(pattern[i]);
        if (find_country == country_candidates_.end()) {
            info.matched = false;
            break;
        }

        auto candidates = find_country->second;
        auto find_candidate = std::lower_bound(candidates.begin(), candidates.end(), find_i);
        if (find_candidate == candidates.end()) {
            info.matched = false;
            break;
        }

        find_i = *find_candidate;

        if (i == 0) {
            info.begin_serial = find_i;
        }

        if (i == pattern.length() - 1) {
            info.end_serial = find_i;
        }
    }

    return info;
}

int main() {
//    std::ios::sync_with_stdio(false);

    int q;
    std::string candidates_line, pattern;

    std::cin >> candidates_line;
    CandidatesSelection selection(candidates_line);

    std::cin >> q;
    while (q-- > 0) {
        std::cin >> pattern;
        auto info = selection.GetCandidates(pattern);

        if (info.matched) {
            printf("Matched %lli %lli\n", info.begin_serial, info.end_serial);
        } else {
            std::cout << "Not matched" << std::endl;
        }
    }

    return 0;
}