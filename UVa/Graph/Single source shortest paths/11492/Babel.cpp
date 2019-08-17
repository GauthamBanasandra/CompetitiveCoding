#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace uva_11492 {
const auto infinity = std::numeric_limits<size_t>::max();

class Selector {
public:
  Selector(const std::string &source, const std::string &destination,
           const std::vector<std::tuple<std::string, std::string, std::string>>
               &edge_list);

  size_t GetSequenceLength() const;

private:
  size_t source_{0};
  size_t destination_{0};
  std::unordered_map<std::string, size_t> nodes_;
  std::vector<std::vector<std::tuple<size_t, size_t, char>>> adj_list_;
};

Selector::Selector(
    const std::string &source, const std::string &destination,
    const std::vector<std::tuple<std::string, std::string, std::string>>
        &edge_list) {
  size_t i_node = 0;
  nodes_[source] = i_node++;
  nodes_[destination] = i_node++;

  for (const auto &[u, v, cost] : edge_list) {
    if (nodes_.find(u) == nodes_.end()) {
      nodes_[u] = i_node++;
    }
    if (nodes_.find(v) == nodes_.end()) {
      nodes_[v] = i_node++;
    }
  }

  source_ = nodes_[source];
  destination_ = nodes_[destination];

  auto nodes_len = nodes_.size();
  adj_list_.resize(nodes_len);
  for (const auto &[u, v, name] : edge_list) {
    auto i_u = nodes_[u];
    auto i_v = nodes_[v];

    adj_list_[i_u].emplace_back(i_v, name.size(), name.front());
    adj_list_[i_v].emplace_back(i_u, name.size(), name.front());
  }
}

struct Comparator {
  bool operator()(const std::tuple<size_t, size_t, char> &a,
                  const std::tuple<size_t, size_t, char> &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

size_t Selector::GetSequenceLength() const {
  auto sentinel_char = 'z' + 1;
  // This is how we handle multiple edges
  // Need to have a min for each multi edge
  // Usually, if there are multiple edges, we just don't care
  // because Dijkstra's algorithm will pick the least among them
  // However, since we want to associate a different state for each edge,
  // we need to have a min for each possible way to reach a vertex
  std::vector<std::vector<size_t>> min_cost(nodes_.size(),
                                            std::vector<size_t>(27, infinity));
  std::priority_queue<std::tuple<size_t, size_t, char>,
                      std::vector<std::tuple<size_t, size_t, char>>, Comparator>
      order;

  min_cost[source_][sentinel_char - 'a'] = 0;
  order.emplace(0, source_, sentinel_char);

  while (!order.empty()) {
    const auto [current_cost, node, type] = order.top();
    order.pop();

    if (current_cost > min_cost[node][type - 'a']) {
      continue;
    }

    for (const auto &[adj_node, adj_cost, adj_type] : adj_list_[node]) {
      if (type == adj_type) {
        continue;
      }
      auto cost = min_cost[node][type - 'a'] + adj_cost;
      if (cost < min_cost[adj_node][adj_type - 'a']) {
        min_cost[adj_node][adj_type - 'a'] = cost;
        order.emplace(cost, adj_node, adj_type);
      }
    }
  }
  return *std::min_element(min_cost[destination_].begin(),
                           min_cost[destination_].end());
}
} // namespace uva_11492

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t m;
  std::string source, destination;
  std::vector<std::tuple<std::string, std::string, std::string>> edge_list;

  while (std::cin >> m, m != 0) {
    edge_list.resize(m);
    std::cin >> source >> destination;

    for (size_t i = 0; i < m; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    const auto min_len =
        uva_11492::Selector(source, destination, edge_list).GetSequenceLength();
    if (min_len == uva_11492::infinity) {
      std::cout << "impossivel" << std::endl;
    } else {
      std::cout << min_len << std::endl;
    }
  }
  return 0;
}
