// TLE

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <unordered_set>
#include <vector>

namespace uva_11377 {
const auto infinity = std::numeric_limits<int>::max();

class Planner {
public:
  Planner(size_t num_nodes, const std::unordered_set<size_t> &special_nodes,
          const std::vector<std::pair<size_t, size_t>> &edge_list);

  int GetMinNumAirports(size_t source, size_t destination) const;

private:
  void DFS(size_t node, size_t destination,
           std::unordered_set<size_t> &ancestry, int &num_airports) const;

  const size_t num_nodes_;
  const std::unordered_set<size_t> &special_nodes_;
  std::vector<std::vector<size_t>> adj_list_;
};

Planner::Planner(const size_t num_nodes,
                 const std::unordered_set<size_t> &special_nodes,
                 const std::vector<std::pair<size_t, size_t>> &edge_list)
    : num_nodes_(num_nodes + 1), special_nodes_(special_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list) {
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);
  }
}

int Planner::GetMinNumAirports(const size_t source,
                               const size_t destination) const {
  if (source == destination) {
    return 0;
  }

  std::unordered_set<size_t> ancestry;
  auto num_airports = infinity;

  ancestry.insert(source);
  DFS(source, destination, ancestry, num_airports);
  return num_airports == infinity ? -1 : num_airports;
}

void Planner::DFS(const size_t node, const size_t destination,
                  std::unordered_set<size_t> &ancestry,
                  int &num_airports) const {
  if (node == destination) {
    const auto count = std::accumulate(
        ancestry.begin(), ancestry.end(), 0,
        [this](const int so_far, const size_t item) -> int {
          return so_far +
                 (special_nodes_.find(item) == special_nodes_.end() ? 1 : 0);
        });
    num_airports = std::min(num_airports, count);
    return;
  }

  for (const auto &adj_node : adj_list_[node]) {
    if (ancestry.find(adj_node) != ancestry.end()) {
      continue;
    }

    ancestry.insert(adj_node);
    DFS(adj_node, destination, ancestry, num_airports);
    ancestry.erase(adj_node);
  }
}
} // namespace uva_11377

int main(int argc, char *argv[]) {
  size_t x = 0, n = 0, m = 0, k = 0, q = 0, source = 0, destination = 0,
         city = 0;
  std::vector<std::pair<size_t, size_t>> edge_list;

  std::cin >> x;

  for (size_t t = 1; t <= x; ++t) {
    std::cin >> n >> m >> k;
    std::unordered_set<size_t> special_nodes;

    for (size_t i = 0; i < k; ++i) {
      std::cin >> city;
      special_nodes.insert(city);
    }

    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    uva_11377::Planner planner(n, special_nodes, edge_list);

    std::cout << "Case " << t << ':' << std::endl;
    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
      std::cin >> source >> destination;
      std::cout << planner.GetMinNumAirports(source, destination) << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
