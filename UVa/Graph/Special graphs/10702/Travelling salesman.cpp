#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <ostream>
#include <unordered_set>
#include <vector>

namespace uva_10702 {
using Profit = long long;

class Maximizer {
public:
  Maximizer(const std::vector<std::vector<Profit>> &profits, size_t source,
            const std::unordered_set<size_t> &destinations, size_t min_trips,
            size_t num_cities);
  Profit GetMaxProfit();

private:
  Profit GetMaxProfit(size_t city, size_t travel_rem);

  const std::vector<std::vector<Profit>> &profits_;
  const size_t source_;
  const size_t min_trips_;
  const size_t num_cities_;
  std::vector<Profit> max_end_profits_;
  std::vector<std::vector<Profit>> memo_;
};

Maximizer::Maximizer(const std::vector<std::vector<Profit>> &profits,
                     const size_t source,
                     const std::unordered_set<size_t> &destinations,
                     const size_t min_trips, const size_t num_cities)
    : profits_{profits}, source_{source}, min_trips_{min_trips},
      num_cities_{num_cities} {
  memo_.resize(num_cities_, std::vector<Profit>(min_trips_ + 1, -1));
  assert(profits.size() == num_cities_);
  max_end_profits_.resize(num_cities_, -1);
  for (size_t i = 0; i < num_cities_; ++i) {
    for (size_t j = 0; j < num_cities_; ++j) {
      if (i == j || destinations.find(j) == destinations.end()) {
        continue;
      }
      max_end_profits_[i] = std::max(max_end_profits_[i], profits_[i][j]);
    }
  }
}

Profit Maximizer::GetMaxProfit() {
  if (min_trips_ == 0) {
    return 0;
  }
  const auto profit = GetMaxProfit(source_, min_trips_);
  return profit == -1 ? 0 : profit;
}

Profit Maximizer::GetMaxProfit(const size_t city, const size_t travel_rem) {
  assert(city < num_cities_);
  if (travel_rem == 1) {
    // Return to the destination city that provides maximum profit
    // Could return -1 if no destination city is available (See how
    // max_end_profits_is initialized)
    return max_end_profits_[city];
  }
  auto &memo = memo_[city][travel_rem];
  if (memo != -1) {
    return memo;
  }
  Profit max_profit = -1;
  for (size_t i = 0; i < num_cities_; ++i) {
    if (i == city) {
      continue;
    }
    const auto profit = GetMaxProfit(i, travel_rem - 1);
    if (profit != -1) {
      max_profit = std::max(max_profit, profit + profits_[city][i]);
    }
  }
  return memo = max_profit;
}
} // namespace uva_10702

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_cities;
  size_t source;
  size_t destination;
  size_t num_destinations;
  size_t min_trips;
  std::vector<std::vector<uva_10702::Profit>> profits;

  while (std::cin >> num_cities >> source >> num_destinations >> min_trips,
         num_cities || source || num_destinations || min_trips) {
    profits.resize(num_cities);
    for (size_t i = 0; i < num_cities; ++i) {
      profits[i].resize(num_cities);
      for (size_t j = 0; j < num_cities; ++j) {
        std::cin >> profits[i][j];
      }
    }

    std::unordered_set<size_t> destinations;
    for (size_t i = 0; i < num_destinations; ++i) {
      std::cin >> destination;
      destinations.insert(--destination);
    }
    --source;
    std::cout << uva_10702::Maximizer(profits, source, destinations, min_trips,
                                      num_cities)
                     .GetMaxProfit()
              << std::endl;
  }
  return 0;
}
