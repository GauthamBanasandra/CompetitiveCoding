// WA, TLE

#include <iostream>
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

namespace JourneyToTheMoon {
using ll = long long;

ll CountChoices(const size_t num_astronauts,
                const std::vector<std::pair<size_t, size_t>> &ids) {
  ds::ufds set(num_astronauts);
  for (const auto &[id1, id2] : ids) {
    set.union_set(id1, id2);
  }

  auto by_country = set.components_size();
  std::vector<size_t> by_country_size;
  by_country_size.reserve(by_country.size());
  for (const auto &item : by_country) {
    by_country_size.emplace_back(item.second);
  }

  ll count = 0;
  const auto len = by_country_size.size();
  if (len == 1) {
    return 1;
  }
  for (size_t i = 0; i < len - 1; ++i) {
    for (auto j = i + 1; j < len; ++j) {
      count += static_cast<ll>(by_country_size[i] * by_country_size[j]);
    }
  }
  return count;
}
} // namespace JourneyToTheMoon

int main(int argc, char *argv[]) {
  size_t num_astronauts, num_ids;
  std::cin >> num_astronauts >> num_ids;

  std::vector<std::pair<size_t, size_t>> ids(num_ids);
  for (size_t i = 0; i < num_ids; ++i) {
    std::cin >> ids[i].first >> ids[i].second;
  }

  std::cout << JourneyToTheMoon::CountChoices(num_astronauts, ids) << std::endl;
  return 0;
}
