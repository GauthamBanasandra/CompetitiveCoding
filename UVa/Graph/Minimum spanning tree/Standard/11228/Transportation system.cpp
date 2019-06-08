// WA

#include <vector>
#include <string>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <cmath>

namespace ds {
class ufds {
 public:
  explicit ufds(std::size_t size);
  std::size_t find_set(std::size_t i);
  bool is_same_set(std::size_t i, std::size_t j);
  void union_set(std::size_t i, std::size_t j);

  std::size_t size;
  std::vector<std::size_t> parent_index;
  std::vector<std::size_t> rank;
};

inline ufds::ufds(const std::size_t size) : size(size) {
  rank.assign(size, 0);

  for (std::size_t i = 0; i < size; ++i) {
    parent_index.emplace_back(i);
  }
}

inline std::size_t ufds::find_set(const std::size_t i) {
  if (parent_index[i] == i) {
    return i;
  }

  parent_index[i] = find_set(parent_index[i]);
  return parent_index[i];
}

inline bool ufds::is_same_set(const std::size_t i, const std::size_t j) {
  return find_set(i) == find_set(j);
}

inline void ufds::union_set(const std::size_t i, const std::size_t j) {
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
}

using Point = std::pair<int, int>;
using Edge = std::pair<std::size_t, std::size_t>;

class TransportationSystem {
 public:
  TransportationSystem(const int city_radius, const std::vector<Point> &nodes)
      : city_radius_(city_radius), nodes_(nodes) {}

  std::tuple<std::size_t, long, long> GetMinimumExtensions() const;

 private:
  std::vector<std::pair<Edge, long>> GetCompleteWeightedGraph() const;
  std::vector<std::pair<Edge, long>> GetMST(
      std::vector<std::pair<Edge, long>> &edge_list) const;
  bool IsSameCity(const long distance) const { return distance <= city_radius_ * city_radius_; }

  const int city_radius_;
  const std::vector<Point> &nodes_;
};

std::vector<std::pair<Edge, long>>
TransportationSystem::GetCompleteWeightedGraph() const {
  assert(!nodes_.empty());

  std::vector<std::pair<Edge, long>> graph;
  const auto len = nodes_.size();
  graph.reserve(len * (len - 1) / 2);

  for (std::size_t i = 0; i < len; ++i) {
    for (auto j = i + 1; j < len; ++j) {
      const auto &n1 = nodes_[i];
      const auto &n2 = nodes_[j];
      const auto distance_sq = (n2.first - n1.first) * (n2.first - n1.first) +
          (n2.second - n1.second) * (n2.second - n1.second);
      graph.emplace_back(std::piecewise_construct,
                         std::forward_as_tuple(i, j), std::forward_as_tuple(distance_sq));
    }
  }
  return graph;
}

std::vector<std::pair<Edge, long>> TransportationSystem::
GetMST(std::vector<std::pair<Edge, long>> &edge_list) const {
  std::vector<std::pair<Edge, long>> mst;
  std::sort(edge_list.begin(), edge_list.end(),
            [](const std::pair<Edge, long> &e1, const std::pair<Edge, long> &e2) -> bool {
              return e1.second < e2.second;
            });

  ds::ufds set(nodes_.size());
  for (const auto &item : edge_list) {
    const auto &edge = item.first;
    if (set.is_same_set(edge.first, edge.second)) {
      continue;
    }

    mst.emplace_back(item);
    set.union_set(edge.first, edge.second);
  }
  return mst;
}

std::tuple<std::size_t, long, long> TransportationSystem::
GetMinimumExtensions() const {
  auto edge_list = GetCompleteWeightedGraph();
  edge_list = GetMST(edge_list);

  std::size_t num_states = 1;
  long road_extension = 0l;
  long railroad_extension = 0l;
  for (const auto &item : edge_list) {
    if (IsSameCity(item.second)) {
      road_extension += std::lround(std::sqrt(item.second));
    } else {
      railroad_extension += std::lround(std::sqrt(item.second));
      ++num_states;
    }
  }
  return {num_states, road_extension, railroad_extension};
}

int main(int argc, char *argv[]) {
  int t;
  std::size_t n;
  std::size_t r;
  int x;
  int y;
  std::vector<Point> nodes;

  std::cin >> t;
  for (int c = 1; c <= t; ++c) {
    std::cin >> n >> r;
    nodes.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> x >> y;
      nodes.emplace_back(x, y);
    }
    const auto&[num_states, road_extension, railroad_extension] = TransportationSystem(r, nodes).GetMinimumExtensions();
    std::cout << "Case #" << c << ": " << num_states << " " << road_extension << " " << railroad_extension << std::endl;
  }
  return 0;
}
