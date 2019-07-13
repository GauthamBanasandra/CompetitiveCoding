#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const auto unvisited = -1;

class Graph {
public:
  Graph(size_t num_nodes,
        const std::vector<std::pair<size_t, size_t>> &edge_list);

  std::vector<int> GetDistances(size_t start_node) const;

private:
  const size_t num_nodes_;
  std::vector<std::vector<size_t>> adj_list_;
};

Graph::Graph(const size_t num_nodes,
             const std::vector<std::pair<size_t, size_t>> &edge_list)
    : num_nodes_(num_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list) {
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);
  }
}

std::vector<int> Graph::GetDistances(const size_t start_node) const {
  std::vector<int> distances(num_nodes_, unvisited);
  std::queue<size_t> order;
  order.push(start_node);
  distances[start_node] = 0;

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();
    for (const auto &adj_node : adj_list_[node]) {
      if (distances[adj_node] == unvisited) {
        distances[adj_node] = distances[node] + 1;
        order.push(adj_node);
      }
    }
  }

  for (auto &value : distances) {
    if (value > 0) {
      value *= 6;
    }
  }
  distances.erase(distances.begin());
  distances.erase(std::find(distances.begin(), distances.end(), 0));
  return distances;
}

int main(int argc, char *argv[]) {
  size_t q, n, m, s;
  std::vector<std::pair<size_t, size_t>> edge_list;

  std::cin >> q;
  while (q--) {
    std::cin >> n >> m;
    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    ++n;
    auto separator = "";
    std::cin >> s;
    for (const auto &distance : Graph(n, edge_list).GetDistances(s)) {
      std::cout << separator << distance;
      separator = " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
