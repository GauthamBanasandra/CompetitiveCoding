//
// Created by gautham on 30/9/18.
//

#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <cassert>
#include <ios>

void Print(const std::vector<int> &elements);

using FrequencyTable = std::map<int, int>;

struct MatchInfo {
  MatchInfo() : all_matched(false), num_left(0), min_bachelor(0) {}
  MatchInfo(bool all_matched, int num_left, int min_bachelor)
      : all_matched(all_matched), num_left(num_left), min_bachelor(min_bachelor) {}

  bool all_matched;
  int num_left;
  int min_bachelor;
};

class MatchMaker {
 public:
  explicit MatchMaker(const std::vector<int> &spinsters);
  MatchInfo Match(std::list<int> &bachelors);

 private:
  FrequencyTable spinsters_;
  void Choose(std::map<int, int>::iterator &greater_eq_it);
};

MatchMaker::MatchMaker(const std::vector<int> &spinsters) {
  for (auto age : spinsters) {
    ++spinsters_[age];
  }
}

MatchInfo MatchMaker::Match(std::list<int> &bachelors) {
  if (bachelors.size() == spinsters_.size()) {
    return {true, 0, 0};
  }

  bachelors.sort(std::greater<int>());
  for (auto bachelor_it = bachelors.begin(); bachelor_it != bachelors.end();
       bachelor_it = bachelors.erase(bachelor_it)) {
    if (spinsters_.empty()) {
      break;
    }

    auto bachelor = *bachelor_it;
    auto greater_eq_it = std::lower_bound(spinsters_.begin(),
                                          spinsters_.end(),
                                          bachelor,
                                          [](const std::pair<const int, int> &a, const int b) -> bool {
                                            return a.first < b;
                                          });

    auto less_eq_it = std::lower_bound(spinsters_.rbegin(),
                                       spinsters_.rend(),
                                       bachelor,
                                       [](const std::pair<const int, int> &a, const int b) -> bool {
                                         return a.first > b;
                                       });

    assert(less_eq_it != spinsters_.rend() || greater_eq_it != spinsters_.end());

    if (greater_eq_it == spinsters_.end()) {
      auto less_eq_fwd_it = (++less_eq_it).base();
      Choose(less_eq_fwd_it);
    } else if (less_eq_it == spinsters_.rend()) {
      Choose(greater_eq_it);
    } else if (std::abs(greater_eq_it->second - bachelor) < std::abs(less_eq_it->second - bachelor)) {
      Choose(greater_eq_it);
    } else {
      // TODO : Use std::forward here by converting the parameter to a universal reference
      auto less_eq_fwd_it = (++less_eq_it).base();
      Choose(less_eq_fwd_it);
    }
  }

  auto min = 0;
  if (!bachelors.empty()) {
    min = bachelors.back();
  }
  return {bachelors.empty(), static_cast<int>(bachelors.size()), min};
}

void MatchMaker::Choose(std::map<int, int>::iterator &greater_eq_it) {
  --greater_eq_it->second;
  if (greater_eq_it->second == 0) {
    spinsters_.erase(greater_eq_it);
  }
}

int main() {
  std::ios::sync_with_stdio(false);

  int b, b_age;
  std::size_t s;
  std::list<int> bachelors;
  std::vector<int> spinsters;

  for (std::size_t t = 1; std::cin >> b >> s, b || s; ++t) {
    bachelors.clear();
    for (int i = 0; i < b; ++i) {
      std::cin >> b_age;
      bachelors.emplace_back(b_age);
    }

    spinsters.resize(s);
    for (std::size_t i = 0; i < s; ++i) {
      std::cin >> spinsters[i];
    }

    std::cout << "Case " << t << ": ";
    auto info = MatchMaker(spinsters).Match(bachelors);
    if (info.all_matched) {
      std::cout << 0 << std::endl;
    } else {
      std::cout << info.num_left << " " << info.min_bachelor << std::endl;
    }
  }
  return 0;
}