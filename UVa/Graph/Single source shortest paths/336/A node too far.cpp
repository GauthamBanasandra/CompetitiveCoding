#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

namespace uva_336 {
using Edge = std::pair<int, int>;
const auto infinity = std::numeric_limits<int>::max();

class Network {
public:
  explicit Network(const std::vector<Edge> &edge_list);

  std::size_t CountNodesTooFar(int start_node, int distance) const;

private:
  std::unordered_map<int, int> BFS(int start_node) const;

  std::unordered_map<int, std::vector<int>> adj_list_;
};

Network::Network(const std::vector<Edge> &edge_list) {
  for (auto &[u, v] : edge_list) {
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);
  }
}

std::size_t Network::CountNodesTooFar(const int start_node,
                                      int distance) const {
  auto distances = BFS(start_node);
  return std::count_if(distances.begin(), distances.end(),
                       [&](const std::pair<const int, int> &item) -> bool {
                         return item.second > distance;
                       });
}

std::unordered_map<int, int> Network::BFS(const int start_node) const {
  std::unordered_map<int, int> visited;
  for (const auto &[node, adj_nodes] : adj_list_) {
    visited[node] = infinity;
  }

  std::queue<int> order;
  visited[start_node] = 0;
  order.push(start_node);
  while (!order.empty()) {
    auto node = order.front();
    order.pop();

    const auto find_adj_node_it = adj_list_.find(node);
    if (find_adj_node_it == adj_list_.end()) {
      return visited;
    }

    for (const auto adj_node : find_adj_node_it->second) {
      if (visited[adj_node] == infinity) {
        visited[adj_node] = visited[node] + 1;
        order.push(adj_node);
      }
    }
  }
  return visited;
}
} // namespace uva_336

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::vector<uva_336::Edge> edge_list;
  std::size_t num_edges, t = 0;
  int start_node, ttl;

  while (std::cin >> num_edges, num_edges != 0) {
    edge_list.resize(num_edges);
    for (std::size_t i = 0; i < num_edges; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    uva_336::Network network(edge_list);
    while (std::cin >> start_node >> ttl, start_node || ttl) {
      std::cout << "Case " << ++t << ": "
                << network.CountNodesTooFar(start_node, ttl)
                << " nodes not reachable from node " << start_node
                << " with TTL = " << ttl << '.' << std::endl;
    }
  }
  return 0;
}
