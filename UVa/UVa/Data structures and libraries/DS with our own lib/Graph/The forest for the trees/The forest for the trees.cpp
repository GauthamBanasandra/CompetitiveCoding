#include <iostream>

int main(int argc, char *argv[]) {
    unsigned long long n, edges = 0, acorns = 0, vertices = 0;
    std::string line;
    std::bitset<26> all_vertices;

    std::cin >> n;
    std::cin.ignore();
    while (n--) {
        vertices = acorns = edges = 0;
        all_vertices.reset();
        while (getline(std::cin, line), line[0] != '*') {
            ++edges;
            all_vertices.set(line[1] - 'A', true);
            all_vertices.set(line[3] - 'A', true);
        }

        for (auto i = 'A' - 'A'; i <= 'Z' - 'A'; ++i) {
            if (all_vertices[i]) {
                ++vertices;
            }
        }

        getline(std::cin, line);
        for (const auto c : line) {
            if (c != ',' && !all_vertices[c - 'A']) {
                ++acorns;
            }
        }

        std::cout << "There are " << vertices - edges << " tree(s) and " << acorns << " acorn(s)." << std::endl;
    }

    return 0;
}
