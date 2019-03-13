//
// Created by gautham on 8/10/18.
//

#include <vector>
#include <iostream>
#include <ios>

using ll = long long;

struct Range {
  Range() : sum(0), start(0), end(0) {}
  bool IsWider(const Range &other) const { return (sum == other.sum) && ((end - start) > (other.end - other.start)); }

  ll sum;
  std::size_t start;
  std::size_t end;
};

Range GetNicestRoute(const std::vector<int> &scores) {
  Range current, cumulative;

  for (std::size_t i = 0, scores_len = scores.size(); i < scores_len; ++i) {
    current.sum += scores[i];
    ++current.end;

    if ((current.sum > cumulative.sum) || current.IsWider(cumulative)) {
      cumulative = current;
    }

    if (current.sum < 0) {
      current.sum = 0;
      current.start = current.end = i + 1;
    }
  }
  return cumulative;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t b, r;
  std::vector<int> scores{4, -5, 4, -3, 4, 4, -4, 4, -5};

  std::cin >> b;
  for (std::size_t i = 1; i <= b; ++i) {
    std::cin >> r;
    --r;
    scores.resize(r);
    for (std::size_t j = 0; j < r; ++j) {
      std::cin >> scores[j];
    }

    auto range = GetNicestRoute(scores);
    if (range.sum == 0) {
      std::cout << "Route " << i << " has no nice parts" << std::endl;
    } else {
      std::cout << "The nicest part of route " << i << " is between stops " << (range.start + 1) << " and "
                << (range.end + 1) << std::endl;
    }
  }
  return 0;
}