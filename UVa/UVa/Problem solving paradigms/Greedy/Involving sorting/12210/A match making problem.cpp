//
// Created by gautham on 30/9/18.
//

#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <cassert>

void Print(const std::vector<int> &elements);

using FrequencyTable = std::map<int, int>;

struct MatchInfo {
  MatchInfo() : all_matched(false), num_left(0), min_bachelor(0) {}

  bool all_matched;
  int num_left;
  int min_bachelor;
};

class MatchMaker {
 public:
  explicit MatchMaker(const std::vector<int> &spinsters);
  MatchInfo Match(std::vector<int> &bachelors) const;

 private:
  FrequencyTable spinsters_;
};

MatchMaker::MatchMaker(const std::vector<int> &spinsters) {
  for (auto age : spinsters) {
    ++spinsters_[age];
  }
}

MatchInfo MatchMaker::Match(std::vector<int> &bachelors) const {
  std::sort(bachelors.begin(), bachelors.end(), std::greater<int>());
  auto greater_eq = std::lower_bound(spinsters_.begin(),
                                     spinsters_.end(),
                                     1,
                                     [](const std::pair<const int, int> &a, const int b) -> bool {
                                       return a.first < b;
                                     });
  assert(greater_eq != spinsters_.end());

  std::cout << "Greater or eq : " << greater_eq->first << std::endl;

  auto less_eq = std::lower_bound(spinsters_.rbegin(),
                                  spinsters_.rend(),
                                  21,
                                  [](const std::pair<const int, int> &a, const int b) -> bool {
                                    return a.first > b;
                                  });
  assert(less_eq != spinsters_.rend());

  std::cout << "Less or eq : " << less_eq->first << std::endl;
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

  MatchMaker(spinsters).Match(bachelors);
  return 0;
}