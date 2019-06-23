#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

namespace ds {
class ufds {
public:
  explicit ufds(size_t size);
  size_t find_set(size_t i);
  bool is_same_set(size_t i, size_t j);
  void union_set(size_t i, size_t j);

  size_t size;
  std::vector<size_t> parent_index;
  std::vector<size_t> rank;
};

inline ufds::ufds(const size_t size) : size(size) {
  rank.assign(size, 0);
  parent_index.resize(size);
  for (size_t i = 0; i < size; ++i) {
    parent_index[i] = i;
  }
}

inline size_t ufds::find_set(const size_t i) {
  if (parent_index[i] == i) {
    return i;
  }

  parent_index[i] = find_set(parent_index[i]);
  return parent_index[i];
}

inline bool ufds::is_same_set(const size_t i, const size_t j) {
  return find_set(i) == find_set(j);
}

inline void ufds::union_set(const size_t i, const size_t j) {
  if (!is_same_set(i, j)) {
    const auto parent_i = find_set(i);
    const auto parent_j = find_set(j);
    if (rank[parent_i] > rank[parent_j]) {
      parent_index[parent_j] = parent_i;
    } else {
      parent_index[parent_i] = parent_j;
      if (rank[parent_i] == rank[parent_j]) {
        ++rank[parent_j];
      }
    }
  }
}
} // namespace ds

namespace uva_10099 {
using Edge = std::pair<size_t, size_t>;
const auto infinity = std::numeric_limits<int>::max();

class TouristGuide {
public:
  TouristGuide(size_t num_nodes, std::vector<std::pair<Edge, int>> &edge_list,
               size_t start_node, size_t end_node, int num_tourists);

  int GetMinimumTrips();

private:
  void MinimumCapacity(size_t node, int min_so_far, int &minimum);

  const size_t num_nodes_;
  const size_t start_node_;
  const size_t end_node_;
  const int num_tourists_;
  std::vector<std::pair<Edge, int>> &edge_list_;
  std::vector<std::vector<std::pair<size_t, int>>> adj_list_;
  std::vector<int> visited_;
};

TouristGuide::TouristGuide(const size_t num_nodes,
                           std::vector<std::pair<Edge, int>> &edge_list,
                           const size_t start_node, const size_t end_node,
                           const int num_tourists)
    : num_nodes_(num_nodes), start_node_(start_node), end_node_(end_node),
      num_tourists_(num_tourists), edge_list_(edge_list) {
  std::sort(edge_list_.begin(), edge_list_.end(),
            [](const std::pair<Edge, int> &e1, const std::pair<Edge, int> &e2)
                -> bool { return e1.second > e2.second; });
  adj_list_.resize(num_nodes_);
  visited_.resize(num_nodes_);
}

int TouristGuide::GetMinimumTrips() {
  ds::ufds set(num_nodes_);
  for (const auto &item : edge_list_) {
    auto &[u, v] = item.first;
    const auto capacity = item.second;
    if (!set.is_same_set(u, v)) {
      adj_list_[u].emplace_back(v, capacity);
      adj_list_[v].emplace_back(u, capacity);
      set.union_set(u, v);
    }
  }

  auto minimum = infinity;
  MinimumCapacity(start_node_, infinity, minimum);
  return static_cast<int>(
      std::ceil(static_cast<double>(num_tourists_) / (minimum - 1)));
}

void TouristGuide::MinimumCapacity(const size_t node, const int min_so_far,
                                   int &minimum) {
  if (node == end_node_) {
    minimum = min_so_far;
    return;
  }

  visited_[node] = 1;
  for (const auto &[adj_node, capacity] : adj_list_[node]) {
    if (visited_[adj_node] == 1) {
      continue;
    }
    MinimumCapacity(adj_node, std::min(min_so_far, capacity), minimum);
  }
}
} // namespace uva_10099

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::vector<std::pair<uva_10099::Edge, int>> edge_list;
  size_t start, destination, num_cities, num_roads;
  int num_tourists;
  size_t t = 0;

  while (std::cin >> num_cities >> num_roads, num_cities || num_roads) {
    edge_list.resize(num_roads);
    for (size_t i = 0; i < num_roads; ++i) {
      std::cin >> edge_list[i].first.first >> edge_list[i].first.second >>
          edge_list[i].second;
      --edge_list[i].first.first;
      --edge_list[i].first.second;
    }
    std::cin >> start >> destination >> num_tourists;

    --start;
    --destination;

    std::cout << "Scenario #" << ++t << std::endl;
    std::cout << "Minimum Number of Trips = "
              << uva_10099::TouristGuide(num_cities, edge_list, start,
                                         destination, num_tourists)
                     .GetMinimumTrips()
              << std::endl
              << std::endl;
  }
  return 0;
}
