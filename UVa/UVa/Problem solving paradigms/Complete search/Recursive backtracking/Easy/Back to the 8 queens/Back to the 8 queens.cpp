//
// Created by gauth on 31-03-2018.
//

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>

class NQueens {
public:
    NQueens(std::vector<int> initial_queens_pos, const int n_column, const int n_row) : initial_queens_pos(std::move(
            initial_queens_pos)), n_column(n_column), n_row(n_row) {}

    int Solve();

    std::vector<int> initial_queens_pos;
    const int n_column, n_row;

private:
    int Solve(int column, std::vector<int> &queens_pos);

    int GetMoves(const std::vector<int> &queens_pos);

    bool IsSafe(int row, int column, const std::vector<int> &queens_pos);
};

int NQueens::Solve(int column, std::vector<int> &queens_pos) {
    if (column == n_column) {
        return GetMoves(queens_pos);
    }

    int min_moves = n_row;
    for (int row = 0; row < n_row; ++row) {
        if (!IsSafe(row, column, queens_pos)) {
            continue;
        }

        queens_pos[column] = row;
        min_moves = std::min(min_moves, Solve(column + 1, queens_pos));
    }

    return min_moves;
}

bool NQueens::IsSafe(int row, int column, const std::vector<int> &queens_pos) {
    for (int c = 0; c < column; ++c) {
        if ((row == queens_pos[c]) || (std::abs(row - queens_pos[c]) == std::abs(c - column))) {
            return false;
        }
    }

    return true;
}

int NQueens::GetMoves(const std::vector<int> &queens_pos) {
    int distance = 0;
    for (std::size_t i = 0; i < queens_pos.size(); ++i) {
        if (initial_queens_pos[i] != queens_pos[i]) {
            ++distance;
        }
    }

    return distance;
}

int NQueens::Solve() {
    std::vector<int> queens_pos(n_column, 0);
    return Solve(0, queens_pos);
}

int main() {
    int t = 0, r = 0;
    std::string line;
    std::vector<int> initial_queens_pos;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        initial_queens_pos.clear();
        std::istringstream tokenizer(line);
        while (tokenizer >> r) {
            initial_queens_pos.emplace_back(r - 1);
        }

        printf("Case %d: %d\n", ++t, NQueens(initial_queens_pos, 8, 8).Solve());
    }

    return 0;
}