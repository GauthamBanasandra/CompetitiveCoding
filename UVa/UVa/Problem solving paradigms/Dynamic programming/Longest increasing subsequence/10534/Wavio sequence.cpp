//
// Created by Gautham on 21-11-2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <ios>

void Print(const std::vector<std::size_t> &numbers, char separator = ' ');

class Wavio {
 public:
  explicit Wavio(const std::vector<int> &seq) : seq_(seq) {}
  std::size_t MaxWavioSize() const;

 private:
  std::vector<std::size_t> GetPredecessors(const std::vector<int> &seq) const;
  std::vector<std::size_t> GetAintSeqLen(const std::vector<std::size_t> &predecessors) const;
  std::size_t FiintSeqLen(const std::vector<std::size_t> &predecessors,
                          std::size_t i,
                          std::vector<std::size_t> &seq_len) const;

  const std::vector<int> &seq_;
};

std::vector<std::size_t> Wavio::GetPredecessors(const std::vector<int> &seq) const {
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
                                    [&seq](const std::size_t &i_m, const int &number) -> bool {
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
  std::vector<int> rev_seq(seq_.rbegin(), seq_.rend());

  auto predecessors = GetPredecessors(seq_);
  auto rev_predecessors = GetPredecessors(rev_seq);

  auto seq_len = GetAintSeqLen(predecessors);
  auto rev_seq_len = GetAintSeqLen(rev_predecessors);

  std::reverse(rev_seq_len.begin(), rev_seq_len.end());

  std::size_t max = 0;
  for (std::size_t i = 0, len = seq_len.size(); i < len; ++i) {
    max = std::max(max, std::min(seq_len[i], rev_seq_len[i]));
  }
  return 2 * max - 1;
}

std::vector<std::size_t> Wavio::GetAintSeqLen(const std::vector<std::size_t> &predecessors) const {
  auto len = predecessors.size();
  std::vector<std::size_t> seq_len(len);

  for (std::size_t i = 0; i < len; ++i) {
    FiintSeqLen(predecessors, i, seq_len);
  }
  return seq_len;
}

std::size_t Wavio::FiintSeqLen(const std::vector<std::size_t> &predecessors,
                               std::size_t i,
                               std::vector<std::size_t> &seq_len) const {
  if (predecessors[i] == 0) {
    seq_len[i] = 1;
    return 1;
  }

  if (seq_len[i] != 0) {
    return seq_len[i];
  }

  auto len = FiintSeqLen(predecessors, predecessors[i] - 1, seq_len) + 1;
  seq_len[i] = len;
  return len;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t len;
  std::vector<int> numbers{1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 1, 5, 4, 1, 2, 3, 2, 2, 1};

  while (std::cin >> len, !std::cin.eof()) {
    numbers.resize(len);
    for (std::size_t i = 0; i < len; ++i) {
      std::cin >> numbers[i];
    }

    std::cout << Wavio(numbers).MaxWavioSize() << std::endl;
  }
  return 0;
}