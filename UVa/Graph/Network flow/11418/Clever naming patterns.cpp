#include <algorithm>
#include <cassert>
#include <cctype>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace uva_11418 {
using Node = size_t;
using Capacity = int;

const auto infinity = std::numeric_limits<Capacity>::max();
const auto unvisited = -1;

class FlowNetwork {
public:
  FlowNetwork(size_t num_questions,
              const std::vector<std::vector<std::string>> &names_list);

  std::vector<std::string> GetQuestionNameAllocations();

private:
  Capacity Augment(const std::vector<Node> &parent);
  std::pair<bool, std::vector<Node>> FindAugmentingPath();
  std::vector<std::string> GetAllocations();

  const size_t num_nodes_;
  const Node source_{0};
  const Node sink_;
  const size_t num_questions_;
  const std::vector<std::vector<std::string>> &names_list_;
  std::vector<std::unordered_map<Node, Capacity>> adj_list_;
};

FlowNetwork::FlowNetwork(
    const size_t num_questions,
    const std::vector<std::vector<std::string>> &names_list)
    : num_nodes_{1 + num_questions * 2 + 1}, sink_{1 + num_questions * 2},
      num_questions_{num_questions}, names_list_{names_list} {
  assert(num_questions == names_list.size());

  std::unordered_map<char, std::vector<Node>> name_idx;
  auto index = num_questions + 1;
  for (const auto &names : names_list) {
    for (const auto &name : names) {
      name_idx[std::toupper(name.front())].emplace_back(index);
    }
    ++index;
  }

  adj_list_.resize(num_nodes_);
  for (Node i = 0; i < num_questions; ++i) {
    auto u = i + 1;
    assert(u <= 26);
    for (const auto &v : name_idx[static_cast<char>('A' + i)]) {
      adj_list_[u][v] = infinity;
      adj_list_[v][u] = 0;
    }
  }
  for (Node i = 1; i <= num_questions; ++i) {
    adj_list_[source_][i] = 1;
    adj_list_[i][source_] = 0;
  }
  for (auto i = 1 + num_questions; i < sink_; ++i) {
    adj_list_[i][sink_] = 1;
    adj_list_[sink_][i] = 0;
  }
}

std::vector<std::string> FlowNetwork::GetQuestionNameAllocations() {
  auto max_flow = 0, flow = 0;
  do {
    auto [is_reachable, bfs_spanning_tree] = FindAugmentingPath();
    if (!is_reachable) {
      return GetAllocations();
    }
    flow = Augment(bfs_spanning_tree);
    max_flow += flow;
  } while (flow != 0);
  assert(false);
  return {};
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

std::pair<bool, std::vector<Node>> FlowNetwork::FindAugmentingPath() {
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

std::vector<std::string> FlowNetwork::GetAllocations() {
  std::vector<std::string> allocations(num_questions_);
  for (auto i = num_questions_ + 1; i < sink_; ++i) {
    for (const auto &[node, capacity] : adj_list_[i]) {
      if (capacity != 1) {
        continue;
      }
      char key = static_cast<char>(node) - 1 + 'A';
      auto value_it = std::find_if(names_list_[i - num_questions_ - 1].begin(),
                                   names_list_[i - num_questions_ - 1].end(),
                                   [&key](const std::string &str) -> bool {
                                     return str.front() == key;
                                   });
      assert(value_it != names_list_[i - num_questions_ - 1].end());
      std::transform(value_it->begin(), value_it->end(),
                     std::back_inserter(allocations[node - 1]),
                     [](const char c) -> char { return std::tolower(c); });
      allocations[node - 1].front() =
          std::toupper(allocations[node - 1].front());
      break;
    }
  }
  return allocations;
}
} // namespace uva_11418

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t, n, k;
  std::vector<std::vector<std::string>> names_list;

  std::cin >> t;
  for (size_t c = 1; c <= t; ++c) {
    std::cin >> n;
    names_list.resize(n);
    for (size_t i = 0; i < n; ++i) {
      std::cin >> k;
      names_list[i].resize(k);
      for (size_t j = 0; j < k; ++j) {
        std::cin >> names_list[i][j];
        names_list[i][j].front() = std::toupper(names_list[i][j].front());
      }
    }
    std::cout << "Case #" << c << ":" << std::endl;
    for (const auto &allocation :
         uva_11418::FlowNetwork(n, names_list).GetQuestionNameAllocations()) {
      std::cout << allocation << std::endl;
    }
  }
  return 0;
}
