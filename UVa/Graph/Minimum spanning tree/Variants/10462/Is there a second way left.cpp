// WA

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const auto infinity = std::numeric_limits<int>::max();

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

using Edge = std::pair<size_t, size_t>;

class Network {
public:
  enum class Status { kNoWay, kNoSecondWay, kIsPossible };

  Network(const size_t num_nodes, std::vector<std::pair<Edge, int>> &edge_list)
      : num_nodes_(num_nodes), edge_list_(edge_list) {}

  std::pair<Status, int> GetSecondBestCost();

private:
  std::pair<bool, int> GetMSTCost() const;

  const size_t num_nodes_;
  std::vector<std::pair<Edge, int>> &edge_list_;
};

std::pair<Network::Status, int> Network::GetSecondBestCost() {
  assert(num_nodes_ > 0);

  std::sort(edge_list_.begin(), edge_list_.end(),
            [](const std::pair<Edge, int> &e1, const std::pair<Edge, int> &e2)
                -> bool { return e1.second < e2.second; });

  std::vector<Edge> mst;
  mst.reserve(num_nodes_ - 1);

  ds::ufds set(num_nodes_);
  for (const auto &item : edge_list_) {
    const auto &[u, v] = item.first;
    if (!set.is_same_set(u, v)) {
      mst.emplace_back(u, v);
      set.union_set(u, v);
    }
  }

  if (set.num_components() != 1) {
    return {Status::kNoWay, infinity};
  }

  const auto remove_edge = [this](const size_t u,
                                  const size_t v) -> std::pair<size_t, int> {
    const auto len = edge_list_.size();
    for (size_t i = 0; i < len; ++i) {
      auto &[edge, cost] = edge_list_[i];
      const auto temp_cost = cost;
      if (edge.first == u && edge.second == v) {
        cost = infinity;
      }
      return {i, temp_cost};
    }
    return {len, infinity};
  };

  auto min_cost = infinity;
  for (const auto &[u, v] : mst) {
    const auto &[removed_idx, cost] = remove_edge(u, v);
    assert(removed_idx != edge_list_.size());

    auto [is_possible, mst_cost] = GetMSTCost();
    edge_list_[removed_idx].second = cost;
    if (!is_possible) {
      continue;
    }

    min_cost = std::min(min_cost, mst_cost);
  }
  return {(min_cost == infinity ? Status::kNoSecondWay : Status::kIsPossible),
          min_cost};
}

std::pair<bool, int> Network::GetMSTCost() const {
  std::sort(edge_list_.begin(), edge_list_.end(),
            [](const std::pair<Edge, int> &e1, const std::pair<Edge, int> &e2)
                -> bool { return e1.second < e2.second; });

  auto min_cost = 0;
  ds::ufds set(num_nodes_);
  for (const auto &item : edge_list_) {
    const auto &[u, v] = item.first;
    const auto cost = item.second;
    if (!set.is_same_set(u, v)) {
      min_cost += cost;
      set.union_set(u, v);
    }
  }
  return {set.num_components() == 1, min_cost};
}

int main(int argc, char *argv[]) {
  size_t t, num_nodes, num_edges;
  std::vector<std::pair<Edge, int>> edge_list;

  std::cin >> t;
  for (size_t i = 1; i <= t; ++i) {
    std::cin >> num_nodes >> num_edges;
    edge_list.resize(num_edges);
    for (size_t j = 0; j < num_edges; ++j) {
      std::cin >> edge_list[j].first.first >> edge_list[j].first.second >>
          edge_list[j].second;
      --edge_list[j].first.first;
      --edge_list[j].first.second;
    }

    std::cout << "Case #" << i << " : ";
    auto [status, second_best_cost] =
        Network(num_nodes, edge_list).GetSecondBestCost();
    switch (status) {
    case Network::Status::kNoWay:
      std::cout << "No way" << std::endl;
      break;
    case Network::Status::kNoSecondWay:
      std::cout << "No second way" << std::endl;
      break;
    case Network::Status::kIsPossible:
      std::cout << second_best_cost << std::endl;
      break;
    default:
      assert(false);
    }
  }
  return 0;
}
