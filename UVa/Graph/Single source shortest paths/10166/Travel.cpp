// WA

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

const auto infinity = std::numeric_limits<int>::max();
const auto neg_infinity = std::numeric_limits<int>::min();

class Scheduler {
 public:
  Scheduler(const std::vector<std::string> &nodes,
            const std::vector<std::vector<std::pair<int, std::string>>> &paths,
            int start_time, const std::string &journey_begin,
            const std::string &journey_end);

  std::tuple<bool, int, int> FindEarliestArrival() const;

 private:
  int GetFirstDepartureTime(
      const std::vector<size_t> &parent,
      const std::vector<std::pair<int, int>> &min_cost) const;

  const size_t num_nodes_;
  const int start_time_;
  size_t journey_begin_{0};
  size_t journey_end_{0};
  std::vector<std::vector<std::tuple<int, int, size_t>>> adj_list_;
};

Scheduler::Scheduler(
    const std::vector<std::string> &nodes,
    const std::vector<std::vector<std::pair<int, std::string>>> &paths,
    const int start_time, const std::string &journey_begin,
    const std::string &journey_end)
    : num_nodes_(nodes.size()), start_time_(start_time) {
  size_t i_node = 0;
  std::unordered_map<std::string, size_t> node_index;
  for (const auto &node : nodes) {
    node_index[node] = i_node++;
  }

  auto find_it = node_index.find(journey_begin);
  assert(find_it != node_index.end());
  journey_begin_ = find_it->second;

  find_it = node_index.find(journey_end);
  assert(find_it != node_index.end());
  journey_end_ = find_it->second;

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

      adj_list_[u].emplace_back(u_time, v_time, v);
    }
  }

  for (auto &items : adj_list_) {
    std::sort(items.begin(), items.end(),
              [](const std::tuple<int, int, size_t> &p1,
                 const std::tuple<int, int, size_t> &p2) -> bool {
                return std::get<0>(p1) < std::get<0>(p2);
              });
  }
}

struct Comparator {
  bool operator()(const std::tuple<int, int, size_t> &p1,
                  const std::tuple<int, int, size_t> &p2) const {
    if (std::get<1>(p1) == std::get<1>(p2)) {
      return std::get<0>(p1) < std::get<0>(p2);
    }
    return std::get<1>(p1) > std::get<1>(p2);
  }
};

std::tuple<bool, int, int> Scheduler::FindEarliestArrival() const {
  std::vector<std::pair<int, int>> min_cost(num_nodes_,
                                            {neg_infinity, infinity});
  std::vector<size_t> parent(num_nodes_, infinity);
  std::priority_queue<std::tuple<int, int, size_t>,
                      std::vector<std::tuple<int, int, size_t>>, Comparator>
      order;
  order.emplace(neg_infinity, start_time_, journey_begin_);

  while (!order.empty()) {
    const auto[departure, arrival, destination] = order.top();
    order.pop();

    if (arrival > min_cost[destination].second ||
        (arrival == min_cost[destination].second &&
            departure < min_cost[destination].first)) {
      continue;
    }

    const auto least_it = std::upper_bound(
        adj_list_[destination].rbegin(), adj_list_[destination].rend(), arrival,
        [](const int arrival,
           const std::tuple<int, int, size_t> &item) -> bool {
          return std::get<0>(item) > arrival;
        });

    for (auto it = adj_list_[destination].rbegin();
      /*it != least_it*/ it != adj_list_[destination].rend(); ++it) {
      const auto[departure_to_adj, arrival_at_adj, adj_destination] = *it;
      if (departure_to_adj < arrival) {
        continue;
      }

      if (arrival_at_adj < min_cost[adj_destination].second ||
          (arrival_at_adj == min_cost[adj_destination].second &&
              departure_to_adj > min_cost[adj_destination].first)) {
        min_cost[adj_destination] = {departure_to_adj, arrival_at_adj};
        parent[adj_destination] = destination;
        order.emplace(departure_to_adj, arrival_at_adj, adj_destination);
      }
    }
  }
  if (min_cost[journey_end_].second == infinity) {
    return {false, -1, -1};
  }
  return {true, GetFirstDepartureTime(parent, min_cost),
          min_cost[journey_end_].second};
}

int Scheduler::GetFirstDepartureTime(
    const std::vector<size_t> &parent,
    const std::vector<std::pair<int, int>> &min_cost) const {
  auto node = journey_end_;
  while (parent[node] != journey_begin_) {
    node = parent[node];
  }
  return min_cost[node].first;
}

int main(int argc, char *argv[]) {
  size_t c = 0, t = 0, ti = 0;
  auto start_time = 0;
  std::string city, begin, destination;
  std::vector<std::string> cities;
  std::vector<std::vector<std::pair<int, std::string>>> trains;

  while (std::cin >> c, c) {
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
    auto[is_possible, departure, arrival] =
    Scheduler(cities, trains, start_time, begin, destination)
        .FindEarliestArrival();
    if (is_possible) {
      std::cout << std::setfill('0') << std::setw(4) << departure << ' '
                << std::setfill('0') << std::setw(4) << arrival << std::endl;
    } else {
      std::cout << "No connection" << std::endl;
    }
  }
  return 0;
}
