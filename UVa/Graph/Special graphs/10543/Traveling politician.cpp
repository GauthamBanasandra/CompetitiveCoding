#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <utility>
#include <vector>

namespace uva_10543 {
using Node = size_t;
using Count = long long;
using EdgeList = std::vector<std::pair<Node, Node>>;

const auto infinity = std::numeric_limits<Count>::max();

class Counter {
public:
  Counter(size_t num_nodes, const EdgeList &edge_list, Count min_speeches,
          Count max_speeches);

  std::pair<bool, Count> MinSpeeches();

private:
  Count MinSpeeches(Node node, Count speech_count);

  const size_t num_nodes_;
  const Count min_speeches_;
  const Count max_speeches_;
  const Node source_node_{0};
  const Node target_node_;
  std::vector<std::vector<Node>> adj_list_;
  std::vector<std::vector<Count>> memo_;
};

Counter::Counter(const size_t num_nodes, const EdgeList &edge_list,
                 const Count min_speeches, const Count max_speeches)
    : num_nodes_{num_nodes}, min_speeches_{min_speeches},
      max_speeches_{max_speeches}, target_node_{num_nodes - 1} {
  assert(num_nodes > 0);
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list) {
    adj_list_[u].emplace_back(v);
  }

  memo_.resize(num_nodes_, std::vector<Count>(max_speeches_ + 1, -1));
}

std::pair<bool, Count> Counter::MinSpeeches() {
  auto count = MinSpeeches(source_node_, 1);
  return {count != infinity, count};
}

Count Counter::MinSpeeches(const Node node, const Count speech_count) {
  if (speech_count > max_speeches_) {
    return infinity;
  }

  if (speech_count >= min_speeches_ && node == target_node_) {
    return speech_count;
  }

  auto &memo = memo_[node][speech_count];
  if (memo != -1) {
    return memo;
  }

  auto min_speeches = infinity;
  for (const auto &adj_node : adj_list_[node]) {
    if (adj_node == node) {
      continue;
    }

    auto count = MinSpeeches(adj_node, speech_count + 1);
    if (count >= min_speeches_) {
      min_speeches = std::min(min_speeches, count);
    }
  }
  return memo = min_speeches;
}
} // namespace uva_10543

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_cities;
  size_t num_roads;
  uva_10543::Count min_speeches;
  uva_10543::EdgeList edge_list;

  while (std::cin >> num_cities >> num_roads >> min_speeches,
         num_cities || num_roads || min_speeches) {
    edge_list.resize(num_roads);
    for (size_t i = 0; i < num_roads; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    auto [is_possible, count] =
        uva_10543::Counter(num_cities, edge_list, min_speeches, 20)
            .MinSpeeches();
    if (!is_possible) {
      std::cout << "LOSER" << std::endl;
    } else {
      std::cout << count << std::endl;
    }
  }
  return 0;
}
