//
// Created by gauth on 08-07-2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

struct Interval {
  Interval() : start(0), end(0) {}

  Interval(long start, long end) : start(start), end(end) {}

  bool TryExpand(const Interval &other);

  long start;
  long end;
};

void Print(const std::vector<std::pair<Interval, Interval>> &intervals);

bool Interval::TryExpand(const Interval &other) {
  auto expanded = false;

  if (other.start < start) {
    start = other.start;
    expanded = true;
  }

  if (other.end > end) {
    end = other.end;
    expanded = true;
  }

  return expanded;
}

class MinimalIntervals {
 public:
  MinimalIntervals(const std::vector<Interval> &intervals, long m) : m_(m), intervals_(intervals) {}

  std::vector<Interval> Filter() const;

 private:
  std::vector<std::pair<Interval, Interval>> Filter0M() const;

  long m_;
  std::vector<Interval> intervals_;
};

std::vector<Interval> MinimalIntervals::Filter() const {
  Interval covered;
  std::vector<Interval> minimal_intervals;

  for (const auto &interval : Filter0M()) {
    if (covered.TryExpand(interval.second)) {
      minimal_intervals.emplace_back(interval.first);
    }
  }

  return minimal_intervals;
}

std::vector<std::pair<Interval, Interval>> MinimalIntervals::Filter0M() const {
  std::vector<std::pair<Interval, Interval>> filtered_intervals;

  for (const auto interval : intervals_) {
    assert(interval.start < interval.end);

    if ((interval.end < 0) || (interval.start > m_)) {
      continue;
    }

    filtered_intervals.emplace_back(interval, Interval{interval.start >= 0 ? interval.start : 0,
                                                       interval.end <= m_ ? interval.end : m_});
  }

  return filtered_intervals;
}

int main() {
  long m = 20, start, end;
  long long t;
  std::vector<Interval> intervals{
      {-10, 2},
      {-20, 1},
      {1, 15},
      {2, 32},
  };

  std::cin >> t;
  while (t-- > 0) {
    intervals.clear();

    std::cin >> m;
    while (std::cin >> start >> end, start || end) {
      intervals.emplace_back(start, end);
    }

    intervals = MinimalIntervals(intervals, m).Filter();
    std::cout << intervals.size() << std::endl;
    for (const auto &interval : intervals) {
      std::cout << interval.start << " " << interval.end << std::endl;
    }

    std::cout << std::endl;
  }

  return 0;
}