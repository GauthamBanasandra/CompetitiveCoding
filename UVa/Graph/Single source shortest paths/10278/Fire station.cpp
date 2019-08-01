// WIP

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using ll = long long;
const auto infinity = std::numeric_limits<ll>::max();

class Selector {
public:
  Selector(size_t num_nodes,
           const std::vector<std::tuple<size_t, size_t, ll>> &edge_list);

  size_t GetNewEasilyReachable(const std::vector<size_t> &sources) const;

private:
  void UpdateMinCost(size_t start_node, std::vector<ll> &min_cost) const;

  const size_t num_nodes_;
  std::vector<std::vector<std::pair<size_t, ll>>> adj_list_;
};

Selector::Selector(const size_t num_nodes,
                   const std::vector<std::tuple<size_t, size_t, ll>> &edge_list)
    : num_nodes_(num_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v, cost] : edge_list) {
    adj_list_[u].emplace_back(v, cost);
    adj_list_[v].emplace_back(u, cost);
  }
}

size_t
Selector::GetNewEasilyReachable(const std::vector<size_t> &sources) const {
  std::vector<ll> min_cost(num_nodes_, infinity);
  for (const auto source_node : sources) {
    UpdateMinCost(source_node, min_cost);
  }
  return std::distance(min_cost.begin(),
                       std::max_element(min_cost.begin() + 1, min_cost.end()));
}

void Selector::UpdateMinCost(size_t start_node,
                             std::vector<ll> &min_cost) const {
  std::priority_queue<std::pair<ll, size_t>, std::vector<std::pair<ll, size_t>>,
                      std::greater<>>
      order;
  order.emplace(0, start_node);
  min_cost[start_node] = 0;

  while (!order.empty()) {
    const auto [current_cost, node] = order.top();
    order.pop();

    if (current_cost > min_cost[node]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost] : adj_list_[node]) {
      const auto cost = min_cost[node] + adj_cost;
      if (cost < min_cost[adj_node]) {
        min_cost[adj_node] = cost;
        order.emplace(cost, adj_node);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  size_t t = 0, num_fire_stations = 0, u = 0, v = 0, num_intersections = 0,
         fire_station = 0, c = 0;
  ll cost = 0;
  std::string line;

  std::getline(std::cin, line);
  std::istringstream t_tokenizer(line);
  t_tokenizer >> t;

  std::getline(std::cin, line);

  while (t--) {
    std::getline(std::cin, line);
    std::istringstream fst_int_tokenizer(line);
    fst_int_tokenizer >> num_fire_stations >> num_intersections;

    std::vector<size_t> fire_stations;
    fire_stations.reserve(num_fire_stations);

    std::getline(std::cin, line);
    std::istringstream fire_stations_tokenizer(line);
    while (fire_stations_tokenizer >> fire_station) {
      fire_stations.emplace_back(fire_station);
    }

    std::vector<std::tuple<size_t, size_t, ll>> edge_list;
    while (std::getline(std::cin, line), !line.empty() && !std::cin.eof()) {
      std::istringstream u_v_cost_tokenizer(line);
      u_v_cost_tokenizer >> u >> v >> cost;
      edge_list.emplace_back(u, v, cost);
    }

    if (c++ > 0) {
      std::cout << std::endl;
    }
    std::cout << Selector(num_intersections + 1, edge_list)
                     .GetNewEasilyReachable(fire_stations)
              << std::endl;
  }
  return 0;
}
