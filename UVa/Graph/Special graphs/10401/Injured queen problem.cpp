// WIP

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using Cost = long long;
using Node = int;

class Scheduler {
public:
  explicit Scheduler(const std::string &configuration);

  Cost GetConfigurationsCount() const;

private:
  void TopologicalSort(Node node, std::vector<int> &visited,
                       std::unordered_set<Node> &order) const;
  std::vector<Node> TopologicalSort();
  std::unordered_set<Node> GetForbiddenNodes(const std::string &configuration);
  bool IsOutside(const Node i, const Node j) const {
    return i < 0 || i >= num_rows_ || j < 0 || j >= num_columns_;
  }
  Node Hash(const int u, const int v) const { return u * num_columns_ + v; }

  std::vector<std::vector<Node>> adj_list_;
  const int num_rows_;
  const int num_columns_;
  const Node source_;
  const Node destination_;
};

Scheduler::Scheduler(const std::string &configuration)
    : num_rows_(static_cast<int>(configuration.size())),
      num_columns_(static_cast<int>(configuration.size())),
      source_(static_cast<int>(configuration.size())),
      destination_(static_cast<int>(configuration.size()) + 1) {}

std::unordered_set<Node>
Scheduler::GetForbiddenNodes(const std::string &configuration) {
  std::unordered_set<Node> forbidden_nodes;
  for (auto i = 0, len = static_cast<int>(configuration.size()); i < len; ++i) {
    if (configuration[i] == '?') {
      continue;
    }

    auto u = configuration[i] - '0' - 1;
    auto v = i;
    if (!IsOutside(u, v + 1)) {
      forbidden_nodes.insert(Hash(u, v + 1));
    }
    if (!IsOutside(u, v - 1)) {
      forbidden_nodes.insert(Hash(u, v - 1));
    }
  }
  return forbidden_nodes;
}

int main(int argc, char *argv[]) { return 0; }
