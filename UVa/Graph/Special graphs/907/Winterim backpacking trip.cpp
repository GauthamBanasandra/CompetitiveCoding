// WA

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

namespace uva_907 {
using Distance = int;

class Scheduler {
public:
  Scheduler(const std::vector<Distance> &camps, size_t days_left);

  Distance GetMinDistance() { return GetMinDistance(0, days_left_); }

private:
  Distance GetMinDistance(size_t i, size_t days_left);

  const std::vector<Distance> &camps_;
  const size_t days_left_;
  std::vector<std::vector<Distance>> memo_;
};

Scheduler::Scheduler(const std::vector<Distance> &camps, const size_t days_left)
    : camps_{camps}, days_left_{days_left} {
  memo_.resize(camps_.size(), std::vector<Distance>(days_left_ + 1, -1));
}

Distance Scheduler::GetMinDistance(const size_t i, const size_t days_left) {
  if (i >= camps_.size() - 1) {
    return camps_[i];
  }

  auto &memo = memo_[i][days_left];
  if (memo != -1) {
    return memo;
  }

  if (days_left == 0) {
    return memo = GetMinDistance(i + 1, days_left) + camps_[i];
  }
  auto camp = GetMinDistance(i + 1, days_left - 1);
  auto no_camp = GetMinDistance(i + 1, days_left) + camps_[i];
  return memo = std::min(std::max(camp, camps_[i]), no_camp);
}
} // namespace uva_907

int main(int argc, char *argv[]) {
  size_t num_camps;
  size_t days_left;
  std::vector<uva_907::Distance> camps;

  while (std::cin >> num_camps >> days_left, !std::cin.eof()) {
    ++num_camps;
    camps.resize(num_camps);
    for (size_t i = 0; i < num_camps; ++i) {
      std::cin >> camps[i];
    }
    std::cout << uva_907::Scheduler(camps, days_left).GetMinDistance()
              << std::endl;
  }
  return 0;
}
