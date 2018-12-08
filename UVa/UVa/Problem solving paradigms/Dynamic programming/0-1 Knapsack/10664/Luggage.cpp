//
// Created by Gautham on 08-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <ios>

class Distributor {
 public:
  explicit Distributor(const std::vector<int> &suitcases);

  bool Distribute();

 private:
  int Distribute(std::size_t i, int weight_left);

  const std::vector<int> &suitcases_;
  const int weight_;
  std::vector<std::vector<int>> memo_;
};

Distributor::Distributor(const std::vector<int> &suitcases)
    : suitcases_(suitcases), weight_(std::accumulate(suitcases_.begin(), suitcases.end(), 0)) {
  memo_.resize(suitcases.size());

  for (auto &row : memo_) {
    row.resize(static_cast<std::size_t>(weight_) + 1, -1);
  }
}

bool Distributor::Distribute() {
  if (weight_ & 1) {
    return false;
  }
  return Distribute(0, weight_ / 2) == weight_ / 2;
}

int Distributor::Distribute(std::size_t i, int weight_left) {
  if (i >= suitcases_.size()) {
    return 0;
  }

  if (suitcases_[i] > weight_left) {
    return Distribute(i + 1, weight_left);
  }

  auto &memo = memo_[i][weight_left];
  if (memo != -1) {
    return memo;
  }

  auto include = Distribute(i + 1, weight_left - suitcases_[i]) + suitcases_[i];
  auto exclude = Distribute(i + 1, weight_left);
  return memo = std::max(include, exclude);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t t;
  std::string line;
  int weight;
  std::vector<int> suitcases;

  std::cin >> t;
  std::getline(std::cin, line);
  while (t--) {
    suitcases.clear();
    std::getline(std::cin, line);
    std::istringstream tokenizer(line);
    while (tokenizer >> weight) {
      suitcases.emplace_back(weight);
    }

    Distributor distributor(suitcases);
    std::cout << (distributor.Distribute() ? "YES" : "NO") << std::endl;
  }
  return 0;
}