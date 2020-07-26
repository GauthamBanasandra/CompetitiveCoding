// WA

#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace fb_qualification_round_2020 {
using ll = long long;
const auto neg_infinity = std::numeric_limits<ll>::min();

struct Tree {
  ll position{0};
  ll height{0};
};

class IntervalFinder {
public:
  explicit IntervalFinder(std::vector<Tree> &trees);

  ll FindLongestCombined();

private:
  ll Find(size_t tree_idx, ll combined_endpoint);

  std::vector<Tree> &trees_;
  std::unordered_map<size_t, std::unordered_map<ll, ll>> memo_;
};

IntervalFinder::IntervalFinder(std::vector<Tree> &trees) : trees_{trees} {
  std::sort(trees_.begin(), trees_.end(),
            [](const Tree &a, const Tree &b) -> bool {
              return a.position < b.position;
            });
}

ll IntervalFinder::FindLongestCombined() {
  const auto &first_tree = trees_.front();
  const auto len_no_action = Find(1, first_tree.position);
  const auto len_left = Find(1, first_tree.position) + first_tree.height;
  const auto len_right =
      Find(1, first_tree.position + first_tree.height) + first_tree.height;
  return std::max(len_no_action, std::max(len_left, len_right));
}

ll IntervalFinder::Find(const size_t tree_idx, const ll combined_endpoint) {
  if (tree_idx >= trees_.size()) {
    return 0;
  }

  auto tree_idx_it = memo_.find(tree_idx);
  if (tree_idx_it != memo_.end()) {
    const auto endpoint_it = tree_idx_it->second.find(combined_endpoint);
    if (endpoint_it != tree_idx_it->second.end()) {
      return endpoint_it->second;
    }
  }

  const auto &tree = trees_[tree_idx];

  const auto len_no_action = Find(tree_idx + 1, combined_endpoint);

  auto len_left{neg_infinity};
  if (combined_endpoint == tree.position - tree.height) {
    len_left = Find(tree_idx + 1, tree.position) + tree.height;
  }

  auto len_right{neg_infinity};
  if (combined_endpoint == tree.position) {
    len_right = Find(tree_idx + 1, tree.position + tree.height) + tree.height;
  }

  const auto max_len = std::max(len_no_action, std::max(len_left, len_right));
  memo_[tree_idx][combined_endpoint] = max_len;
  return max_len;
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
