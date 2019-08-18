#include <cassert>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace uva_10166 {
using Time = int;
using Node = size_t;
using EdgeMetadata = std::pair<Time, Time>;
const auto infinity = std::numeric_limits<Time>::max();

struct Comparator {
  bool operator()(const std::pair<EdgeMetadata, Node> &a,
                  const std::pair<EdgeMetadata, Node> &b) const {
    return a.first.second > b.first.second;
  }
};

class Scheduler {
  using EarliestArrivalPriorityQueue =
      std::priority_queue<std::pair<EdgeMetadata, Node>,
                          std::vector<std::pair<EdgeMetadata, Node>>,
                          Comparator>;

public:
  Scheduler(const std::vector<std::string> &nodes,
            const std::vector<std::vector<std::pair<int, std::string>>> &paths,
            int start_time, const std::string &journey_begin,
            const std::string &journey_end);

  std::tuple<bool, Time, Time> GetBestSchedule();

private:
  Time GetEarliestArrival(std::vector<Time> &min_cost,
                          EarliestArrivalPriorityQueue &order);

  const size_t num_nodes_;
  const int arrival_time_at_source_;
  size_t source_{0};
  size_t destination_{0};
  std::vector<std::vector<std::pair<Node, EdgeMetadata>>> adj_list_;
};

Scheduler::Scheduler(
    const std::vector<std::string> &nodes,
    const std::vector<std::vector<std::pair<int, std::string>>> &paths,
    const int start_time, const std::string &journey_begin,
    const std::string &journey_end)
    : num_nodes_(nodes.size()), arrival_time_at_source_(start_time) {
  size_t i_node = 0;
  std::unordered_map<std::string, size_t> node_index;
  for (const auto &node : nodes) {
    node_index[node] = i_node++;
  }

  auto find_it = node_index.find(journey_begin);
  assert(find_it != node_index.end());
  source_ = find_it->second;

  find_it = node_index.find(journey_end);
  assert(find_it != node_index.end());
  destination_ = find_it->second;

  adj_list_.resize(num_nodes_);
  for (const auto &path : paths) {
    const auto len = path.size();
    assert(len >= 2);

    for (size_t i = 0; i < len - 1; ++i) {
      const auto &[u_time, u_name] = path[i];
      find_it = node_index.find(u_name);
      assert(find_it != node_index.end());
      const auto u = find_it->second;

      const auto &[v_time, v_name] = path[i + 1];
      find_it = node_index.find(v_name);
      assert(find_it != node_index.end());
      const auto v = find_it->second;

      adj_list_[u].emplace_back(std::piecewise_construct,
                                std::forward_as_tuple(v),
                                std::forward_as_tuple(u_time, v_time));
    }
  }
}

std::tuple<bool, Time, Time> Scheduler::GetBestSchedule() {
  Time max_departure = 0;
  Time min_arrival = infinity;

  // Just run Dijkstra for separately for each edge emanating from the source
  // node
  // This is the key to solving this problem
  // If we don't do this, Dijkstra won't explore the cases when we start late at
  // the source node, yet arrive at the earliest at the final destination
  for (const auto &[node, edge] : adj_list_[source_]) {
    if (edge.first < arrival_time_at_source_) {
      continue;
    }

    std::vector<Time> min_cost(num_nodes_, infinity);
    EarliestArrivalPriorityQueue order;

    min_cost[source_] = arrival_time_at_source_;
    min_cost[node] = edge.second;
    order.emplace(edge, node);

    // At each node, we try to choose the edge which takes us to the destination
    // at the earliest
    const auto arrival = GetEarliestArrival(min_cost, order);
    if (arrival < min_arrival) {
      min_arrival = arrival;
      max_departure = edge.first;

      // However, if there are multiple trains which arrives at the final
      // destination at the same time, we would rather take the one which starts
      // as late as possible
    } else if (arrival == min_arrival && edge.first > max_departure) {
      max_departure = edge.first;
    }
  }

  if (min_arrival == infinity) {
    return {false, -1, -1};
  }
  return {true, max_departure, min_arrival};
}

Time Scheduler::GetEarliestArrival(std::vector<Time> &min_cost,
                                   EarliestArrivalPriorityQueue &order) {
  while (!order.empty()) {
    auto [edge, node] = order.top();
    order.pop();

    if (edge.second > min_cost[node]) {
      continue;
    }

    for (const auto &[adj_node, adj_edge] : adj_list_[node]) {
      if (adj_edge.first >= edge.second &&
          adj_edge.second < min_cost[adj_node]) {
        min_cost[adj_node] = adj_edge.second;
        order.emplace(adj_edge, adj_node);
      }
    }
  }
  return min_cost[destination_];
}
} // namespace uva_10166

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t c = 0, t = 0, ti = 0, tc = 0;
  auto start_time = 0;
  std::string city, begin, destination;
  std::vector<std::string> cities;
  std::vector<std::vector<std::pair<int, std::string>>> trains;

  while (std::cin >> c, c) {
    ++tc;
    cities.resize(c);
    for (size_t i = 0; i < c; ++i) {
      std::cin >> cities[i];
    }

    std::cin >> t;
    trains.resize(t);
    for (size_t i = 0; i < t; ++i) {
      auto &train = trains[i];
      std::cin >> ti;
      train.resize(ti);

      for (size_t j = 0; j < ti; ++j) {
        std::cin >> train[j].first >> train[j].second;
      }
    }

    std::cin >> start_time >> begin >> destination;
    auto [is_possible, departure, arrival] =
        uva_10166::Scheduler(cities, trains, start_time, begin, destination)
            .GetBestSchedule();
    if (is_possible) {
      std::cout << std::setfill('0') << std::setw(4) << departure << ' '
                << std::setfill('0') << std::setw(4) << arrival << std::endl;
    } else {
      std::cout << "No connection" << std::endl;
    }
  }
  return 0;
}
