// WIP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>

using Profit = long long;

class Maximizer {
public:
  Maximizer(const std::vector<std::vector<Profit>> &profits, size_t source,
            const std::unordered_set<size_t> &destinations, size_t min_trips,
            size_t num_cities);

private:
  const std::vector<std::vector<Profit>> &profits_;
  const size_t source_;
  const std::unordered_set<size_t> &destinations_;
  const size_t min_trips_;
  std::vector<Profit> max_end_profits_;
  std::vector<std::vector<Profit>> memo_;
};

Maximizer::Maximizer(const std::vector<std::vector<Profit>> &profits,
                     size_t source,
                     const std::unordered_set<size_t> &destinations,
                     size_t min_trips, size_t num_cities)
    : profits_{profits}, source_{source}, destinations_{destinations},
      min_trips_{min_trips} {
  memo_.resize(num_cities, std::vector<Profit>(min_trips_ + 1, -1));
  assert(profits.size() == num_cities);
  max_end_profits_.resize(num_cities, -1);
  for (size_t i = 0; i < num_cities; ++i) {
    for (size_t j = 0; j < num_cities; ++j) {
      if (i == j && destinations.find(j) == destinations.end()) {
        continue;
      }
      max_end_profits_[i] = std::max(max_end_profits_[i], profits_[i][j]);
    }
  }
}

int main(int argc, char *argv[]) { return 0; }
