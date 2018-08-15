//
// Created by Gautham Banasandra on 23/06/18.
//

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

void Print(const std::vector<std::vector<long>> &heights_diagonal);

class Grapevine {
 public:
  explicit Grapevine(const std::vector<std::vector<long>> &heights_diagonal_) : heights_diagonal_(heights_diagonal_) {}

  long GetLargestSide(long l, long u) const;

 private:
  const std::vector<std::vector<long>> &heights_diagonal_;
};

long Grapevine::GetLargestSide(long l, long u) const {
  long largest_side = 0;

  for (const auto &heights_list : heights_diagonal_) {
    auto l_it =
        heights_list[0] >= l ? heights_list.begin() : std::lower_bound(heights_list.begin(), heights_list.end(), l);
    auto u_it =
        heights_list[heights_list.size() - 1] <= u ? heights_list.rbegin() : std::lower_bound(heights_list.rbegin(),
                                                                                              heights_list.rend(),
                                                                                              u,
                                                                                              std::greater<long>());

    largest_side = std::max(largest_side, static_cast<long>(std::distance(l_it, (++u_it).base()) + 1));
  }

  return largest_side;
}

int main() {
  std::ios::sync_with_stdio(false);

  long n, m, q, l, u, h;
  std::vector<std::vector<long>> heights_diagonal;

  while (std::cin >> n >> m, n || m) {
    heights_diagonal.clear();
    heights_diagonal.resize(static_cast<std::size_t >(m + n - 1));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cin >> h;
        heights_diagonal[j < i ? m + i - j - 1 : j - i].emplace_back(h);
      }
    }

    Grapevine grapevine(heights_diagonal);

    std::cin >> q;
    while (q-- > 0) {
      std::cin >> l >> u;
      std::cout << grapevine.GetLargestSide(l, u) << std::endl;
    }

    std::cout << "-" << std::endl;
  }

  return 0;
}