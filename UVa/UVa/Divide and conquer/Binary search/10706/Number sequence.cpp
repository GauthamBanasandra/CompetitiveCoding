//
// Created by Gautham Banasandra on 14/06/18.
//

// WIP

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using ll = long long;

class NumberSequence {
 public:
  explicit NumberSequence(ll max_i);

  char GetDigitAt(ll i);

  void PrintStart();

 private:
  ll CountDigits(ll digit);

  std::vector<ll> s_start_i_;
};

NumberSequence::NumberSequence(ll max_i) {
  ll s = 1, d = 1, i = 1;

  s_start_i_.emplace_back(1);
  while (i <= max_i) {
    ++s;
    d += CountDigits(s);
    i += d - 1;
    s_start_i_.emplace_back(i);
  }
}

ll NumberSequence::CountDigits(ll digit) {
  ll num_digits = 0;

  while (digit) {
    ++num_digits;
    digit /= 10;
  }

  return num_digits;
}

void NumberSequence::PrintStart() {
  std::cout << "Size : " << s_start_i_.size() << std::endl;

  for (std::size_t i = 0; i < s_start_i_.size(); ++i) {
    std::cout << (i + 1) << " : " << s_start_i_[i] << std::endl;
  }
}

char NumberSequence::GetDigitAt(ll i) {
  auto find_group = std::upper_bound(s_start_i_.begin(), s_start_i_.end(), i);
  assert(find_group != s_start_i_.end());
  --find_group;
  std::cout << "Group : " << std::distance(s_start_i_.begin(), find_group) + 1 << "\tstarts at : " << *find_group
            << std::endl;

  ll k = *find_group, j;
  std::string sequence;
  for (j = 1; k <= i; ++j) {
    k += CountDigits(j);
    sequence += std::to_string(j);
  }

  std::cout << "Size : " << sequence.length() << std::endl;
  return sequence[k - i - 1];
}

int main() {
  NumberSequence sequence(2147483647);
  sequence.PrintStart();
  std::cout << sequence.GetDigitAt(69) << std::endl;
  return 0;
}