#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace uva_825 {
const auto infinity = std::numeric_limits<int>::max();

class Scheduler {
public:
  Scheduler(size_t num_rows, size_t num_columns,
            const std::vector<std::pair<size_t, size_t>> &invalid_nodes);

  int CountPathsToDestination();

private:
  const size_t num_rows_;
  const size_t num_columns_;
  std::vector<std::vector<int>> adj_matrix_;
};

Scheduler::Scheduler(
    const size_t num_rows, const size_t num_columns,
    const std::vector<std::pair<size_t, size_t>> &invalid_nodes)
    : num_rows_{num_rows}, num_columns_{num_columns} {
  adj_matrix_.resize(num_rows_, std::vector<int>(num_columns_));
  for (const auto &[u, v] : invalid_nodes) {
    adj_matrix_[u - 1][v - 1] = infinity;
  }
}

int Scheduler::CountPathsToDestination() {
  std::queue<std::pair<size_t, size_t>> order;
  if (adj_matrix_.front().front() == infinity) {
    return 0;
  }

  adj_matrix_.front().front() = 1;
  order.emplace(0, 0);

  while (!order.empty()) {
    // Initially, I had gone wrong here by using a const reference -
    // const auto& [u, v] = order.front();
    // It was causing undefined behaviour as the reference held, was popped
    const auto [u, v] = order.front();
    order.pop();

    if (v + 1 < num_columns_ && adj_matrix_[u][v + 1] != infinity) {
      ++adj_matrix_[u][v + 1];
      order.emplace(u, v + 1);
    }

    if (u + 1 < num_rows_ && adj_matrix_[u + 1][v] != infinity) {
      ++adj_matrix_[u + 1][v];
      order.emplace(u + 1, v);
    }
  }
  return adj_matrix_[num_rows_ - 1][num_columns_ - 1];
}
} // namespace uva_825

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t, num_rows, num_columns, row, column;
  std::string line;

  std::getline(std::cin, line);
  std::istringstream t_tokenizer(line);
  t_tokenizer >> t;

  for (size_t c = 0; c < t; ++c) {
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::istringstream rc_tokenizer(line);
    rc_tokenizer >> num_rows >> num_columns;

    std::vector<std::pair<size_t, size_t>> invalid_nodes;
    for (size_t i = 0; i < num_rows; ++i) {
      std::getline(std::cin, line);
      std::istringstream r_tokenizer(line);
      r_tokenizer >> row;
      while (r_tokenizer >> column) {
        invalid_nodes.emplace_back(row, column);
      }
    }

    if (c > 0) {
      std::cout << std::endl;
    }
    std::cout << uva_825::Scheduler(num_rows, num_columns, invalid_nodes)
                     .CountPathsToDestination()
              << std::endl;
  }
  return 0;
}
