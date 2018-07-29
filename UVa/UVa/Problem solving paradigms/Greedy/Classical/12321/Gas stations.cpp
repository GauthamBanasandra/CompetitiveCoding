//
// Created by gautham on 29/7/18.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <ios>

struct Interval {
  Interval() : begin(0), end(0) {}
  Interval(long begin, long end) : begin(begin), end(end) {}

  long begin;
  long end;
};

class MinimalStations {
 public:
  explicit MinimalStations(const std::vector<std::pair<long, long>> &pos);
  int CountRedundant(long road_length);

 private:
  std::vector<Interval> intervals_;
};

MinimalStations::MinimalStations(const std::vector<std::pair<long, long>> &pos) {
  for (const auto p : pos) {
    intervals_.emplace_back(std::max(0l, p.first - p.second), p.first + p.second);
  }

  std::sort(intervals_.begin(), intervals_.end(), [](const Interval &a, const Interval &b) -> bool {
    return a.begin == b.begin ? a.end > b.end : a.begin < b.begin;
  });
}

int MinimalStations::CountRedundant(long road_length) {
  assert(!intervals_.empty());

  if (intervals_[0].begin != 0) {
    return -1;
  }

  auto is_done = [road_length, this](std::size_t i) -> bool {
    return (i < intervals_.size()) && (intervals_[i].end >= road_length);
  };

  auto is_ij_overlap = [this](std::size_t i, std::size_t j) -> bool {
    return (j < intervals_.size()) && (intervals_[j].begin <= intervals_[i].end);
  };

  int num_chosen = 1;
  for (std::size_t i = 0; !is_done(i); ++num_chosen) {
    auto i_successor = i;
    long max_coverage = 0;
    for (auto j = i + 1; is_ij_overlap(i, j); ++j) {
      if (intervals_[j].end > max_coverage) {
        i_successor = j;
        max_coverage = intervals_[j].end;
      }
    }

    if (i_successor == i) {
      if (!is_done(i)) {
        return -1;
      }
      break;
    }

    i = i_successor;
  }

  return static_cast<int>(intervals_.size()) - num_chosen;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::pair<long, long>> pos;
  long road_length = 0;
  int num_stations = 0;

  while (std::cin >> road_length >> num_stations, road_length || num_stations) {
    pos.resize(static_cast<std::size_t>(num_stations));
    for (std::size_t i = 0; i < num_stations; ++i) {
      std::cin >> pos[i].first >> pos[i].second;
    }

    std::cout << MinimalStations(pos).CountRedundant(road_length) << std::endl;
  }

  return 0;
}