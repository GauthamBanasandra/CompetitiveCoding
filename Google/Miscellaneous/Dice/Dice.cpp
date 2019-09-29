#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dice {
using Node = size_t;
using Capacity = int;

const auto infinity = std::numeric_limits<Capacity>::max();
const auto unvisited = -1;

class FlowNetwork {
public:
  FlowNetwork(const std::vector<std::string> &dice, const std::string &target);

  bool IsReachable();

private:
  Capacity Augment(const std::vector<Node> &parent);
  [[nodiscard]] std::pair<bool, std::vector<Node>> FindAugmentingPath() const;

  const Node source_{0};
  const size_t target_len_;
  Node sink_{0};
  size_t num_nodes_{0};
  std::vector<std::unordered_map<Node, Capacity>> adj_list_;
};

FlowNetwork::FlowNetwork(const std::vector<std::string> &dice,
                         const std::string &target)
    : target_len_(target.size()) {
  Node index = 1;
  std::unordered_map<char, Node> letter_idx;
  for (const auto &each_dice : dice) {
    for (const auto &letter : each_dice) {
      if (letter_idx.find(letter) == letter_idx.end()) {
        letter_idx[letter] = index++;
      }
    }
  }
  for (const auto &letter : target) {
    if (letter_idx.find(letter) == letter_idx.end()) {
      letter_idx[letter] = index++;
    }
  }

  num_nodes_ = 1                   // source
               + letter_idx.size() // unique letters
               + dice.size()       // dice
               + 1;                // sink

  sink_ = num_nodes_ - 1; // Last node is the sink

  adj_list_.resize(num_nodes_);

  for (Node i = 0, len = dice.size(), dice_idx_offset = letter_idx.size() + 1;
       i < len; ++i) {
    for (const auto &letter : dice[i]) {
      adj_list_[letter_idx[letter]][i + dice_idx_offset] = infinity;
      adj_list_[i + dice_idx_offset][letter_idx[letter]] = 0;
    }
  }

  for (const auto &letter : target) {
    ++adj_list_[source_][letter_idx[letter]];
    adj_list_[letter_idx[letter]][source_] = 0;
  }

  // Each dice can only be used once
  for (auto i = letter_idx.size() + 1; i < sink_; ++i) {
    adj_list_[i][sink_] = 1;
    adj_list_[sink_][i] = 0;
  }
}

bool FlowNetwork::IsReachable() {
  auto max_flow = 0, flow = 0;
  do {
    auto [is_reachable, bfs_spanning_tree] = FindAugmentingPath();
    if (!is_reachable) {
      return max_flow == static_cast<int>(target_len_);
    }
    flow = Augment(bfs_spanning_tree);
    max_flow += flow;
  } while (flow != 0);
  return false;
}

Capacity FlowNetwork::Augment(const std::vector<Node> &parent) {
  auto min_capacity = infinity;
  for (auto node = sink_; node != source_; node = parent[node]) {
    min_capacity = std::min(min_capacity, adj_list_[parent[node]][node]);
  }
  for (auto node = sink_; node != source_; node = parent[node]) {
    adj_list_[parent[node]][node] -= min_capacity;
    adj_list_[node][parent[node]] += min_capacity;
  }
  return min_capacity;
}

std::pair<bool, std::vector<Node>> FlowNetwork::FindAugmentingPath() const {
  std::vector<int> visited(num_nodes_, unvisited);
  std::vector<Node> parent(num_nodes_, std::numeric_limits<Node>::max());
  std::queue<Node> order;
  visited[source_] = 1;
  order.emplace(source_);

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();
    if (node == sink_) {
      return std::make_pair(true, std::move(parent));
    }

    for (const auto &[adj_node, capacity] : adj_list_[node]) {
      if (capacity > 0 && visited[adj_node] == unvisited) {
        parent[adj_node] = node;
        order.emplace(adj_node);
        visited[adj_node] = 1;
      }
    }
  }
  return std::make_pair(false, std::move(parent));
}
} // namespace dice

int main(int argc, char *argv[]) {
  const std::vector<std::string> dice{"AABCDE", "BCDKAX", "KECZAD", "ABCESK",
                                      "EISLIA", "KOWPAC", "BQMXAX", "CKIELA"};
  const auto target = "ACCEICBK";

  std::cout << (dice::FlowNetwork(dice, target).IsReachable() ? "Yes" : "No")
            << std::endl;
  return 0;
}
