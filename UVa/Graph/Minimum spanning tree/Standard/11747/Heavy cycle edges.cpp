#include <algorithm>
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

namespace uva_11747 {
using Edge = std::pair<int, int>;
std::vector<int> GetHeavyWeights(const std::size_t num_nodes,
                                 std::vector<std::pair<Edge, int>> &edge_list) {
  std::sort(edge_list.begin(), edge_list.end(),
            [](const std::pair<Edge, int> &e1, const std::pair<Edge, int> &e2)
                -> bool { return e1.second < e2.second; });

  std::unordered_set<int> selected;
  ds::ufds set(num_nodes);
  for (const auto &edge : edge_list) {
    auto [u, v] = edge.first;
    auto weight = edge.second;
    if (!set.is_same_set(u, v)) {
      selected.insert(weight);
      set.union_set(u, v);
    }
  }

  std::vector<int> heavy_weights;
  heavy_weights.reserve(num_nodes);
  for (const auto &edge : edge_list) {
    auto find_it = selected.find(edge.second);
    if (find_it == selected.end()) {
      heavy_weights.emplace_back(edge.second);
    }
  }
  return heavy_weights;
}
} // namespace uva_11747

int main(int argc, char *argv[]) {
  std::size_t n, m;
  std::vector<std::pair<uva_11747::Edge, int>> edge_list;

  while (std::cin >> n >> m, n || m) {
    edge_list.resize(m);
    for (std::size_t i = 0; i < m; ++i) {
      std::cin >> edge_list[i].first.first >> edge_list[i].first.second >>
          edge_list[i].second;
    }
    auto heavy_weights = uva_11747::GetHeavyWeights(n, edge_list);
    if (heavy_weights.empty()) {
      std::cout << "forest" << std::endl;
    } else {
      auto separator = "";
      for (const auto weight : heavy_weights) {
        std::cout << separator << weight;
        separator = " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
