#include <cassert>
#include <ios>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

namespace uva_910 {
using Count = long long;

class Counter {
public:
  explicit Counter(
      const std::vector<std::tuple<size_t, size_t, size_t, bool>> &nodes,
      int num_moves);

  Count CountMoves() { return CountMoves(0, num_moves_); }

private:
  Count CountMoves(size_t node, int num_moves);

  const int num_moves_;
  std::vector<std::vector<size_t>> adj_list_;
  std::vector<int> is_node_special_;
  std::vector<std::vector<Count>> memo_;
};

Counter::Counter(
    const std::vector<std::tuple<size_t, size_t, size_t, bool>> &nodes,
    const int num_moves)
    : num_moves_{num_moves} {
  memo_.resize(nodes.size(), std::vector<Count>(num_moves_ + 1, -1));
  adj_list_.resize(nodes.size());
  is_node_special_.resize(nodes.size());

  for (const auto &[node, adj_node1, adj_node2, is_special] : nodes) {
    adj_list_[node].emplace_back(adj_node1);
    adj_list_[node].emplace_back(adj_node2);
    is_node_special_[node] = is_special ? 1 : 0;
  }
}

Count Counter::CountMoves(const size_t node, const int num_moves) {
  assert(num_moves >= 0);

  if (num_moves == 0) {
    if (is_node_special_[node] == 1) {
      return 1;
    }
    return 0;
  }

  auto &memo = memo_[node][num_moves];
  if (memo != -1) {
    return memo;
  }

  Count count = 0;
  for (const auto &adj_node : adj_list_[node]) {
    count += CountMoves(adj_node, num_moves - 1);
  }
  return memo = count;
}
} // namespace uva_910

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes;
  int num_moves;
  char node, adj_node1, adj_node2, is_special;
  std::vector<std::tuple<size_t, size_t, size_t, bool>> nodes;

  while (std::cin >> num_nodes, !std::cin.eof()) {
    nodes.resize(num_nodes);
    for (size_t i = 0; i < num_nodes; ++i) {
      std::cin >> node >> adj_node1 >> adj_node2 >> is_special;
      std::get<0>(nodes[i]) = node - 'A';
      std::get<1>(nodes[i]) = adj_node1 - 'A';
      std::get<2>(nodes[i]) = adj_node2 - 'A';
      std::get<3>(nodes[i]) = is_special == 'x';
    }
    std::cin >> num_moves;
    std::cout << uva_910::Counter(nodes, num_moves).CountMoves() << std::endl;
  }
  return 0;
}
