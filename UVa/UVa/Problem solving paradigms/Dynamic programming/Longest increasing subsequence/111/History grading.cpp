//
// Created by Gautham on 02-11-2018.
//

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cassert>

class Evaluator {
 public:
  explicit Evaluator(const std::vector<std::size_t> &events);
  std::size_t Evaluate(const std::vector<std::size_t> &events) const;

 private:
  std::unordered_map<std::size_t, std::size_t> reference_;
};

Evaluator::Evaluator(const std::vector<std::size_t> &events) {
  for (std::size_t i = 0, len = events.size(); i < len; ++i) {
    reference_[events[i]] = events[i] * (20 + i + 1);
  }
}

std::size_t Evaluator::Evaluate(const std::vector<std::size_t> &events) const {
  std::set<std::size_t> sequence;
  for (auto event : events) {
    auto find_it = reference_.find(event);
    if (find_it == reference_.end()) {
      assert(false);
    }

    auto place_it = sequence.lower_bound(event);
    if (place_it != sequence.end()) {
      sequence.erase(place_it);
    }
    sequence.insert(event);
  }
  return sequence.size();
}

int main() {
  std::vector<std::size_t> reference{4, 2, 3, 1};
  std::vector<std::size_t> events{1, 3, 2, 4};
  std::cout << Evaluator(reference).Evaluate(events) << std::endl;
  return 0;
}