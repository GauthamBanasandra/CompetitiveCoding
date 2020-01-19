// WA

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <ostream>
#include <utility>
#include <vector>

namespace uva_590 {
using Cost = int;

const auto infinity = std::numeric_limits<Cost>::max();

class Scheduler {
public:
  Scheduler(size_t num_cities, size_t max_days,
            const std::vector<std::vector<std::vector<Cost>>> &cost);

  std::pair<bool, Cost> GetMinCost();

private:
  Cost Fly(size_t from_city, size_t day);
  Cost GetCost(const size_t from_city, const size_t to_city,
               const size_t day) const;

  static Cost Add(const Cost a, const Cost b) {
    return a == infinity || b == infinity ? infinity : a + b;
  }

  const size_t num_cities_;
  const size_t max_days_;
  const std::vector<std::vector<std::vector<Cost>>> &cost_;
  std::vector<std::vector<Cost>> memo_;
};

Scheduler::Scheduler(const size_t num_cities, const size_t max_days,
                     const std::vector<std::vector<std::vector<Cost>>> &cost)
    : num_cities_{num_cities}, max_days_{max_days}, cost_{cost} {
  memo_.resize(num_cities_, std::vector<Cost>(max_days_ + 1, -1));
}

std::pair<bool, Cost> Scheduler::GetMinCost() {
  if (max_days_ == 0) {
    return {false, infinity};
  }
  auto cost = Fly(0, 0);
  return {cost != infinity, cost};
}

Cost Scheduler::Fly(const size_t from_city, const size_t day) {
  if (from_city >= num_cities_) {
    assert(false);
  }

  if (day >= max_days_) {
    if (from_city == num_cities_ - 1) {
      return 0;
    }
    return GetCost(from_city, num_cities_ - 1, day);
  }

  auto &memo = memo_[from_city][day];
  if (memo != -1) {
    return memo;
  }

  auto min_cost = infinity;
  for (size_t to_city = 0; to_city < num_cities_; ++to_city) {
    if (from_city == to_city) {
      continue;
    }

    const auto cost = GetCost(from_city, to_city, day + 1);
    if (cost == infinity) {
      continue;
    }
    min_cost = std::min(min_cost, Add(cost, Fly(to_city, day + 1)));
  }
  return memo = min_cost;
}

Cost Scheduler::GetCost(const size_t from_city, const size_t to_city,
                        const size_t day) const {
  assert(day > 0);
  const auto &costs = cost_[from_city][to_city];
  const auto day_idx = (day - 1) % (costs.size() - 1) + 1;
  return cost_[from_city][to_city][day_idx];
}
} // namespace uva_590

int main(int argc, char *argv[]) {
  size_t num_cities;
  size_t max_days;
  size_t num_days;
  size_t scenario_num = 0;
  std::vector<std::vector<std::vector<uva_590::Cost>>> cost;

  while (std::cin >> num_cities >> max_days, num_cities || max_days) {
    cost.resize(num_cities);
    for (size_t i = 0; i < num_cities; ++i) {
      cost[i].resize(num_cities);
      for (size_t j = 0; j < num_cities; ++j) {
        if (i == j) {
          continue;
        }
        std::cin >> num_days;
        cost[i][j].resize(num_days + 1);
        for (size_t k = 1; k <= num_days; ++k) {
          std::cin >> cost[i][j][k];
          cost[i][j][k] =
              cost[i][j][k] == 0 ? uva_590::infinity : cost[i][j][k];
        }
      }
    }

    std::cout << "Scenario #" << ++scenario_num << std::endl;
    auto [is_possible, min_cost] =
        uva_590::Scheduler(num_cities, max_days, cost).GetMinCost();
    if (is_possible) {
      std::cout << "The best flight costs " << min_cost << "." << std::endl;
    } else {
      std::cout << "No flight possible." << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
