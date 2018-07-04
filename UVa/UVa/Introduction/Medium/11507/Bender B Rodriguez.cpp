#include <stdio.h>
#include <ios>
#include <unordered_map>

#define MAX_CHAR 5
char bend_store[MAX_CHAR];

int main() {
    std::ios::sync_with_stdio(false);

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> dfa;
    std::unordered_map<std::string, std::string> transition_pos_x;
    std::unordered_map<std::string, std::string> transition_neg_x;
    std::unordered_map<std::string, std::string> transition_pos_y;
    std::unordered_map<std::string, std::string> transition_neg_y;
    std::unordered_map<std::string, std::string> transition_pos_z;
    std::unordered_map<std::string, std::string> transition_neg_z;

    transition_pos_x["+y"] = "+y";
    transition_pos_x["-y"] = "-y";
    transition_pos_x["+z"] = "+z";
    transition_pos_x["-z"] = "-z";

    transition_neg_x["+y"] = "-y";
    transition_neg_x["-y"] = "+y";
    transition_neg_x["+z"] = "-z";
    transition_neg_x["-z"] = "+z";

    transition_pos_y["+y"] = "-x";
    transition_pos_y["-y"] = "+x";
    transition_pos_y["+z"] = "+y";
    transition_pos_y["-z"] = "+y";

    transition_neg_y["+y"] = "+x";
    transition_neg_y["-y"] = "-x";
    transition_neg_y["+z"] = "-y";
    transition_neg_y["-z"] = "-y";

    transition_pos_z["+y"] = "+z";
    transition_pos_z["-y"] = "+z";
    transition_pos_z["+z"] = "-x";
    transition_pos_z["-z"] = "+x";

    transition_neg_z["+y"] = "-z";
    transition_neg_z["-y"] = "-z";
    transition_neg_z["+z"] = "+x";
    transition_neg_z["-z"] = "-x";

    dfa["+x"] = transition_pos_x;
    dfa["-x"] = transition_neg_x;
    dfa["+y"] = transition_pos_y;
    dfa["-y"] = transition_neg_y;
    dfa["+z"] = transition_pos_z;
    dfa["-z"] = transition_neg_z;

    unsigned long long l;
    while (scanf("%llu", &l), l) {
        std::string state = "+x";
        for (unsigned long long i = 0; i < l - 1; ++i) {
            scanf("%s", bend_store);
            std::string bend = bend_store;
            if (bend != "No") {
                state = dfa[state][bend];
            }
        }

        printf("%s\n", state.c_str());
    }
}