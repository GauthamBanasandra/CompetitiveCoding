//
// Created by Gautham on 21-11-2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using ll = long long;

void Print(const std::vector<std::size_t> &numbers, char separator = ' ');

class Wavio {
 public:
  explicit Wavio(const std::vector<ll> &seq) : seq_(seq) {}
  std::size_t MaxWavioSize() const;

 private:
  std::vector<std::size_t> GetPredecessors(const std::vector<ll> &seq) const;

  const std::vector<ll> &seq_;
};

std::vector<std::size_t> Wavio::GetPredecessors(const std::vector<ll> &seq) const {
  assert(!seq.empty());
  const auto len = seq.size();

  std::vector<std::size_t> m;
  m.reserve(len + 1);
  m.emplace_back(0);

  std::vector<std::size_t> predecessors(len);

  for (std::size_t i = 0; i < len; ++i) {
    auto find_it = std::lower_bound(m.begin() + 1,
                                    m.end(),
                                    seq[i],
                                    [&seq](const std::size_t &i_m, const ll &number) -> bool {
                                      return seq[i_m - 1] < number;
                                    });

    const auto i_m = std::distance(m.begin(), find_it);
    if (find_it == m.end()) {
      m.emplace_back(i + 1);
    } else {
      *find_it = i + 1;
    }
    predecessors[i] = m[i_m - 1];
  }
  return predecessors;
}

std::size_t Wavio::MaxWavioSize() const {
  auto len = seq_.size();
  for (int i = 1; i <= len; ++i) {
    std::cout << i << '\t';
  }
  std::cout << std::endl << std::endl;

  for (const auto &number : seq_) {
    std::cout << number << '\t';
  }
  std::cout << std::endl;

  auto predecessors = GetPredecessors(seq_);
  for (const auto &number : predecessors) {
    std::cout << number << '\t';
  }
  std::cout << std::endl << std::endl << std::endl;

  std::vector<ll> reverse_seq(seq_.rbegin(), seq_.rend());
  for (int i = 1; i <= len; ++i) {
    std::cout << i << '\t';
  }
  std::cout << std::endl << std::endl;

  for (const auto &number : reverse_seq) {
    std::cout << number << '\t';
  }
  std::cout << std::endl;
  auto reverse_predecessors = GetPredecessors(reverse_seq);
  for (const auto &number : reverse_predecessors) {
    std::cout << number << '\t';
  }
  std::cout << std::endl << std::endl << std::endl;


  return 0;
}

int main() {
  std::vector<ll> numbers{1, 2, 3, 2/*, 1, 2, 3, 4, 3, 2, 1, 5, 4, 1, 2, 3, 2, 2, 1*/};
  Wavio(numbers).MaxWavioSize();
  return 0;
}