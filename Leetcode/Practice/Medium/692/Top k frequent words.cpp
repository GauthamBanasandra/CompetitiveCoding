#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lc_692 {
struct ByFrequency {
  // I couldn't recollect the signature of this method. I kept writing operator<
  // (which is wrong)
  bool operator()(const std::pair<size_t, std::string> &a,
                  const std::pair<size_t, std::string> &b) const {
    // Went wrong here. Need to use inverse of the order we want
    // If frequencies are the same, a comes before b if a.word is
    // lexicographically smaller than b.word (used a.word *>* b.word) here
    // If frequencies are not same, a comes before b if a has greater frequency
    // than b (used a.frequency < b.frequency here)
    return a.first == b.first ? a.second > b.second : a.first < b.first;
  }
};

class Solution {
public:
  std::vector<std::string> topKFrequent(std::vector<std::string> &words, int k);
};

std::vector<std::string> Solution::topKFrequent(std::vector<std::string> &words,
                                                int k) {
  std::unordered_map<std::string, size_t> frequencies;
  for (const auto &word : words) {
    ++frequencies[word];
  }

  std::priority_queue<std::pair<size_t, std::string>,
                      std::vector<std::pair<size_t, std::string>>, ByFrequency>
      order;
  for (const auto &[word, frequency] : frequencies) {
    order.emplace(frequency, word);
  }

  std::vector<std::string> top_k;
  top_k.reserve(k);
  for (auto i = 0; i < k; ++i) {
    top_k.emplace_back(order.top().second);
    order.pop();
  }
  return top_k;
}
} // namespace lc_692

int main(int argc, char *argv[]) {
  std::vector<std::string> words{"the", "day", "is",    "sunny", "the",
                                 "the", "the", "sunny", "is",    "is"};
  for (const auto &word : lc_692::Solution().topKFrequent(words, 4)) {
    std::cout << word << std::endl;
  }
  return 0;
}
