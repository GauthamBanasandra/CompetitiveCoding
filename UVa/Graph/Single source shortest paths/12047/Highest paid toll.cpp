// WA

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using Node = size_t;
using Cost = int;
using TotalCost = int;

const auto infinity = std::numeric_limits<Cost>::max();

class Selector {
public:
  Selector(size_t num_nodes,
           const std::vector<std::tuple<Node, Node, Cost>> &edge_list,
           Node source, Node destination, TotalCost capital);

  Cost GetHighestCost() const;

private:
  const size_t num_nodes_;
  const size_t source_;
  const size_t destination_;
  const TotalCost capital_;
  std::vector<std::vector<std::pair<Node, Cost>>> adj_list_;
};

Selector::Selector(const size_t num_nodes,
                   const std::vector<std::tuple<Node, Node, Cost>> &edge_list,
                   const Node source, const Node destination,
                   const TotalCost capital)
    : num_nodes_(num_nodes + 1), source_(source), destination_(destination),
      capital_(-capital) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list) {
    adj_list_[u].emplace_back(v, -cost);
  }
}

struct Comparator {
  bool operator()(const std::tuple<Cost, Node, TotalCost> &a,
                  const std::tuple<Cost, Node, TotalCost> &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

Cost Selector::GetHighestCost() const {
  std::vector<Cost> max_cost(num_nodes_, infinity);
  std::priority_queue<std::tuple<Cost, Node, TotalCost>,
                      std::vector<std::tuple<Cost, Node, TotalCost>>,
                      Comparator>
      order;

  max_cost[source_] = 0;
  order.emplace(0, source_, 0);

  while (!order.empty()) {
    auto [current_max_cost, node, current_cost] = order.top();
    order.pop();

    if (current_max_cost > max_cost[node]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost] : adj_list_[node]) {
      auto cost = max_cost[node] + adj_cost;
      if (cost < capital_) {
        continue;
      }
      max_cost[adj_node] =
          std::min(max_cost[adj_node], std::min(current_max_cost, adj_cost));
      order.emplace(max_cost[adj_node], adj_node, cost);
    }
  }
  return max_cost[destination_] == infinity ? -1 : -max_cost[destination_];
}

int main(int argc, char *argv[]) {
  size_t tc, n, m;
  Node s, t;
  TotalCost p;
  std::vector<std::tuple<Node, Node, Cost>> edge_list;

  std::cin >> tc;
  while (tc--) {
    std::cin >> n >> m >> s >> t >> p;
    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> std::get<0>(edge_list[i]) >> std::get<1>(edge_list[i]) >>
          std::get<2>(edge_list[i]);
    }

    std::cout << Selector(n, edge_list, s, t, p).GetHighestCost() << std::endl;
  }
  return 0;
}
