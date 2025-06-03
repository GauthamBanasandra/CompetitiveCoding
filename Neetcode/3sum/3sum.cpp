#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums);

private:
  static bool
  decr_or_remove(std::unordered_map<int, std::list<std::size_t>> &freq_table,
                 int element);
};

class UFDS {
public:
  UFDS(std::size_t num_vertices);

  std::size_t FindSet(std::size_t u);
  bool IsSameSet(std::size_t u, std::size_t v);
  void Union(std::size_t u, std::size_t v);
  std::vector<std::vector<int>> GetSets();

private:
  std::vector<std::size_t> parent_;
  std::vector<std::size_t> rank_;
  std::size_t num_vertices_;
};

std::vector<std::vector<int>> Solution::threeSum(std::vector<int> &nums) {
  std::unordered_map<int, std::list<std::size_t>> freq_table;
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    freq_table[*it].emplace_back(std::distance(nums.begin(), it));
  }

  UFDS ufds(nums.size());
  for (auto i_it = nums.begin(); i_it != nums.end(); ++i_it) {
    decr_or_remove(freq_table, *i_it);
    for (auto j_it = i_it + 1; j_it != nums.end(); ++j_it) {
      decr_or_remove(freq_table, *j_it);
      const auto sum_it = freq_table.find(-(*i_it + *j_it));
      if (sum_it != freq_table.end()) {
        const auto i = std::distance(nums.begin(), i_it);
        const auto j = std::distance(nums.begin(), j_it);

        ufds.Union(i, j);
        ufds.Union(i, sum_it->second.front());
        sum_it->second.pop_front();
        if (sum_it->second.empty()) {
          freq_table.erase(sum_it);
        }
      }

      freq_table[*j_it].emplace_back(std::distance(nums.begin(), j_it));
    }

    freq_table[*i_it].emplace_back(std::distance(nums.begin(), i_it));
  }

  return ufds.GetSets();
}

bool Solution::decr_or_remove(
    std::unordered_map<int, std::list<std::size_t>> &freq_table,
    const int element) {
  const auto it = freq_table.find(element);
  if (it == freq_table.end()) {
    return false;
  }

  it->second.pop_back();
  if (it->second.empty()) {
    freq_table.erase(it);
  }

  return true;
}

UFDS::UFDS(std::size_t num_vertices) : num_vertices_(num_vertices) {
  parent_.resize(num_vertices_);
  std::iota(parent_.begin(), parent_.end(), 0);

  rank_.resize(num_vertices_);
}

std::size_t UFDS::FindSet(std::size_t u) {
  if (u >= num_vertices_) {
    throw std::exception("Invalid index");
  }

  if (parent_[u] == u) {
    return u;
  }

  return parent_[u] = FindSet(parent_[u]);
}

bool UFDS::IsSameSet(std::size_t u, std::size_t v) {
  return FindSet(u) == FindSet(v);
}

void UFDS::Union(std::size_t u, std::size_t v) {
  if (IsSameSet(u, v)) {
    return;
  }

  const auto u_root = FindSet(u);
  const auto v_root = FindSet(v);

  if (rank_[u_root] > rank_[v_root]) {
    parent_[v_root] = u_root;
  } else {
    parent_[u_root] = v_root;
    if (rank_[u_root] == rank_[v_root]) {
      ++rank_[v_root];
    }
  }
}

std::vector<std::vector<int>> UFDS::GetSets() {
  std::unordered_map<std::size_t, std::vector<int>> sets;
  std::vector<std::vector<int>> sets_vec;

  for (auto it = parent_.begin(); it != parent_.end(); ++it) {
    sets[*it].emplace_back(
        static_cast<int>(std::distance(parent_.begin(), it)));
  }

  sets_vec.reserve(sets.size());
  for (const auto &[_, set] : sets) {
    sets_vec.emplace_back(set);
  }
  return sets_vec;
}

int main(int argc, char *argv[]) {
  std::vector nums{-1, 0, 1, 2, -1, -4};
  for (const auto &triplet : Solution().threeSum(nums)) {
    for (const auto num : triplet) {
      std::cout << num << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
