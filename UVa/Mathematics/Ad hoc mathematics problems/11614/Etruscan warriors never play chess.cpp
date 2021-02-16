// WIP

#include <cmath>
#include <iostream>
#include <ostream>

namespace uva_11614 {
class RowFinder {
public:
  static long long GetRowCount(long double num);
};

long long RowFinder::GetRowCount(const long double num) {
  const auto rows = std::log2l(num);
  return static_cast<long long>(std::floor(rows));
}
} // namespace uva_11614

int main(int argc, char *argv[]) {
  size_t t;
  long double num;
  std::cin >> t;

  while (t--) {
    std::cin >> num;
    std::cout << uva_11614::RowFinder::GetRowCount(num) << std::endl;
  }

  return 0;
}
