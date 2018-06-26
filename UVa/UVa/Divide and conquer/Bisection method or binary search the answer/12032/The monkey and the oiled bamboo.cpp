//
// Created by Gautham Banasandra on 26/06/18.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>

using ll = long long;

class Climber {
 public:
  explicit Climber(const std::vector<ll> &rungs_height_);

  ll GetStrength() const;

 private:
  ll Climb(ll k) const;

  const std::vector<ll> &rungs_height_;
  std::vector<ll> height_diff_;
  ll max_diff_;
};

Climber::Climber(const std::vector<ll> &rungs_height_) : rungs_height_(rungs_height_) {
  ll prev_height = 0;
  max_diff_ = 0;
  height_diff_.reserve(rungs_height_.size());

  for (const auto height : rungs_height_) {
    const auto diff = height - prev_height;
    assert(diff > 0);

    height_diff_.emplace_back(diff);
    prev_height = height;

    max_diff_ = std::max(max_diff_, diff);
  }
}

ll Climber::Climb(ll k) const {
  for (const auto height : height_diff_) {
    if (height < k) {
      continue;
    }

    if (height > k) {
      return -1;
    }

    --k;
  }

  return k;
}

ll Climber::GetStrength() const {
  ll l = max_diff_, h = *rungs_height_.rbegin(), k = max_diff_, prev_l, prev_h;

  while (l <= h) {
    prev_l = l;
    prev_h = h;
    k = (l + h) / 2;

    if (Climb(k) == -1) {
      l = k;
    } else {
      h = k;
    }

    // This is so that binary search doesn't get stuck for the input commented out below
    if (prev_l == l && prev_h == h) {
      ++l;
    }
  }

  return k;
}

int main() {
  std::ios::sync_with_stdio(false);

  int t, num_rungs;
  std::vector<ll> heights
  /*{57, 150, 167, 234, 322, 359, 397, 481, 580, 640, 692, 723, 822, 898, 939, 1018, 1076, 1123, 1222, 1290, 1304,
   1327, 1411, 1467, 1556, 1557, 1616, 1623}*/;

//  std::cout << Climber(heights).GetStrength() << std::endl;
  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    std::cin >> num_rungs;
    heights.clear();
    heights.resize(num_rungs);

    for (int j = 0; j < num_rungs; ++j) {
      std::cin >> heights[j];
    }

    std::sort(heights.begin(), heights.end());

    std::cout << "Case " << i << ": " << Climber(heights).GetStrength() << std::endl;
  }

  return 0;
}