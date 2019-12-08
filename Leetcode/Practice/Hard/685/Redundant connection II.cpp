// WA

#include <cassert>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

namespace lc_685 {
class Ufds {
public:
  explicit Ufds(const size_t num_nodes);

  size_t FindSet(size_t i);
  bool IsSameSet(const size_t i, const size_t j) {
    return FindSet(i) == FindSet(j);
  }
  bool UnionSet(size_t i, size_t j);

private:
  std::vector<size_t> parent_;
  std::vector<size_t> rank_;
};

Ufds::Ufds(const size_t num_nodes) {
  rank_.resize(num_nodes);
  parent_.resize(num_nodes);
  std::iota(parent_.begin(), parent_.end(), 0);
}

size_t Ufds::FindSet(const size_t i) {
  if (parent_[i] == i) {
    return i;
  }
  return parent_[i] = FindSet(parent_[i]);
}

bool Ufds::UnionSet(const size_t i, const size_t j) {
  if (IsSameSet(i, j)) {
    return false;
  }

  const auto parent_i = FindSet(i);
  const auto parent_j = FindSet(j);
  if (rank_[parent_i] > rank_[parent_j]) {
    parent_[parent_j] = parent_i;
  } else {
    parent_[parent_i] = parent_j;
    if (rank_[parent_i] == rank_[parent_j]) {
      ++rank_[parent_j];
    }
  }
  return true;
}

std::vector<int>
FindRedundantEdge(const std::vector<std::vector<int>> &edge_list) {
  Ufds ufds(edge_list.size());
  for (const auto &edge : edge_list) {
    if (!ufds.UnionSet(edge.front() - 1, edge.back() - 1)) {
      return edge;
    }
  }
  assert(false);
  return {};
}
} // namespace lc_685

class Solution {
public:
  std::vector<int>
  findRedundantDirectedConnection(std::vector<std::vector<int>> &edges);
};

std::vector<int> Solution::findRedundantDirectedConnection(
    std::vector<std::vector<int>> &edges) {
  return lc_685::FindRedundantEdge(edges);
}

int main(int argc, char *argv[]) {
  std::vector<std::vector<int>> edges{{1, 2}, {1, 3}, {2, 3}};
  auto cycle = Solution().findRedundantDirectedConnection(edges);
  std::cout << cycle.front() << '\t' << cycle.back() << std::endl;
  return 0;
}
