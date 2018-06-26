#include <iostream>
#include <list>

int main(int argc, char *argv[]) {
    std::string line;
    std::list<char> beiju;
    while (getline(std::cin, line), !std::cin.eof()) {
        beiju.clear();
        auto it = beiju.begin();
        for (const auto &c : line) {
            if (beiju.empty() && (c == '[' || c == ']')) {
                continue;
            }

            switch (c) {
                case '[':
                    it = beiju.begin();
                    break;
                case ']':
                    it = beiju.end();
                    break;
                default:
                    it = beiju.insert(it, c);
                    ++it;
            }
        }

        std::cout << std::string(beiju.begin(), beiju.end()) << '\n';
    }

    return 0;
}
