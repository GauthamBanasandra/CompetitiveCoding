// WA

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

using Count = long long;
using Node = int;

class Scheduler {
public:
  explicit Scheduler(const std::string &configuration);

  Count GetConfigurationsCount() const;

private:
  void TopologicalSort(Node node, std::vector<int> &visited,
                       std::vector<Node> &order) const;
  std::vector<Node> TopologicalSort() const;
  std::unordered_set<Node>
  GetForbiddenNodes(const std::string &configuration) const;
  bool IsOutside(const Node i, const Node j) const {
    return i < 0 || i >= num_rows_ || j < 0 || j >= num_columns_;
  }
  bool IsConflicting(int a, int b, int c, int d) const;
  Node Hash(const int u, const int v) const { return u * num_columns_ + v; }

  std::vector<std::vector<Node>> adj_list_;
  const int num_rows_;
  const int num_columns_;
  const Node source_;
  const Node destination_;
  size_t num_nodes_{0};
};

Scheduler::Scheduler(const std::string &configuration)
    : num_rows_(static_cast<int>(configuration.size())),
      num_columns_(static_cast<int>(configuration.size())),
      source_(static_cast<int>(configuration.size())),
      destination_(static_cast<int>(configuration.size()) + 1) {
  num_nodes_ = num_rows_ * num_columns_ + 2;
  adj_list_.resize(num_nodes_);
  auto forbidden_nodes = GetForbiddenNodes(configuration);
  for (auto k = 0; k < num_columns_ - 1; ++k) {
    for (auto i = 0; i < num_rows_; ++i) {
      if (forbidden_nodes.find(Hash(i, k)) != forbidden_nodes.end()) {
        continue;
      }
      for (auto j = 0; j < num_rows_; ++j) {
        if (j >= i - 1 && j <= i + 1) {
          continue;
        }
        auto u = Hash(i, k);
        auto v = Hash(j, k + 1);
        if (forbidden_nodes.find(u) == forbidden_nodes.end() &&
            forbidden_nodes.find(v) == forbidden_nodes.end()) {
          adj_list_[u].emplace_back(v);
        }
      }
    }
  }

  for (auto v = 0; v < num_rows_; ++v) {
    if (forbidden_nodes.find(Hash(v, 0)) == forbidden_nodes.end()) {
      adj_list_[source_].emplace_back(Hash(v, 0));
    }
    if (forbidden_nodes.find(Hash(v, num_columns_ - 1)) ==
        forbidden_nodes.end()) {
      adj_list_[Hash(v, num_columns_ - 1)].emplace_back(destination_);
    }
  }
}

Count Scheduler::GetConfigurationsCount() const {
  std::vector<Count> num_possibilities(num_nodes_);
  num_possibilities[source_] = 1;
  auto order = TopologicalSort();
  for (const auto &node : order) {
    for (const auto &adj_node : adj_list_[node]) {
      num_possibilities[adj_node] += num_possibilities[node];
    }
  }
  return num_possibilities[destination_];
}

void Scheduler::TopologicalSort(Node node, std::vector<int> &visited,
                                std::vector<Node> &order) const {
  if (visited[node] == 1) {
    return;
  }
  visited[node] = 1;

  for (const auto &adj_node : adj_list_[node]) {
    TopologicalSort(adj_node, visited, order);
  }
  order.emplace_back(node);
}

std::vector<Node> Scheduler::TopologicalSort() const {
  std::vector<int> visited(num_nodes_);
  std::vector<Node> order;
  order.reserve(num_nodes_);
  TopologicalSort(source_, visited, order);
  std::reverse(order.begin(), order.end());
  return order;
}

std::unordered_set<Node>
Scheduler::GetForbiddenNodes(const std::string &configuration) const {
  std::unordered_set<Node> forbidden_nodes;
  for (auto i = 0, len = static_cast<int>(configuration.size()); i < len; ++i) {
    if (configuration[i] == '?') {
      continue;
    }

    const auto u = configuration[i] - '0' - 1;
    const auto v = i;
    if (!IsOutside(u, v + 1)) {
      forbidden_nodes.insert(Hash(u, v + 1));
    }
    if (!IsOutside(u, v - 1)) {
      forbidden_nodes.insert(Hash(u, v - 1));
    }
    if (!IsOutside(u - 1, v - 1)) {
      forbidden_nodes.insert(Hash(u - 1, v - 1));
    }
    if (!IsOutside(u + 1, v + 1)) {
      forbidden_nodes.insert(Hash(u + 1, v + 1));
    }
    if (!IsOutside(u - 1, v + 1)) {
      forbidden_nodes.insert(Hash(u - 1, v + 1));
    }
    if (!IsOutside(u + 1, v - 1)) {
      forbidden_nodes.insert(Hash(u + 1, v - 1));
    }

    for (auto k = 0; k < len; ++k) {
      if (k != u) {
        forbidden_nodes.insert(Hash(k, v));
      }
    }
  }
  return forbidden_nodes;
}

int main(int argc, char *argv[]) {
  std::string configuration;
  while (std::cin >> configuration, !std::cin.eof()) {
    std::cout << Scheduler(configuration).GetConfigurationsCount() << std::endl;
  }
  return 0;
}
