#include <ios>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace edu_round_65 {
namespace ds {
class ufds {
public:
  explicit ufds(std::size_t size);
  std::size_t find_set(std::size_t i);
  bool is_same_set(std::size_t i, std::size_t j);
  void union_set(std::size_t i, std::size_t j);
  std::vector<size_t> GetComponentSizes(const size_t i_until);

  std::size_t size;
  std::vector<std::size_t> parent_index;
  std::vector<std::size_t> rank;
};

ufds::ufds(const std::size_t size) : size(size) {
  rank.assign(size, 0);

  for (std::size_t i = 0; i < size; ++i) {
    parent_index.emplace_back(i);
  }
}

std::size_t ufds::find_set(const std::size_t i) {
  if (parent_index[i] == i) {
    return i;
  }

  parent_index[i] = find_set(parent_index[i]);
  return parent_index[i];
}

bool ufds::is_same_set(const std::size_t i, const std::size_t j) {
  return find_set(i) == find_set(j);
}

void ufds::union_set(const std::size_t i, const std::size_t j) {
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

std::vector<size_t> ufds::GetComponentSizes(const size_t i_until) {
  // We must go with an unordered_map here because the component number returned
  // by find_set(i) might be greater than i_until and thus could cause an index
  // out-of-bound exception
  std::unordered_map<size_t, size_t> component_size(i_until);
  for (size_t i = 0; i < i_until; ++i) {
    ++component_size[find_set(i)];
  }

  std::vector<size_t> node_size(i_until);
  for (size_t i = 0; i < i_until; ++i) {
    node_size[i] = component_size.at(find_set(i));
  }
  return node_size;
}
} // namespace ds

std::vector<size_t>
GetAllMsgReachability(const size_t num_nodes,
                      const std::vector<std::vector<size_t>> &sets) {
  const auto len = sets.size();
  ds::ufds ufds(num_nodes + len);
  for (size_t i = 0; i < len; ++i) {
    const auto u = i + num_nodes;
    for (const auto &node : sets[i]) {
      const auto v = node - 1;
      ufds.union_set(u, v);
    }
  }
  return ufds.GetComponentSizes(num_nodes);
}
} // namespace edu_round_65

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, num_sets, set_len;
  std::vector<std::vector<size_t>> sets;

  std::cin >> num_nodes >> num_sets;
  sets.resize(num_sets);
  for (size_t i = 0; i < num_sets; ++i) {
    std::cin >> set_len;
    sets[i].resize(set_len);
    for (size_t j = 0; j < set_len; ++j) {
      std::cin >> sets[i][j];
    }
  }

  auto separator = "";
  for (const auto &count :
       edu_round_65::GetAllMsgReachability(num_nodes, sets)) {
    std::cout << separator << count;
    separator = " ";
  }
  std::cout << std::endl;
  return 0;
}
