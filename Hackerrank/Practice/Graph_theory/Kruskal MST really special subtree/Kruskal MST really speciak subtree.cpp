#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>
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
  std::unordered_map<size_t, size_t> components_size();

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

std::unordered_map<size_t, size_t> ufds::components_size() {
  std::unordered_map<size_t, size_t> size;
  for (size_t i = 0; i < this->size; ++i) {
    ++size[find_set(i)];
  }
  return size;
}
} // namespace ds

using ll = long long;
using Edge = std::tuple<size_t, size_t, int>;

ll GetMSTWeight(const size_t num_nodes, std::vector<Edge> &edge_list) {
  std::sort(edge_list.begin(), edge_list.end(),
            [](const Edge e1, const Edge &e2) -> bool {
              const auto &[u1, v1, w1] = e1;
              const auto &[u2, v2, w2] = e2;
              if (w1 == w2) {
                return u1 + v1 + w1 < u2 + v2 + w2;
              }
              return w1 < w2;
            });

  ll mst_weight = 0;
  ds::ufds set(num_nodes);
  for (const auto &[u, v, weight] : edge_list) {
    if (!set.is_same_set(u, v)) {
      mst_weight += weight;
      set.union_set(u, v);
    }
  }
  return mst_weight;
}

int main(int argc, char *argv[]) {
  size_t num_nodes = 0, num_edges = 0, u = 0, v = 0;
  int weight;
  std::vector<std::tuple<size_t, size_t, int>> edge_list;

  std::cin >> num_nodes >> num_edges;
  edge_list.reserve(num_edges);
  for (size_t i = 0; i < num_edges; ++i) {
    std::cin >> u >> v >> weight;
    edge_list.emplace_back(u, v, weight);
  }
  ++num_nodes;
  std::cout << GetMSTWeight(num_nodes, edge_list) << std::endl;
  return 0;
}
