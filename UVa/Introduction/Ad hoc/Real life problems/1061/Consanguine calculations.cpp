#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <ios>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <algorithm>

void Print(const std::string &p1, const std::string &p2, const std::unordered_set<std::string> &child_types);

void PrintPpc(const std::unordered_map<std::string, std::unordered_set<std::string>> &ppc);

void PrintPcp(const std::unordered_map<std::string, std::unordered_set<std::string>> &pcp);

typedef unsigned long long big_int;

inline std::string Hash(const std::string &t1, const std::string &t2) {
    return t1 < t2 ? t1 + " " + t2 : t2 + " " + t1;
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    std::unordered_map<std::string, std::string> rbt;
    rbt["AA++"] = "A+";
    rbt["AA+-"] = "A+";
    rbt["AO++"] = "A+";
    rbt["AO+-"] = "A+";
    rbt["BB++"] = "B+";
    rbt["BB+-"] = "B+";
    rbt["BO++"] = "B+";
    rbt["BO+-"] = "B+";
    rbt["AA--"] = "A-";
    rbt["AO--"] = "A-";
    rbt["BB--"] = "B-";
    rbt["BO--"] = "B-";
    rbt["AB++"] = "AB+";
    rbt["AB+-"] = "AB+";
    rbt["AB--"] = "AB-";
    rbt["OO++"] = "O+";
    rbt["OO+-"] = "O+";
    rbt["OO--"] = "O-";

    std::vector<std::string> rbt_list;
    for (const auto bt : rbt) {
        rbt_list.push_back(bt.first);
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> ppc, pcp;
    std::unordered_set<std::string> abo, rh, child_types;
    for (auto i = 0; i < rbt_list.size(); ++i) {
        for (auto j = i; j < rbt_list.size(); ++j) {
            const auto &p1 = rbt_list[i];
            const auto &p2 = rbt_list[j];
            abo.clear();
            rh.clear();
            child_types.clear();

            for (const auto m : p1.substr(0, 2)) {
                for (const auto n : p2.substr(0, 2)) {
                    char str[3] = {m, n};
                    str[2] = '\0';
                    std::string abo_ = str;
                    sort(abo_.begin(), abo_.end());
                    abo.insert(abo_);
                }
            }

            for (const auto m : p1.substr(2)) {
                for (const auto n : p2.substr(2)) {
                    char str[3] = {m, n};
                    str[2] = '\0';
                    std::string rh_ = str;
                    sort(rh_.begin(), rh_.end());
                    rh.insert(rh_);
                }
            }

            for (const auto abo_ : abo) {
                for (const auto rh_ : rh) {
                    child_types.insert(rbt[abo_ + rh_]);
                }
            }

            //const auto hash = Hash(rbt[p1], rbt[p2]);
            ppc[rbt[p1] + " " + rbt[p2]].insert(child_types.begin(), child_types.end());
            ppc[rbt[p2] + " " + rbt[p1]].insert(child_types.begin(), child_types.end());
            for (const auto child_type : child_types) {
                pcp[rbt[p1] + " " + child_type].insert(rbt[p2]);
                pcp[rbt[p2] + " " + child_type].insert(rbt[p1]);
            }
        }
    }

    //PrintPcp(pcp);
    big_int c = 1;
    char t1[5];
    char t2[5];
    char t3[5];
    while (scanf("%s%s%s", t1, t2, t3), t1[0] != 'E') {
        if (t3[0] == '?') {
            std::string children = "{";
            for (const auto child : ppc[std::string(t1) + " " + std::string(t2)]) {
                children += child + ", ";
            }

            assert(children.length() > 1);
            children[children.length() - 2] = '}';
            children.erase(children.length() - 1, 1);
            printf("Case %lld: %s %s %s\n", c++, t1, t2, children.c_str());
        } else if (t1[0] == '?') {
            const auto hash = std::string(t2) + " " + std::string(t3);
            const auto find = pcp.find(hash);
            if (find != pcp.end()) {
                std::string parents = "{";
                for (const auto parent : pcp[hash]) {
                    parents += parent + ", ";
                }

                assert(parents.length() > 1);
                parents[parents.length() - 2] = '}';
                parents.erase(parents.length() - 1, 1);
                printf("Case %lld: %s %s %s\n", c++, parents.c_str(), t2, t3);
            } else {
                printf("Case %lld: IMPOSSIBLE %s %s\n", c++, t2, t3);
            }
        } else if (t2[0] == '?') {
            const auto hash = std::string(t1) + " " + std::string(t3);
            const auto find = pcp.find(hash);
            if (find != pcp.end()) {
                std::string parents = "{";
                for (const auto parent : pcp[hash]) {
                    parents += parent + ", ";
                }

                assert(parents.length() > 1);
                parents[parents.length() - 2] = '}';
                parents.erase(parents.length() - 1, 1);
                printf("Case %lld: %s %s %s\n", c++, t1, parents.c_str(), t3);
            } else {
                printf("Case %lld: %s IMPOSSIBLE %s\n", c++, t1, t3);
            }
        } else { assert(false); }
    }

    return 0;
}