// WA - Though it passed on UVa OJ, it failed for a couple of cases on uDebug

#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace uva_10801 {
const auto infinity = std::numeric_limits<int>::max();

class Scheduler {
public:
  Scheduler(const std::vector<std::pair<int, std::vector<int>>> &lifts,
            int destination);

  int GetMinDestinationTime() const;

private:
  int source_{-1};
  const int destination_;
  size_t num_lifts_;
  std::vector<std::vector<std::tuple<int, int, int>>> adj_list_;
};

Scheduler::Scheduler(const std::vector<std::pair<int, std::vector<int>>> &lifts,
                     const int destination)
    : destination_(destination), num_lifts_(lifts.size()) {
  adj_list_.resize(100);
  for (auto lift_id = 0, num_lifts = static_cast<int>(lifts.size()),
            min_start = infinity;
       lift_id < num_lifts; ++lift_id) {
    const auto &[time, floors] = lifts[lift_id];
    if (floors.front() == 0 && time < min_start) {
      source_ = lift_id;
      min_start = time;
    }
    if (floors.size() < 2) {
      continue;
    }

    for (size_t i = 0, num_floors = floors.size(); i < num_floors - 1; ++i) {
      adj_list_[floors[i]].emplace_back(
          floors[i + 1], (floors[i + 1] - floors[i]) * time, lift_id);
      adj_list_[floors[i + 1]].emplace_back(
          floors[i], (floors[i + 1] - floors[i]) * time, lift_id);
    }
  }
}

struct Comparator {
  bool operator()(const std::tuple<int, int, int> &a,
                  const std::tuple<int, int, int> &b) const {
    return std::get<0>(a) > std::get<0>(b);
  }
};

int Scheduler::GetMinDestinationTime() const {
  if (source_ == -1) {
    return infinity;
  }

  std::priority_queue<std::tuple<int, int, int>,
                      std::vector<std::tuple<int, int, int>>, Comparator>
      order;
  std::vector<std::vector<int>> min_cost(num_lifts_,
                                         std::vector<int>(100, infinity));

  order.emplace(0, 0, source_);
  min_cost[source_][0] = 0;

  while (!order.empty()) {
    const auto [current_cost, node, type] = order.top();
    order.pop();

    if (current_cost > min_cost[type][node]) {
      continue;
    }

    for (const auto &[adj_node, adj_cost, adj_type] : adj_list_[node]) {
      const auto cost =
          min_cost[type][node] + adj_cost + (type == adj_type ? 0 : 60);
      if (cost < min_cost[adj_type][adj_node]) {
        min_cost[adj_type][adj_node] = cost;
        order.emplace(cost, adj_node, adj_type);
      }
    }
  }
  return (*std::min_element(
      min_cost.begin(), min_cost.end(),
      [this](const std::vector<int> &a, const std::vector<int> &b) -> bool {
        return a[destination_] < b[destination_];
      }))[destination_];
}
} // namespace uva_10801

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string line;
  auto num_lifts = 0, destination = 0;
  std::vector<int> times;
  std::vector<std::pair<int, std::vector<int>>> lifts;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    std::stringstream ld_tokenizer(line);
    ld_tokenizer >> num_lifts >> destination;
    times.resize(num_lifts);
    lifts.resize(num_lifts);

    std::getline(std::cin, line);
    std::stringstream times_tokenizer(line);
    for (auto i = 0, time = 0; times_tokenizer >> time; ++i) {
      times[i] = time;
    }

    for (auto i = 0; i < num_lifts; ++i) {
      std::getline(std::cin, line);
      std::stringstream floor_tokenizer(line);
      std::vector<int> floors;
      for (auto floor = 0; floor_tokenizer >> floor;) {
        floors.emplace_back(floor);
      }
      lifts[i] = std::make_pair(times[i], floors);
    }

    auto min_time =
        uva_10801::Scheduler(lifts, destination).GetMinDestinationTime();
    if (min_time == uva_10801::infinity) {
      std::cout << "IMPOSSIBLE" << std::endl;
    } else {
      std::cout << min_time << std::endl;
    }
  }
  return 0;
}
