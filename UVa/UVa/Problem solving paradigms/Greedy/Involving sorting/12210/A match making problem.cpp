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
  MatchInfo Match(std::vector<int> &bachelors);

 private:
  FrequencyTable spinsters_;
  void Choose(std::map<int, int>::iterator &greater_eq_it);
};

MatchMaker::MatchMaker(const std::vector<int> &spinsters) {
  for (auto age : spinsters) {
    ++spinsters_[age];
  }
}

MatchInfo MatchMaker::Match(std::vector<int> &bachelors) {
  std::sort(bachelors.begin(), bachelors.end(), std::greater<int>());
  for (auto bachelor : bachelors) {
    if (spinsters_.empty()) {
      break;
    }

    auto greater_eq_it = std::lower_bound(spinsters_.begin(),
                                          spinsters_.end(),
                                          bachelor,
                                          [](const std::pair<const int, int> &a, const int b) -> bool {
                                            return a.first < b;
                                          });

    auto less_eq_it = std::lower_bound(spinsters_.rbegin(),
                                       spinsters_.rend(),
                                       19,
                                       [](const std::pair<const int, int> &a, const int b) -> bool {
                                         return a.first > b;
                                       });

    if (greater_eq_it == spinsters_.end()) {
      assert(less_eq_it != spinsters_.rend());

      Choose((++less_eq_it).base());
    }

    if (less_eq_it == spinsters_.rend()) {
      assert(greater_eq_it != spinsters_.end());

      Choose(greater_eq_it);
    }

  }

  return {};
}

void MatchMaker::Choose(std::map<int, int>::iterator &greater_eq_it) {
  --greater_eq_it->second;
  if (greater_eq_it->second == 0) {
    spinsters_.erase(greater_eq_it);
  }
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