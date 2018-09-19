//
// Created by gautham on 15/8/18.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>
#include <list>
#include <cassert>
#include <string>
#include <ios>

using Dimension = std::size_t;
using PackingOrder = std::vector<std::list<Dimension>>;

struct BagFrequency {
  BagFrequency() : dimension(0), frequency(-1) {}
  BagFrequency(Dimension dimension, int frequency) : dimension(dimension), frequency(frequency) {}

  bool operator<(const BagFrequency &other) const {
    return frequency < other.frequency;
  }

  Dimension dimension;
  int frequency;
};

class Packer {
 public:
  explicit Packer(const std::unordered_map<Dimension, int> &bag_frequency);

  PackingOrder Pack();

 private:
  std::size_t Pack(PackingOrder &order, std::size_t i_order, BagFrequency &bag);

  std::priority_queue<BagFrequency> bags_;
};

PackingOrder Packer::Pack() {
  assert(!bags_.empty());

  PackingOrder order(static_cast<std::size_t>(bags_.top().frequency));
  std::size_t i_order = 0;

  while (!bags_.empty()) {
    BagFrequency bag = bags_.top();
    bags_.pop();

    i_order = Pack(order, i_order, bag);
    assert(bag.frequency == 0);
  }

  return order;
}

Packer::Packer(const std::unordered_map<Dimension, int> &bag_frequency) {
  for (auto &kv : bag_frequency) {
    bags_.emplace(kv.first, kv.second);
  }
}

std::size_t Packer::Pack(PackingOrder &order, std::size_t i_order, BagFrequency &bag) {
  assert(i_order < order.size());

  auto handle_bag = [&order, &bag](std::size_t i) -> bool {
    assert(bag.frequency >= 0);

    if (bag.frequency <= 0) {
      return false;
    }

    order[i].emplace_back(bag.dimension);
    --bag.frequency;
    return true;
  };

  std::size_t i;
  for (i = i_order; i < order.size(); ++i) {
    if (!handle_bag(i)) {
      return i;
    }
  }

  if (bag.frequency <= 0) {
    return i % order.size();
  }

  for (i = 0; i < i_order; ++i) {
    if (!handle_bag(i)) {
      return i;
    }
  }

  return i;
}

void Print(const PackingOrder &order) {
  std::string line;

  std::cout << order.size() << std::endl;
  for (auto &bags :order) {
    line.clear();
    for (auto bag : bags) {
      line += std::to_string(bag) + " ";
    }

    line.pop_back();
    std::cout << line << std::endl;
  }
}

int main() {
  std::ios::sync_with_stdio(false);

  int n;
  Dimension dimension;
  std::unordered_map<Dimension, int> bag_frequency;

  auto after_first = false;
  while (std::cin >> n, n) {
    bag_frequency.clear();
    while (n-- > 0) {
      std::cin >> dimension;
      ++bag_frequency[dimension];
    }

    if (after_first) {
      std::cout << std::endl;
    }

    Print(Packer(bag_frequency).Pack());
    after_first = true;
  }

  return 0;
}