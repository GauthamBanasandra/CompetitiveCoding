//
// Created by Gautham Banasandra on 10/06/18.
//

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

struct ChimpInfo {
  ChimpInfo() : shorter_height(-1), taller_height(-1) {}

  int shorter_height;
  int taller_height;
};

class ChimpBroker {
 public:
  explicit ChimpBroker(std::vector<int> heights);
  ChimpInfo GetChimps(int height);

 private:
  std::vector<int> heights_;
  std::vector<int> heights_neg_;
};

ChimpBroker::ChimpBroker(std::vector<int> heights) : heights_(std::move(heights)) {
  heights_neg_.reserve(heights_.size());
  std::transform(heights_.begin(),
                 heights_.end(),
                 std::back_inserter(heights_neg_),
                 std::bind2nd(std::multiplies<int>(), -1));
}

ChimpInfo ChimpBroker::GetChimps(int height) {
  ChimpInfo info;

  auto find_shorter = std::upper_bound(heights_neg_.rbegin(), heights_neg_.rend(), -height);
  if (find_shorter != heights_neg_.rend()) {
    info.shorter_height = -*find_shorter;
  }

  auto find_taller = std::upper_bound(heights_.begin(), heights_.end(), height);
  if (find_taller != heights_.end()) {
    info.taller_height = *find_taller;
  }

  return info;
}

int main() {
  std::ios::sync_with_stdio(false);

  int n, q, height;
  std::cin >> n;

  std::vector<int> lady_chimps_heights(static_cast<std::size_t >(n));
  for (std::size_t i = 0; i < n; ++i) {
    std::cin >> lady_chimps_heights[i];
  }

  ChimpBroker broker(lady_chimps_heights);

  auto print_height = [](int height, char trail) {
    if (height == -1) {
      std::cout << 'X' << trail;
    } else {
      std::cout << height << trail;
    }
  };

  std::cin >> q;
  for (std::size_t i = 0; i < q; ++i) {
    std::cin >> height;
    auto info = broker.GetChimps(height);
    print_height(info.shorter_height, ' ');
    print_height(info.taller_height, '\n');
  }

  return 0;
}