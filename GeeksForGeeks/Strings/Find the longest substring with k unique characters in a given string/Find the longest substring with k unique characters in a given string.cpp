#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>

using namespace std;

long GetLongestSubStrWithKUnique(const string &str, size_t k) {
  unordered_map<char, size_t> frequencies;
  size_t i = 0;
  size_t max_len = 0;
  const auto len = str.size();
  for (size_t j = 0; j < len; ++j) {
    ++frequencies[str[j]];
    if (frequencies.size() == k) {
      max_len = max(max_len, j - i + 1);
    } else if (frequencies.size() > k) {
      const auto c = str[i];
      --frequencies[c];
      if (frequencies[c] == 0) {
        frequencies.erase(c);
        max_len = max(max_len, j - i);
      }
      ++i;
    }
  }
  return max_len == 0 ? -1 : static_cast<long>(max_len);
}

int main() {
  size_t t = 0, k = 0;
  string str;

  cin >> t;
  for (size_t i = 0; i < t; ++i) {
    cin >> str >> k;
    cout << GetLongestSubStrWithKUnique(str, k) << endl;
  }
  return 0;
}
