#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>

namespace uva_907 {
using Distance = int;
const auto infinity = std::numeric_limits<Distance>::max();

class Scheduler {
public:
  Scheduler(const std::vector<Distance> &distances, size_t days_left);

  Distance GetMinMaxDistance() { return GetMinMaxDistance(0, days_left_); }

private:
  Distance GetMinMaxDistance(size_t i, size_t days_left);
  Distance GetDistance(size_t from, size_t to);

  const std::vector<Distance> &distances_;
  const size_t days_left_;
  std::vector<Distance> distances_cumulative_;
  std::vector<std::vector<Distance>> memo_;
};

Scheduler::Scheduler(const std::vector<Distance> &distances,
                     const size_t days_left)
    : distances_{distances}, days_left_{days_left} {
  const auto len = distances_.size();
  memo_.resize(len, std::vector<Distance>(days_left_ + 1, -1));

  distances_cumulative_.resize(len);
  distances_cumulative_.front() = distances_.front();
  for (size_t i = 1; i < len; ++i) {
    distances_cumulative_[i] = distances_[i] + distances_cumulative_[i - 1];
  }
}

Distance Scheduler::GetMinMaxDistance(const size_t i, const size_t days_left) {
  const auto len = distances_.size();
  assert(i < len);
  if (i == len - 1) {
    return distances_[i];
  }

  // Since we can't camp any further, we'll be walking all the way till the end
  if (days_left == 0) {
    return GetDistance(i, len - 1);
  }

  auto &memo = memo_[i][days_left];
  if (memo != -1) {
    return memo;
  }

  auto min_max_distance = infinity;
  for (auto j = i; j < len - 1; ++j) {
    auto this_camp_distance = GetDistance(i, j);
    auto next_camp_distance = GetMinMaxDistance(j + 1, days_left - 1);
    auto max_distance = std::max(this_camp_distance, next_camp_distance);
    min_max_distance = std::min(min_max_distance, max_distance);
  }
  return memo = min_max_distance;
}

Distance Scheduler::GetDistance(const size_t from, const size_t to) {
  assert(from <= to && to < distances_cumulative_.size());
  auto distance = distances_cumulative_[to];
  if (from > 0) {
    distance -= distances_cumulative_[from - 1];
  }
  return distance;
}
} // namespace uva_907

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_camps;
  size_t days_left;
  std::vector<uva_907::Distance> distances;

  while (std::cin >> num_camps >> days_left, !std::cin.eof()) {
    ++num_camps;
    distances.resize(num_camps);
    for (size_t i = 0; i < num_camps; ++i) {
      std::cin >> distances[i];
    }
    std::cout << uva_907::Scheduler(distances, days_left).GetMinMaxDistance()
              << std::endl;
  }
  return 0;
}
