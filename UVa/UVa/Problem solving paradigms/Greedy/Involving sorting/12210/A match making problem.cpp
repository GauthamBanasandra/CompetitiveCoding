//
// Created by gautham on 30/9/18.
//

#include <algorithm>
#include <vector>
#include <iostream>

void Print(const std::vector<int> &elements);

struct MatchInfo {
  MatchInfo() : all_matched(false), num_left(0), min_bachelor(0) {}

  bool all_matched;
  int num_left;
  int min_bachelor;
};

MatchInfo Match(std::vector<int> &bachelors, std::vector<int> &spinsters) {
  std::sort(spinsters.begin(), spinsters.end());
  std::sort(bachelors.begin(), bachelors.end(), std::greater<int>());

  for (auto b_it = bachelors.begin(); b_it != bachelors.end(); ++b_it) {
    if (spinsters.empty()) {
      break;
    }

  }
  return {};
}

int main() {
  std::vector<int> bachelors{
      5,
      5,
      10,
      15
  };

  std::vector<int> spinsters{
      20,
      18
  };

  Match(bachelors, spinsters);
  return 0;
}