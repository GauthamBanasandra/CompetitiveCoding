// WA

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

namespace fb_qualification_round_2020 {
using ll = long long;
const auto unvisited = -1;

struct Tree {
  ll position{0};
  ll height{0};
};

struct Node {
  ll id{0};
  ll value{0};

  Node(const ll id, const ll value) : id{id}, value{value} {}
};

class IntervalFinder {
public:
  explicit IntervalFinder(const std::vector<Tree> &trees);

  ll FindLongestCombined();

private:
  ll Combine(ll node_id);

  const std::vector<Tree> &trees_;
  std::unordered_map<ll, std::vector<Node>> adj_list_;
  std::unordered_map<ll, size_t> in_degree_;
  std::vector<ll> memo_;
  std::vector<int> visited_;
  ll global_id_{0};
};

IntervalFinder::IntervalFinder(const std::vector<Tree> &trees) : trees_{trees} {
  const auto len = trees_.size();
  std::unordered_map<ll, std::vector<std::tuple<Node, Node, ll>>>
      interval_bucket;

  for (ll tree_idx = 0; tree_idx < static_cast<ll>(len); ++tree_idx) {
    const auto &tree = trees[tree_idx];
    auto lx = tree.position - tree.height;
    auto ly = tree.position;
    auto rx = tree.position;
    auto ry = tree.position + tree.height;
    auto lx_id = global_id_++;
    auto ly_id = global_id_++;
    auto rx_id = global_id_++;
    auto ry_id = global_id_++;

    std::tuple<Node, Node, ll> t1({lx_id, lx}, {ly_id, ly}, tree_idx);
    interval_bucket[lx].emplace_back(t1);
    std::tuple<Node, Node, ll> t2({rx_id, rx}, {ry_id, ry}, tree_idx);
    interval_bucket[rx].emplace_back(t2);

    adj_list_[lx_id].emplace_back(ly_id, tree.height);
    adj_list_[ly_id].emplace_back(lx_id, tree.height);
    adj_list_[rx_id].emplace_back(ry_id, tree.height);
    adj_list_[ry_id].emplace_back(rx_id, tree.height);
    ++in_degree_[lx_id];
    ++in_degree_[ly_id];
    ++in_degree_[rx_id];
    ++in_degree_[ry_id];
  }

  for (const auto &[_, bucket] : interval_bucket) {
    for (const auto &[u, v, tree_idx] : bucket) {
      auto find_it = interval_bucket.find(v.value);
      if (find_it == interval_bucket.end()) {
        continue;
      }

      for (const auto &[adj_u, adj_v, adj_tree_idx] : find_it->second) {
        if (tree_idx == adj_tree_idx) {
          continue;
        }

        adj_list_[v.id].emplace_back(adj_u.id, 0L);
        adj_list_[adj_u.id].emplace_back(v.id, 0L);
        ++in_degree_[adj_u.id];
        ++in_degree_[v.id];
      }
    }
  }

  memo_.resize(global_id_, unvisited);
  visited_.resize(global_id_, unvisited);
}

ll IntervalFinder::FindLongestCombined() {
  ll max_value{0};
  for (const auto &[id, in_degree] : in_degree_) {
    assert(id < global_id_);

    if (in_degree == 1 && visited_[id] == unvisited) {
      auto value = Combine(id);
      max_value = std::max(max_value, value);
    }
  }
  return max_value;
}

ll IntervalFinder::Combine(const ll node_id) {
  auto &memo = memo_[node_id];
  if (memo != unvisited) {
    return memo;
  }

  visited_[node_id] = 1;
  ll max_value{0L};
  for (const auto &adj_node : adj_list_[node_id]) {
    if (visited_[adj_node.id] == unvisited) {
      auto value = Combine(adj_node.id) + adj_node.value;
      max_value = std::max(max_value, value);
    }
  }

  return memo = max_value;
}
} // namespace fb_qualification_round_2020

int main(int argc, char *argv[]) {
  size_t t{0};
  size_t num_trees{0};
  std::vector<fb_qualification_round_2020::Tree> trees;

  std::cin >> t;
  for (size_t case_num = 1; case_num <= t; ++case_num) {
    std::cin >> num_trees;
    trees.resize(num_trees);
    for (size_t i = 0; i < num_trees; ++i) {
      std::cin >> trees[i].position >> trees[i].height;
    }

    auto interval_finder = fb_qualification_round_2020::IntervalFinder(trees);
    std::cout << "Case #" << case_num << ": "
              << interval_finder.FindLongestCombined() << std::endl;
  }
  return 0;
}
