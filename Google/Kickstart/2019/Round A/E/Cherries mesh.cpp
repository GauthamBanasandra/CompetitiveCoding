// WA

#include <iostream>
#include <unordered_set>
#include <vector>

using Node = size_t;
using Cost = int;

namespace ds {
class ufds {
public:
  explicit ufds(std::size_t size);
  std::size_t find_set(std::size_t i);
  bool is_same_set(std::size_t i, std::size_t j);
  void union_set(std::size_t i, std::size_t j);
  size_t count_sets_from(Node node);

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

size_t ufds::count_sets_from(const Node node) {
  std::unordered_set<Node> unique_parents;
  for (auto i = node; i < size; ++i) {
    unique_parents.insert(find_set(i));
  }
  return unique_parents.size();
}
} // namespace ds

size_t GetMinSugarLevel(const size_t num_nodes,
                        const std::vector<std::pair<Node, Node>>& edge_list) {
  ds::ufds set(num_nodes + 1);
  size_t total_cost = 0;
  for (const auto &edge : edge_list) {
    const auto u = edge.first;
    const auto v = edge.second;
    if (!set.is_same_set(u, v)) {
      ++total_cost;
      set.union_set(u, v);
    }
  }
  total_cost += (set.count_sets_from(1) - 1) * 2;
  return total_cost;
}

int main(int argc, char *argv[]) {
  size_t t, n, m;
  std::vector<std::pair<Node, Node>> edge_list;

  std::cin >> t;
  for (size_t i = 1; i <= t; ++i) {
    std::cin >> n >> m;
    edge_list.resize(m);
    for (size_t j = 0; j < m; ++j) {
      std::cin >> edge_list[j].first >> edge_list[j].second;
    }

    std::cout << "Case #" << i << ':' << GetMinSugarLevel(n, edge_list)
              << std::endl;
  }
  return 0;
}
