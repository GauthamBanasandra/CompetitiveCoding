#include <algorithm>
#include <cassert>
#include <cmath>
#include <ios>
#include <iostream>
#include <tuple>
#include <vector>

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
  parent_index.resize(size);
  for (std::size_t i = 0; i < size; ++i) {
    parent_index[i] = i;
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
} // namespace ds

namespace uva_1216 {
using ll = long long;
using Point = std::pair<ll, ll>;
using Edge = std::pair<size_t, size_t>;

ll GetECD(const ll k, const std::vector<Point> &points) {
  const auto num_nodes = points.size();
  if (num_nodes == 0) {
    return 0;
  }

  std::vector<std::pair<Edge, ll>> edge_list;
  edge_list.reserve(num_nodes * (num_nodes - 1));

  for (size_t i = 0; i < num_nodes; ++i) {
    for (auto j = i + 1; j < num_nodes; ++j) {
      auto &p1 = points[i];
      auto &p2 = points[j];
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
  std::vector<ll> mst_edges_len;
  mst_edges_len.reserve(num_nodes - 1);
  for (const auto &item : edge_list) {
    auto &[u, v] = item.first;
    auto &cost = item.second;

    if (!set.is_same_set(u, v)) {
      mst_edges_len.emplace_back(cost);
      set.union_set(u, v);
    }
  }

  // Since MST is a tree, each edge that is removed creates a new connected component
  // In order to get k components, we need to remove k-1 edges
  // So, we just remove k-1 largest edges and the last greatest remaining edge is the
  // one with largest ECD

  // Here, we just subtract k to account the 0-1 offset
  const auto index = static_cast<ll>(mst_edges_len.size()) - k;
  assert(index >= 0);
  return std::ceil(std::sqrt(mst_edges_len[index]));
}
} // namespace uva_1216

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  int t;
  uva_1216::ll k, u, v;

  std::cin >> t;
  while (t--) {
    std::cin >> k;
    std::vector<uva_1216::Point> points;

    while (std::cin >> u, u != -1) {
      std::cin >> v;
      points.emplace_back(u, v);
    }
    std::cout << uva_1216::GetECD(k, points) << std::endl;
  }
  return 0;
}
