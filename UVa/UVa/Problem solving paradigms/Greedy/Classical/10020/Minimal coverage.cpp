//
// Created by gauth on 08-07-2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <ios>
#include <cassert>

using ll = long long;

struct Interval {
  Interval() : start(0), end(0) {}

  Interval(long start, long end) : start(start), end(end) {}

  bool operator<(const Interval &other) {
    return start == other.start ? end > other.end : start < other.start;
  }

  long start;
  long end;
};

void Print(const std::vector<std::pair<Interval, Interval>> &intervals);

struct MinimalIntervalsInfo {
  MinimalIntervalsInfo(bool is_possible) : is_possible(is_possible) {}
  MinimalIntervalsInfo(bool is_possible, const std::vector<Interval> &intervals)
      : is_possible(is_possible), intervals(intervals) {}

  bool is_possible;
  std::vector<Interval> intervals;
};

class MinimalIntervals {
 public:
  MinimalIntervals(const std::vector<Interval> &intervals, long m) : intervals_(intervals), m_(m) {}

  MinimalIntervalsInfo Filter() const;

 private:
  std::vector<std::pair<Interval, Interval>> Filter0M() const;

  long m_;
  std::vector<Interval> intervals_;
};

MinimalIntervalsInfo MinimalIntervals::Filter() const {
  auto intervals = Filter0M();
  if (intervals.empty()) {
    return MinimalIntervalsInfo{false};
  }

  auto first = intervals[0].second;
  if (first.start != 0) {
    return MinimalIntervalsInfo{false};
  }

  std::vector<Interval> minimal{intervals[0].first};
  auto m = first.end;

  for (std::size_t i = 0, j = 0; m < m_;) {
    // Select an interval
    auto current = intervals[i];

    // Find its successor such that among the ones overlapping
    // with the selected interval, the uncovered distance is maximum
    auto i_successor = i;
    for (j = i; j < intervals.size() && intervals[j].second.start <= current.second.end; ++j) {
      if (intervals[j].second.end > m) {
        i_successor = j;
        m = intervals[j].second.end;
      }
    }

    // Break out if a successor can't be found
    if (i_successor == i) {
      break;
    }

    i = i_successor;
    minimal.emplace_back(intervals[i].first);
  }

  return MinimalIntervalsInfo{m >= m_, minimal};
}

std::vector<std::pair<Interval, Interval>> MinimalIntervals::Filter0M() const {
  std::vector<std::pair<Interval, Interval>> filtered_intervals;

  for (const auto interval : intervals_) {
    if ((interval.end < 0) || (interval.start > m_)) {
      continue;
    }

    filtered_intervals.emplace_back(interval, Interval{interval.start >= 0 ? interval.start : 0,
                                                       interval.end <= m_ ? interval.end : m_});
  }

  std::sort(filtered_intervals.begin(), filtered_intervals.end(),
            [](const std::pair<Interval, Interval> &a, const std::pair<Interval, Interval> &b) -> bool {
              return a.second.start == b.second.start ? a.second.end > b.second.end : a.second.start < b.second.start;
            });
  return filtered_intervals;
}

int main() {
  std::ios::sync_with_stdio(false);

  long m, start, end;
  ll t;
  std::vector<Interval> intervals;

  std::cin >> t;
  for (ll i = 0; i < t; ++i) {
    intervals.clear();

    std::cin >> m;
    while (std::cin >> start >> end, start || end) {
      intervals.emplace_back(start, end);
    }

    if (i > 0) {
      std::cout << std::endl;
    }

    auto info = MinimalIntervals(intervals, m).Filter();
    if (info.is_possible) {
      std::cout << info.intervals.size() << std::endl;
      for (const auto &interval : info.intervals) {
        std::cout << interval.start << " " << interval.end << std::endl;
      }
    } else {
      std::cout << 0 << std::endl;
    }
  }

  return 0;
}