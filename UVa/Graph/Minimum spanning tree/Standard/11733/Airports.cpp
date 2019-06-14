#include <algorithm>
#include <ios>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace ds {
class ufds {
public:
  explicit ufds(std::size_t size);
  std::size_t find_set(std::size_t i);
  bool is_same_set(std::size_t i, std::size_t j);
  void union_set(std::size_t i, std::size_t j);
  std::size_t num_components();

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

std::size_t ufds::num_components() {
  std::unordered_set<std::size_t> unique;
  for (std::size_t i = 0; i < size; ++i) {
    // It is super important to use find_set method here
    // Initially I went wrong by just looping over parent_index and trying to
    // find unique elements That was so totally wrong because UFDS updates the
    // parent indices lazily So, I need to use find_set which forcefully updates
    // the parent indices
    unique.insert(find_set(i));
  }
  return unique.size();
}
} // namespace ds

using Edge = std::pair<std::size_t, std::size_t>;

namespace uva_11733 {
std::pair<std::size_t, std::size_t>
EstimateCost(std::vector<std::pair<Edge, std::size_t>> &edge_list,
             const std::size_t airport_cost, const std::size_t num_locations) {
  std::sort(edge_list.begin(), edge_list.end(),
            [](const std::pair<Edge, std::size_t> &e1,
               const std::pair<Edge, std::size_t> &e2) -> bool {
              return e1.second < e2.second;
            });

  ds::ufds set(num_locations);
  std::size_t total_cost = 0;

  for (const auto &edge : edge_list) {
    const auto &[u, v] = edge.first;
    const auto cost = edge.second;

    if (set.is_same_set(u, v)) {
      continue;
    }

    if (cost < airport_cost) {
      set.union_set(u, v);
      total_cost += cost;
    }
  }

  const auto num_components = set.num_components();
  total_cost += num_components * airport_cost;
  return {total_cost, num_components};
}
} // namespace uva_11733

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  int t;
  std::vector<std::pair<Edge, std::size_t>> edge_list;
  std::size_t airport_cost;
  std::size_t n, m;

  std::cin >> t;
  for (auto i = 1; i <= t; ++i) {
    std::cin >> n >> m >> airport_cost;
    edge_list.resize(m);
    for (std::size_t j = 0; j < m; ++j) {
      std::cin >> edge_list[j].first.first >> edge_list[j].first.second >>
          edge_list[j].second;
      --edge_list[j].first.first;
      --edge_list[j].first.second;
    }

    auto [total_cost, num_airports] =
        uva_11733::EstimateCost(edge_list, airport_cost, n);
    std::cout << "Case #" << i << ": " << total_cost << " " << num_airports
              << std::endl;
  }
  return 0;
}
