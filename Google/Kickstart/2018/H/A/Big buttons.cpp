//
// Created by Gautham on 18-11-2018.
//

#include <vector>
#include <map>
#include <string>
#include <iostream>

using ll = unsigned long long;

class Analyzer {
 public:
  explicit Analyzer(std::vector<std::string> forbidden_patterns_)
      : forbidden_patterns_(std::move(forbidden_patterns_)) {}

  ll CountWinningPatterns(ll n) const;
 private:
  std::vector<std::string> forbidden_patterns_;
};

ll Analyzer::CountWinningPatterns(ll n) const {
  return 1 << n;
}

int main() {
  std::vector<std::string> forbidden_patterns;

    // Impossible as it would overflow
  std::cout << (1 << 50) << std::endl;
  std::cout << Analyzer(forbidden_patterns).CountWinningPatterns(50) << std::endl;
  return 0;
}