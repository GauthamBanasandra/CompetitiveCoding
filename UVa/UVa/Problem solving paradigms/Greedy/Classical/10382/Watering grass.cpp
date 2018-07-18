//
// Created by gauth on 18-07-2018.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>
#include <sstream>

struct Interval {
  Interval() : start(0), end(0) {}

  Interval(float start, float end) : start(start), end(end) {}

  bool operator<(const Interval &other) {
    return start == other.start ? end > other.end : start < other.start;
  }

  float start;
  float end;
};

struct Sprinkler {
  Sprinkler() : offset(0), radius(0) {}
  Sprinkler(long offset, long radius) : offset(offset), radius(radius) {}

  long offset;
  long radius;
};

class MinimalSprinkler {
 public:
  MinimalSprinkler(long length, long width) : length_(length), width_(width) {}
  long Filter(const std::vector<Sprinkler> &sprinklers) const;

 private:
  std::vector<Interval> Transform(const std::vector<Sprinkler> &sprinklers) const;

  long length_, width_;
};

std::vector<Interval> MinimalSprinkler::Transform(const std::vector<Sprinkler> &sprinklers) const {
  float height_half = width_ / 2.0f;
  std::vector<Interval> intervals;

  for (const Sprinkler &sprinkler:sprinklers) {
    const auto dx = std::sqrt(sprinkler.radius * sprinkler.radius - height_half * height_half);
    intervals.emplace_back(sprinkler.offset - dx, sprinkler.offset + dx);
  }

  return intervals;
}

long MinimalSprinkler::Filter(const std::vector<Sprinkler> &sprinklers) const {
  long minimal = 1;
  auto intervals = Transform(sprinklers);
  assert(!intervals.empty());

  /*for (std::size_t i = 0; i < sprinklers.size(); ++i) {
    printf("(%ld, %ld) -> (%f, %f)\n",
           sprinklers[i].offset,
           sprinklers[i].radius,
           intervals[i].start,
           intervals[i].end);
  }*/

  std::sort(intervals.begin(), intervals.end());

  auto current = intervals[0];
  auto current_len = current.end;

  for (std::size_t i = 0, j = 0; current_len < length_;) {
    current = intervals[i];

    auto i_successor = i;
    for (j = i; j < intervals.size() && intervals[j].start <= current.end; ++j) {
      if (intervals[j].end > current_len) {
        i_successor = j;
        current_len = intervals[j].end;
      }
    }

    if (i_successor == i) {
      break;
    }

    i = i_successor;
    ++minimal;
  }

  return current_len >= length_ ? minimal : -1;
}

int main() {
  std::vector<Sprinkler> sprinklers{
      /*{5, 3},
      {4, 1},
      {1, 2},
      {7, 2},
      {10, 2},
      {13, 3},
      {16, 2},
      {19, 4}*/

      /*{3, 5},
      {9, 3},
      {6, 1}*/

      /*{5, 3},
      {1, 1},
      {9, 1}*/
  };

//  std::cout << MinimalSprinkler(10l, 1l).Filter(sprinklers) << std::endl;

  long n, l, w, offset, r;
  std::string line;
  while (std::getline(std::cin, line), !std::cin.eof()) {
    sprinklers.clear();
    std::istringstream tokenizer(line);
    tokenizer >> n >> l >> w;

//    sprinklers.resize(static_cast<std::size_t>(n));

    while (n-- > 0) {
      std::getline(std::cin, line);
      std::istringstream line_tokenizer(line);
      line_tokenizer >> offset >> r;
      sprinklers.emplace_back(offset, r);
    }

    std::cout << MinimalSprinkler(l, w).Filter(sprinklers) << std::endl;
  }

  return 0;
}