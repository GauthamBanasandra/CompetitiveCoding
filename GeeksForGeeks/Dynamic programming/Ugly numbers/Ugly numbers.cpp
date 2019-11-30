// This is O(n*max_ugly_number) - TLE

#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>

class Finder {
public:
  size_t GetNthUglyNumber(size_t n);

private:
  bool IsUgly(int n);

  std::unordered_map<size_t, bool> memo_;
  std::vector<size_t> ugly_numbers_;
};

size_t Finder::GetNthUglyNumber(const size_t n) {
  for (size_t i = 1; ugly_numbers_.size() < n; ++i) {
    if (IsUgly(static_cast<int>(i))) {
      ugly_numbers_.emplace_back(i);
    }
  }
  return ugly_numbers_.back();
}

bool Finder::IsUgly(const int n) {
  if (n == 1) {
    return true;
  }

  if (memo_.find(n) != memo_.end()) {
    return memo_[n];
  }

  if (n >= 2 && n % 2 == 0) {
    return memo_[n] = IsUgly(n / 2);
  }
  if (n >= 3 && n % 3 == 0) {
    return memo_[n] = IsUgly(n / 3);
  }
  if (n >= 5 && n % 5 == 0) {
    return memo_[n] = IsUgly(n / 5);
  }
  return memo_[n] = false;
}

int main(int argc, char *argv[]) {
  size_t t;
  size_t n;

  std::cin >> t;
  while (t--) {
    std::cin >> n;
    std::cout << Finder().GetNthUglyNumber(n) << std::endl;
  }
  return 0;
}
