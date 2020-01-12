#include <numeric>
#include <unordered_set>
#include <vector>

namespace lc_1319 {
class Ufds {
public:
  explicit Ufds(size_t num_nodes);

  size_t FindSet(size_t i);
  bool IsSameSet(size_t i, size_t j);
  void UnionSet(size_t i, size_t j);
  size_t GetNumComponents();

private:
  std::vector<size_t> set_;
  std::vector<size_t> rank_;
};

Ufds::Ufds(const size_t num_nodes) {
  set_.resize(num_nodes);
  rank_.resize(num_nodes);
  std::iota(set_.begin(), set_.end(), 0);
}

size_t Ufds::FindSet(const size_t i) {
  if (i == set_[i]) {
    return i;
  }
  return set_[i] = FindSet(set_[i]);
}

bool Ufds::IsSameSet(const size_t i, const size_t j) {
  return FindSet(i) == FindSet(j);
}

void Ufds::UnionSet(const size_t i, const size_t j) {
  if (IsSameSet(i, j)) {
    return;
  }

  const auto parent_i = FindSet(i);
  const auto parent_j = FindSet(j);

  if (rank_[parent_i] > rank_[parent_j]) {
    set_[parent_j] = parent_i;
  } else {
    set_[parent_i] = parent_j;
    if (rank_[parent_i] == rank_[parent_j]) {
      ++rank_[parent_j];
    }
  }
}

size_t Ufds::GetNumComponents() {
  std::unordered_set<size_t> unique;
  for (size_t i = 0; i < set_.size(); ++i) {
    unique.insert(FindSet(i));
  }
  return unique.size();
}
} // namespace lc_1319

class Solution {
public:
  int makeConnected(int n, std::vector<std::vector<int>> &connections);
};

int Solution::makeConnected(const int n,
                            std::vector<std::vector<int>> &connections) {
  lc_1319::Ufds ufds(n);
  size_t redundant_connections = 0;
  for (const auto &connection : connections) {
    if (ufds.IsSameSet(connection.front(), connection.back())) {
      ++redundant_connections;
    } else {
      ufds.UnionSet(connection.front(), connection.back());
    }
  }

  const auto num_components = ufds.GetNumComponents();
  if (num_components == 1) {
    return 0;
  }
  return redundant_connections < num_components - 1
             ? -1
             : static_cast<int>(num_components - 1);
}

int main(int argc, char *argv[]) { return 0; }
