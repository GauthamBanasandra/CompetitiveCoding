#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_11045 {
using Node = size_t;
using Capacity = int;

const auto infinity = std::numeric_limits<Capacity>::max();
const auto unvisited = -1;

class FlowNetwork {
public:
  FlowNetwork(
      size_t num_shirts, size_t num_people,
      const std::vector<std::pair<std::string, std::string>> &preference);

  bool IsAllocationPossible();

private:
  Capacity Augment(const std::vector<Node> &parent);
  std::pair<bool, std::vector<Node>> FindAugmentingPath() const;

  const size_t num_nodes_;
  const Node source_{0};
  const Node sink_;
  const size_t num_people_;
  std::vector<std::unordered_map<Node, Capacity>> adj_list_;
  static std::unordered_map<std::string, Node> shirt_node_;
};

std::unordered_map<std::string, Node> FlowNetwork::shirt_node_;

FlowNetwork::FlowNetwork(
    const size_t num_shirts, const size_t num_people,
    const std::vector<std::pair<std::string, std::string>> &preference)
    : num_nodes_{1 + 6 + num_people + 1}, sink_{1 + 6 + num_people},
      num_people_{num_people} {
  if (shirt_node_.empty()) {
    shirt_node_ = {{"XXL", 1}, {"XL", 2}, {"L", 3},
                   {"M", 4},   {"S", 5},  {"XS", 6}};
  }

  adj_list_.resize(num_nodes_);
  const auto people_idx_offset = 1 + shirt_node_.size();
  for (size_t i = 0, len = preference.size(); i < len; ++i) {
    auto person_idx = people_idx_offset + i;
    const auto &[shirt1, shirt2] = preference[i];

    auto find_it = shirt_node_.find(shirt1);
    assert(find_it != shirt_node_.end());
    auto shirt1_idx = find_it->second;

    find_it = shirt_node_.find(shirt2);
    assert(find_it != shirt_node_.end());
    auto shirt2_idx = find_it->second;

    adj_list_[shirt1_idx][person_idx] = adj_list_[shirt2_idx][person_idx] = 1;
    adj_list_[person_idx][shirt1_idx] = adj_list_[person_idx][shirt2_idx] = 0;
  }

  for (auto i = people_idx_offset; i < sink_; ++i) {
    adj_list_[i][sink_] = 1;
    adj_list_[sink_][i] = 0;
  }

  assert(num_shirts % 6 == 0);
  for (size_t i = 1, len = shirt_node_.size(), each = num_shirts / 6; i <= len;
       ++i) {
    adj_list_[source_][i] = each;
    adj_list_[i][source_] = 0;
  }
}

bool FlowNetwork::IsAllocationPossible() {
  auto max_flow = 0, flow = 0;
  do {
    auto [is_possible, bfs_spanning_tree] = FindAugmentingPath();
    if (!is_possible) {
      return max_flow == static_cast<int>(num_people_);
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
    if (sink_ == node) {
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
} // namespace uva_11045

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t, num_shirts, num_people;
  std::vector<std::pair<std::string, std::string>> preferences;

  std::cin >> t;
  while (t--) {
    std::cin >> num_shirts >> num_people;
    preferences.resize(num_people);
    for (size_t i = 0; i < num_people; ++i) {
      std::cin >> preferences[i].first >> preferences[i].second;
    }

    std::cout << (uva_11045::FlowNetwork(num_shirts, num_people, preferences)
                          .IsAllocationPossible()
                      ? "YES"
                      : "NO")
              << std::endl;
  }
  return 0;
}
