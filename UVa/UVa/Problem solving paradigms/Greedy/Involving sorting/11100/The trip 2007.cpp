//
// Created by gautham on 15/8/18.
//

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <list>
#include <cassert>
#include <string>

using Dimension = std::size_t;
using PackingOrder = std::vector<std::list<Dimension>>;

struct BagFrequency {
  BagFrequency() : dimension(0), frequency(-1) {}
  BagFrequency(Dimension dimension, int frequency) : dimension(dimension), frequency(frequency) {}

  bool operator>(const BagFrequency &other) const {
    return frequency < other.frequency;
  }

  Dimension dimension;
  int frequency;
};

using BagsCollection = std::priority_queue<BagFrequency, std::vector<BagFrequency>, std::greater<BagFrequency>>;

class Packer {
 public:
  explicit Packer(const std::unordered_map<Dimension, int> &bag_frequency);

  PackingOrder Pack();

 private:
  std::size_t Pack(PackingOrder &order, std::size_t i_order, BagFrequency &bag);

  BagsCollection bags_;
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
  // TODO : Use std::transform
  for (auto &kv : bag_frequency) {
    bags_.emplace(kv.first, kv.second);
  }
}

std::size_t Packer::Pack(PackingOrder &order, std::size_t i_order, BagFrequency &bag) {
  assert(i_order < order.size());

  std::size_t i;
  for (i = i_order; i < order.size(); ++i) {
    assert(bag.frequency >= 0);

    if (bag.frequency <= 0) {
      return i;
    }

    order[i].emplace_back(bag.dimension);
    --bag.frequency;
  }

  if (bag.frequency <= 0) {
    return i % order.size();
  }

  for (i = 0; i < i_order; ++i) {
    assert(bag.frequency >= 0);

    if (bag.frequency <= 0) {
      return i;
    }

    order[i].emplace_back(bag.dimension);
    --bag.frequency;
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
  int n;
  Dimension dimension;
  std::unordered_map<Dimension, int> bag_frequency;
  /*for (auto dimension : {17, 16, 7, 8, 20, 2, 11, 10, 8, 11, 3, 11, 10, 6}) {
    ++bag_frequency[dimension];
  }

  Print(Packer(bag_frequency).Pack());*/

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