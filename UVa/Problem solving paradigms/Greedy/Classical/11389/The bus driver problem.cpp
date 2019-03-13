//
// Created by gauth on 20-07-2018.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <ios>

class RouteAssigner {
 public:
  RouteAssigner(int num_routes_, int max_distance_, int rate_)
      : num_routes_(num_routes_), max_distance_(max_distance_), rate_(rate_) {}

  long GetOvertimeCost(std::vector<int> &morning, std::vector<int> &afternoon) const;

 private:
  int num_routes_;
  int max_distance_;
  int rate_;
};

long RouteAssigner::GetOvertimeCost(std::vector<int> &morning, std::vector<int> &afternoon) const {
  assert(morning.size() == afternoon.size());

  std::sort(morning.begin(), morning.end());
  std::sort(afternoon.begin(), afternoon.end(), std::greater<int>());

  long cost = 0;
  for (std::size_t i = 0; i < morning.size(); ++i) {
    auto distance = morning[i] + afternoon[i];
    cost = distance > max_distance_ ? (cost + (distance - max_distance_) * rate_) : cost;
  }

  return cost;
}

int main() {
  std::ios::sync_with_stdio(false);

  int n, d, r;
  std::vector<int> morning;
  std::vector<int> afternoon;

  while (std::cin >> n >> d >> r, n || d || r) {
    assert(n && d && r);

    morning.resize(static_cast<std::size_t>(n));
    afternoon.resize(static_cast<std::size_t>(n));

    for (int i = 0; i < n; ++i) {
      std::cin >> morning[i];
    }

    for (int i = 0; i < n; ++i) {
      std::cin >> afternoon[i];
    }

    std::cout << RouteAssigner(n, d, r).GetOvertimeCost(morning, afternoon) << std::endl;
  }

  return 0;
}