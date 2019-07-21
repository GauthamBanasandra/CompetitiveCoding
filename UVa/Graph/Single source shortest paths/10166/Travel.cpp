// WIP

#include <algorithm>
#include <cassert>
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
  bool operator()(const std::pair<int, int> &p1,
                  const std::pair<int, int> &p2) const {
    if (p1.second == p2.second) {
      return p1.first < p2.first;
    }
    return p1.second > p2.second;
  }
};

std::tuple<bool, int, int> Scheduler::FindEarliestArrival() const {
  std::vector<std::pair<int, int>> min_cost(num_nodes_,
                                            {neg_infinity, infinity});
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      Comparator>
      order;
  return {};
}

int main(int argc, char *argv[]) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      Comparator>
      order;
  order.emplace(2, 4);
  order.emplace(1, 5);
  order.emplace(3, 4);
  while (!order.empty()) {
    const auto [u, v] = order.top();
    order.pop();

    std::cout << u << '\t' << v << std::endl;
  }
  return 0;
}
