// This solution threw a stack overflow error for input 9999 10000 on Windows.
// However, it got AC on Codeforces. Refer to CMake docs to set the appropriate
// stack size for this target.

#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>

namespace round_295 {
const auto infinity = std::numeric_limits<int>::max();

class Counter {
public:
  explicit Counter(int m);

  int Count(int n);

private:
  const int m_;
  std::vector<int> memo_;
  std::vector<int> visited_;
};

Counter::Counter(const int m) : m_(m) {
  memo_.resize(static_cast<size_t>(m_), -1);
  visited_.resize(static_cast<size_t>(m_));
}

int Counter::Count(const int n) {
  if (n == 0) {
    return infinity;
  }
  if (n > m_) {
    return n - m_;
  }
  if (n == m_) {
    return 0;
  }

  auto &memo = memo_[n];
  if (memo != -1) {
    return memo;
  }

  if (visited_[n] == 1) {
    return infinity;
  }
  visited_[n] = 1;

  const auto count = std::min(Count(n * 2), Count(n - 1));
  return memo = count == infinity ? count : count + 1;
}
} // namespace round_295

int main(int argc, char *argv[]) {
  int n, m;
  std::cin >> n >> m;
  std::cout << round_295::Counter(m).Count(n) << std::endl;
  return 0;
}
