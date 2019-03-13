//
// Created by gauth on 08-07-2018.
//

#include <iostream>
#include <vector>

struct Interval {
  Interval() : start(0), end(0) {}

  Interval(long start, long end) : start(start), end(end) {}

  bool TryExpand(const Interval &other);

  long start;
  long end;
};

void Print(const std::vector<std::pair<Interval, Interval>> &intervals) {
  for (const auto &interval : intervals) {
    std::cout << "(" << interval.first.start << ", " << interval.first.end << ")\t(" << interval.second.start
              << ", " << interval.second.end << ")" << std::endl;
  }
}