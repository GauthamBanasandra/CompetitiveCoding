#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

using ii = std::pair<int, int>;
using lii = std::list<ii>;

void print(const std::vector<lii> &adj_list);

class adjacency_list {
public:
    adjacency_list(int rows, int cols);

    void transpose();

    void print_sparse_matrix() const;

    std::vector<lii> adj_list;
    int rows, cols;
};

adjacency_list::adjacency_list(const int rows, const int cols) : rows(rows), cols(cols) {
    adj_list.assign(rows + 1, lii());
    std::string indices_line, values_line;
    int index, value, indices;

    for (auto i = 1; i <= rows; ++i) {
        getline(std::cin, indices_line);
        getline(std::cin, values_line);

        std::istringstream index_tokenizer(indices_line);
        std::istringstream value_tokenizer(values_line);

        index_tokenizer >> indices;
        while (indices-- > 0) {
            index_tokenizer >> index;
            value_tokenizer >> value;
            adj_list[i].emplace_back(index, value);
        }
    }
}

void adjacency_list::transpose() {
    std::vector<lii> adj_list_t(cols + 1, lii());
    for (auto i = 1; i <= rows; ++i) {
        for (const auto &item : adj_list[i]) {
            adj_list_t[item.first].emplace_back(i, item.second);
        }
    }

    adj_list = adj_list_t;

    rows += cols;
    cols = rows - cols;
    rows = rows - cols;
}

void adjacency_list::print_sparse_matrix() const {
    std::cout << rows << " " << cols << std::endl;
    for (auto i = 1; i <= rows; ++i) {
        std::cout << adj_list[i].size();
        std::string values_line;
        for (const auto &item : adj_list[i]) {
            std::cout << " " << item.first;
            values_line += std::to_string(item.second) + " ";
        }

        std::cout << std::endl;
        if (values_line.length() > 0) {
            values_line.erase(values_line.length() - 1);
        }

        std::cout << values_line << std::endl;
    }
}

int main(int argc, char *argv[]) {
    int rows, cols;

    while (true) {
        std::cin >> rows >> cols;
        std::cin.ignore();

        if (std::cin.eof()) {
            break;
        }

        adjacency_list adj_list(rows, cols);
        adj_list.transpose();
        adj_list.print_sparse_matrix();
    }

    return 0;
}
