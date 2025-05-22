#include <vector>

class Solution {
public:
  void duplicateZeros(std::vector<int> &numbers);
};

void Solution::duplicateZeros(std::vector<int> &numbers) {
  std::vector<int> duplicate_zeros;
  duplicate_zeros.resize(numbers.size());

  for (auto i_it = numbers.begin(), j_it = duplicate_zeros.begin();
       j_it != duplicate_zeros.end(); ++i_it) {
    *j_it++ = *i_it;
    if (j_it != duplicate_zeros.end() && *i_it == 0) {
      *j_it++ = 0;
    }
  }

  numbers.swap(duplicate_zeros);
}

int main() { return 0; }