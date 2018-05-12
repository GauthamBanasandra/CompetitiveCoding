// TLE
#include <iostream>
#include <stack>
#include <list>
#include <algorithm>
#include <string>

void GetAnagramicStackOps(const std::string &source, const std::string &target, std::list<std::string> &o_stack_ops) {
    std::string stack_ops;
    for (auto i = 1; i < target.length(); ++i) {
        stack_ops += "i";
    }

    for (auto i = 0; i < target.length(); ++i) {
        stack_ops += "o";
    }

    do {
        std::stack<char> anagram_stack;
        std::string anagram;
        auto source_top = 0;
        std::string temp_stack_ops = "i" + stack_ops;
        for (auto i = 0; i < temp_stack_ops.length(); ++i) {
            if (temp_stack_ops[i] == 'i') {
                anagram_stack.push(source[source_top++]);
            } else {
                if (anagram_stack.empty()) {
                    break;
                }

                anagram += anagram_stack.top();
                anagram_stack.pop();
            }
        }

        if (source_top != source.length() || !anagram_stack.empty()) {
            continue;
        }

        if (anagram == target) {
            o_stack_ops.push_back(temp_stack_ops);
        }
    } while (next_permutation(stack_ops.begin(), stack_ops.end()));
}

int main(int argc, char *argv[]) {
    std::string source, target;
    while (std::cin >> source) {
        if (source == "") {
            while (source != "") {
                std::cin >> source;
            }
        }

        std::cin >> target;
        if (target == "") {
            while (target != "") {
                std::cin >> target;
            }
        }

        auto d_src = source;
        auto d_tgt = target;
        sort(d_src.begin(), d_src.end());
        sort(d_tgt.begin(), d_tgt.end());

        printf("[\n");
        if (d_src != d_tgt) {
            printf("]\n");
            continue;
        }

        std::list<std::string> stack_ops;
        GetAnagramicStackOps(source, target, stack_ops);
        for (auto &op : stack_ops) {
            auto const len = op.length();
            for (auto i = 1; i < 2 * (len - 1); i += 2) {
                op.insert(i, 1, ' ');
            }

            printf("%s\n", op.c_str());
        }

        printf("]\n");
    }

    return 0;
}
