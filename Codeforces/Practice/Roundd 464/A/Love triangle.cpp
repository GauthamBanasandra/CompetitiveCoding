#include <iostream>
#include <vector>

namespace round_464 {
bool IsLoveTriangle(const std::vector<size_t> &planes) {
  for (size_t i = 1, len = planes.size(); i < len; ++i) {
    if (planes[planes[planes[i]]] == i) {
      return true;
    }
  }
  return false;
}
} // namespace round_464

int main(int argc, char *argv[]) {
  size_t n;
  std::cin >> n;

  std::vector<size_t> planes(n + 1);
  for (size_t i = 1; i <= n; ++i) {
    std::cin >> planes[i];
  }

  std::cout << (round_464::IsLoveTriangle(planes) ? "YES" : "NO") << std::endl;
  return 0;
}
