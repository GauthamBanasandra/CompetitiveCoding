#include <iostream>
#include <vector>

class Solution {
public:
  int removeDuplicates(std::vector<int> &numbers);
};

int Solution::removeDuplicates(std::vector<int> &numbers) {
  if (numbers.size() < 2) {
    return 1;
  }

  auto i_it = numbers.begin() + 1;
  for (auto j_it = i_it; j_it != numbers.end();) {
    for (; j_it != numbers.end() && *j_it == *(i_it - 1); ++j_it)
      ;
    if (j_it != numbers.end()) {
      std::swap(*i_it++, *j_it++);
    }
  }

  return static_cast<int>(std::distance(numbers.begin(), i_it));
}

int main(int argc, char *argv[]) {
  std::vector numbers{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  const auto k = Solution().removeDuplicates(numbers);

  std::cout << "k = " << k << std::endl;

  for (const int number : numbers) {
    std::cout << number << std::endl;
  }
}
