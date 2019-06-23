#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <tuple>
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

using ll = long long;
using Point = std::pair<ll, ll>;
using Edge = std::pair<size_t, size_t>;

namespace uva_10147 {
std::vector<std::pair<size_t, size_t>>
GetHighways(const std::vector<Point> &points,
            const std::vector<Edge> &highways_built) {
  const auto num_nodes = points.size();
  assert(num_nodes > 0);

  std::vector<std::pair<Edge, ll>> edge_list;
  edge_list.reserve(num_nodes * (num_nodes - 1));

  for (size_t i = 0; i < num_nodes; ++i) {
    for (auto j = i + 1; j < num_nodes; ++j) {
      const auto &p1 = points[i];
      const auto &p2 = points[j];
      edge_list.emplace_back(
          std::piecewise_construct, std::forward_as_tuple(i, j),
          std::forward_as_tuple((p1.first - p2.first) * (p1.first - p2.first) +
                                (p1.second - p2.second) *
                                    (p1.second - p2.second)));
    }
  }

  std::sort(
      edge_list.begin(), edge_list.end(),
      [](const std::pair<Edge, ll> &e1, const std::pair<Edge, ll> &e2) -> bool {
        return e1.second < e2.second;
      });

  ds::ufds set(num_nodes);
  for (const auto &edge : highways_built) {
    set.union_set(edge.first, edge.second);
  }

  std::vector<Edge> highways_to_build;
  for (const auto &item : edge_list) {
    const auto &[u, v] = item.first;
    if (!set.is_same_set(u, v)) {
      highways_to_build.emplace_back(u + 1, v + 1);
      set.union_set(u, v);
    }
  }
  return highways_to_build;
}
} // namespace uva_10147

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t, c = 0, num_cities, num_highways;
  std::vector<Point> cities;
  std::vector<Edge> highways;

  std::cin >> t;
  while (t--) {
    std::cin >> num_cities;
    cities.resize(num_cities);
    for (size_t i = 0; i < num_cities; ++i) {
      std::cin >> cities[i].first >> cities[i].second;
    }

    std::cin >> num_highways;
    highways.resize(num_highways);
    for (size_t i = 0; i < num_highways; ++i) {
      std::cin >> highways[i].first >> highways[i].second;
      --highways[i].first;
      --highways[i].second;
    }

    if (c++ > 0) {
      std::cout << std::endl;
    }

    auto highways_to_build = uva_10147::GetHighways(cities, highways);
    if (highways_to_build.empty()) {
      std::cout << "No new highways need." << std::endl;
    } else {
      for (const auto &highway : highways_to_build) {
        std::cout << highway.first << ' ' << highway.second << std::endl;
      }
    }
  }
  return 0;
}
