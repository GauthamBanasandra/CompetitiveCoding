#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using ll = long long;

class Counter {
public:
  explicit Counter(const std::string &numbers);

  ll Count() { return Count(0); }

private:
  ll Count(size_t i);

  const std::string &numbers_;
  std::vector<ll> memo_;
};

Counter::Counter(const std::string &numbers) : numbers_{numbers} {
  memo_.resize(numbers_.size(), -1);
}

ll Counter::Count(const size_t i) {
  if (i >= numbers_.size()) {
    return 1;
  }

  auto &memo = memo_[i];
  if (memo != -1) {
    return memo;
  }

  const auto letter = numbers_[i] > '0' ? Count(i + 1) : 0;
  ll letters = 0;
  if (i + 1 < numbers_.size() && numbers_[i] > '0') {
    const auto value = std::stoi(numbers_.substr(i, 2));
    letters = value <= 26 ? Count(i + 2) : 0;
  }
  return memo = letter + letters;
}

class Solution {
public:
  int numDecodings(std::string s);
};

int Solution::numDecodings(std::string s) {
  return static_cast<int>(Counter(s).Count());
}

int main(int argc, char *argv[]) {
  std::cout << Counter("0").Count() << std::endl;
  return 0;
}
