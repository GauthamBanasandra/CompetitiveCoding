#include <algorithm>
#include <cassert>
#include <ios>
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

namespace uva_10462 {
using Edge = std::pair<size_t, size_t>;

class Network {
public:
  enum class Status { kNoWay, kNoSecondWay, kIsPossible };

  Network(const size_t num_nodes, std::vector<std::pair<Edge, int>> &edge_list)
      : num_nodes_(num_nodes), edge_list_(edge_list) {}

  std::pair<Status, int> GetSecondBestCost() const;

private:
  std::pair<bool, int> GetMSTCost() const;

  const size_t num_nodes_;
  std::vector<std::pair<Edge, int>> &edge_list_;
};

std::pair<Network::Status, int> Network::GetSecondBestCost() const {
  assert(num_nodes_ > 0);

  // Just sort only once
  std::sort(edge_list_.begin(), edge_list_.end(),
            [](const std::pair<Edge, int> &e1, const std::pair<Edge, int> &e2)
                -> bool { return e1.second < e2.second; });

  // Collect only indices from edge_list that could form MST
  std::vector<size_t> mst;
  mst.reserve(num_nodes_ - 1);

  ds::ufds set(num_nodes_);
  for (size_t i = 0, len = edge_list_.size(); i < len; ++i) {
    auto &[u, v] = edge_list_[i].first;
    if (!set.is_same_set(u, v)) {
      mst.emplace_back(i);
      set.union_set(u, v);
    }
  }

  if (set.num_components() != 1) {
    return {Status::kNoWay, infinity};
  }

  auto min_cost = infinity;
  for (const auto i : mst) {
    const auto cost = edge_list_[i].second;
    // Set the cost to infinity, thereby indicating that this edge
    // must not be considered
    edge_list_[i].second = infinity;

    // Get the MST cost excluding the edge above
    // We have excluded the least edge that was possible
    // Thus, the MST that will be obtained must be the second best MST
    auto [is_possible, mst_cost] = GetMSTCost();

    // Restore the cost back
    edge_list_[i].second = cost;
    if (!is_possible) {
      continue;
    }
    min_cost = std::min(min_cost, mst_cost);
  }
  return {(min_cost == infinity ? Status::kNoSecondWay : Status::kIsPossible),
          min_cost};
}

std::pair<bool, int> Network::GetMSTCost() const {
  auto min_cost = 0;
  ds::ufds set(num_nodes_);
  for (const auto &item : edge_list_) {
    const auto &[u, v] = item.first;
    const auto cost = item.second;
    if (cost == infinity) {
      continue;
    }

    if (!set.is_same_set(u, v)) {
      min_cost += cost;
      set.union_set(u, v);
    }
  }
  return {set.num_components() == 1, min_cost};
}
} // namespace uva_10462

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t, num_nodes, num_edges;
  std::vector<std::pair<uva_10462::Edge, int>> edge_list;

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
        uva_10462::Network(num_nodes, edge_list).GetSecondBestCost();
    switch (status) {
    case uva_10462::Network::Status::kNoWay:
      std::cout << "No way" << std::endl;
      break;

    case uva_10462::Network::Status::kNoSecondWay:
      std::cout << "No second way" << std::endl;
      break;

    case uva_10462::Network::Status::kIsPossible:
      std::cout << second_best_cost << std::endl;
      break;

    default:
      assert(false);
    }
  }
  return 0;
}
