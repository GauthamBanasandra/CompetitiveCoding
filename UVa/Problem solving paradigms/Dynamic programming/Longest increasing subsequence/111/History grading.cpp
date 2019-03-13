//
// Created by Gautham on 02-11-2018.
//

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cassert>
#include <ios>

class Evaluator {
 public:
  explicit Evaluator(const std::vector<std::size_t> &events);
  std::size_t Evaluate(const std::vector<std::size_t> &events) const;

 private:
  std::vector<std::size_t> OrderEvents(const std::vector<std::size_t> &events) const;

  std::unordered_map<std::size_t, std::size_t> reference_;
};

Evaluator::Evaluator(const std::vector<std::size_t> &events) {
  std::size_t cumulative = 0;
  for (const auto event : OrderEvents(events)) {
    reference_[event] = event + cumulative;
    cumulative += event;
  }
}

std::size_t Evaluator::Evaluate(const std::vector<std::size_t> &events) const {
  std::set<std::size_t> sequence;
  for (auto event : OrderEvents(events)) {
    auto find_it = reference_.find(event);
    if (find_it == reference_.end()) {
      assert(false);
    }

    event = find_it->second;
    auto place_it = sequence.lower_bound(event);
    if (place_it != sequence.end()) {
      sequence.erase(place_it);
    }
    sequence.insert(event);
  }
  return sequence.size();
}

std::vector<std::size_t> Evaluator::OrderEvents(const std::vector<std::size_t> &events) const {
  std::vector<std::size_t> events_ordered(events.size());
  for (std::size_t i = 0, len = events.size(); i < len; ++i) {
    events_ordered[events[i] - 1] = i + 1;
  }
  return events_ordered;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t n;
  std::vector<std::size_t> reference;
  std::vector<std::size_t> events;

  std::cin >> n;

  reference.resize(n);
  for (std::size_t i = 0; i < n; ++i) {
    std::cin >> reference[i];
  }
  Evaluator evaluator(reference);

  events.resize(n);
  while (!std::cin.eof()) {
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> events[i];
      if (std::cin.eof()) {
        return 0;
      }
    }
    std::cout << evaluator.Evaluate(events) << std::endl;
  }

  return 0;
}