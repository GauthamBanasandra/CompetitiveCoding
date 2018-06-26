#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <forward_list>

#define PAGE_ROW 60
#define PAGE_COL 60
#define MID_EVEN 30
#define MID_ODD 31
#define C5_ROW_LEN 5
#define C5_COL_LEN 6

char page[PAGE_ROW + 10][PAGE_COL + 10];
std::forward_list<std::pair<int, int>> pos_dirty;

inline int Col(char cmd, int n) {
    switch (cmd) {
        case 'C':
            return n & 1 ? MID_ODD - static_cast<int>(floor(n / 2.0)) - 1 : MID_EVEN - n / 2;

        case 'R':
            return PAGE_COL - n;

        case 'L':
            return 0;

        default:
            assert(false);
    }

    return -1;
}

inline std::pair<int, int> Pos(int x, int y) {
    return std::make_pair(x, y);
}

inline bool Write(int x, int y, char c) {
    if (x >= 0 && y >= 0 && x < PAGE_ROW && y < PAGE_COL) {
        page[x][y] = c;
        pos_dirty.push_front(std::make_pair(x, y));
        return true;
    }

    return false;
}


int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    for (auto i = 0; i < PAGE_ROW + 10; ++i) {
        for (auto j = 0; j < PAGE_COL + 10; ++j) {
            page[i][j] = '.';
        }
    }

    const std::vector<std::pair<int, int>> letter_a({
                                                            Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2), Pos(2, 3), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_b({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2), Pos(2, 3),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_c({
                                                            Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0),
                                                            Pos(3, 0),
                                                            Pos(4, 1), Pos(4, 2), Pos(4, 3), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_d({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_e({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 0),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2),
                                                            Pos(3, 0),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_f({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 0),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2),
                                                            Pos(3, 0),
                                                            Pos(4, 0)
                                                    });

    const std::vector<std::pair<int, int>> letter_g({
                                                            Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 0),
                                                            Pos(2, 0), Pos(2, 3), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_h({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2), Pos(2, 3), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_i({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 2),
                                                            Pos(2, 2),
                                                            Pos(3, 2),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_j({
                                                            Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 3),
                                                            Pos(2, 3),
                                                            Pos(3, 0), Pos(3, 3),
                                                            Pos(4, 1), Pos(4, 2)
                                                    });

    const std::vector<std::pair<int, int>> letter_k({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 3),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2),
                                                            Pos(3, 0), Pos(3, 3),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_l({
                                                            Pos(0, 0),
                                                            Pos(1, 0),
                                                            Pos(2, 0),
                                                            Pos(3, 0),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_m({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 1), Pos(1, 3), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 2), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_n({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 1), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 2), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 3), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_o({
                                                            Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_p({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2), Pos(2, 3),
                                                            Pos(3, 0),
                                                            Pos(4, 0)
                                                    });

    const std::vector<std::pair<int, int>> letter_q({
                                                            Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 3), Pos(3, 4),
                                                            Pos(4, 1), Pos(4, 2), Pos(4, 3), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_r({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 1), Pos(2, 2), Pos(2, 3),
                                                            Pos(3, 0), Pos(3, 3),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_s({
                                                            Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 0),
                                                            Pos(2, 1), Pos(2, 2), Pos(2, 3),
                                                            Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_t({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 2), Pos(1, 4),
                                                            Pos(2, 2),
                                                            Pos(3, 2),
                                                            Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_u({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 4),
                                                            Pos(4, 1), Pos(4, 2), Pos(4, 3)
                                                    });

    const std::vector<std::pair<int, int>> letter_v({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 1), Pos(2, 3),
                                                            Pos(3, 1), Pos(3, 3),
                                                            Pos(4, 2)
                                                    });

    const std::vector<std::pair<int, int>> letter_w({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 0), Pos(1, 4),
                                                            Pos(2, 0), Pos(2, 2), Pos(2, 4),
                                                            Pos(3, 0), Pos(3, 1), Pos(3, 3), Pos(3, 4),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_x({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 1), Pos(1, 3),
                                                            Pos(2, 2),
                                                            Pos(3, 1), Pos(3, 3),
                                                            Pos(4, 0), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> letter_y({
                                                            Pos(0, 0), Pos(0, 4),
                                                            Pos(1, 1), Pos(1, 3),
                                                            Pos(2, 2),
                                                            Pos(3, 2),
                                                            Pos(4, 2)
                                                    });

    const std::vector<std::pair<int, int>> letter_z({
                                                            Pos(0, 0), Pos(0, 1), Pos(0, 2), Pos(0, 3), Pos(0, 4),
                                                            Pos(1, 3),
                                                            Pos(2, 2),
                                                            Pos(3, 1),
                                                            Pos(4, 0), Pos(4, 1), Pos(4, 2), Pos(4, 3), Pos(4, 4)
                                                    });

    const std::vector<std::pair<int, int>> blank;

    std::unordered_map<char, const std::vector<std::pair<int, int>> *> letters;
    letters['A'] = &letter_a;
    letters['B'] = &letter_b;
    letters['C'] = &letter_c;
    letters['D'] = &letter_d;
    letters['E'] = &letter_e;
    letters['F'] = &letter_f;
    letters['G'] = &letter_g;
    letters['H'] = &letter_h;
    letters['I'] = &letter_i;
    letters['J'] = &letter_j;
    letters['K'] = &letter_k;
    letters['L'] = &letter_l;
    letters['M'] = &letter_m;
    letters['N'] = &letter_n;
    letters['O'] = &letter_o;
    letters['P'] = &letter_p;
    letters['Q'] = &letter_q;
    letters['R'] = &letter_r;
    letters['S'] = &letter_s;
    letters['T'] = &letter_t;
    letters['U'] = &letter_u;
    letters['V'] = &letter_v;
    letters['W'] = &letter_w;
    letters['X'] = &letter_x;
    letters['Y'] = &letter_y;
    letters['Z'] = &letter_z;
    letters[' '] = &blank;

    std::string line, cmd, font, row_str, col_str;
    int row, col;
    while (getline(std::cin, line)) {
        row = col = -1;
        std::istringstream buf(line);
        buf >> cmd;
        if (cmd[1] == 'E') {
            for (auto i = 0; i < PAGE_ROW; ++i) {
                for (auto j = 0; j < PAGE_COL; ++j) {
                    printf("%c", page[i][j]);
                }

                printf("\n");
            }

            printf("\n");
            for (auto i = 0; i < PAGE_ROW; ++i) {
                printf("-");
            }

            printf("\n\n");

            for (const auto pos : pos_dirty) {
                page[pos.first][pos.second] = '.';
            }

            pos_dirty.clear();
            if (std::cin.eof()) { break; }
            continue;
        }

        buf >> font;
        buf >> row_str;
        row = atoi(row_str.c_str()) - 1;
        if (cmd[1] == 'P') {
            buf >> col_str;
            col = atoi(col_str.c_str()) - 1;
        }

        assert(row >= 0);
        assert(line.length() > static_cast<int>(buf.tellg()) + 2);
        auto content = line.substr(static_cast<int>(buf.tellg()) + 2,
                                   line.length() - (static_cast<int>(buf.tellg()) + 3));

        if (!content.length() || row > PAGE_ROW) { continue; }
        if (font[1] == '1') {
            if (cmd[1] != 'P') {
                col = Col(cmd[1], static_cast<int>(content.length()));
            }

            for (auto i = 0; i < content.length(); ++i) {
                if (content[i] == ' ') { continue; }
                if (!Write(row, col + i, content[i])) { break; }
            }
        } else if (font[1] == '5') {
            if (cmd[1] != 'P') {
                col = Col(cmd[1], C5_COL_LEN * static_cast<int>(content.length()));
            }

            for (auto c : content) {
                if (col >= PAGE_COL) { break; }
                for (const auto pos : *letters[toupper(c)]) {
                    Write(row + pos.first, col + pos.second, '*');
                }

                col += C5_COL_LEN;
            }
        } else { assert(false); }
    }

    return 0;
}
