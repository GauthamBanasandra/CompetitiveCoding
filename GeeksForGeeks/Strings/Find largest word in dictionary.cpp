#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class SubsequenceFinder {
public:
  SubsequenceFinder(const string &src);

  string GetLongestSubsequence(const vector<string> &strings);

private:
  bool IsSubsequence(const string &s);

  const string &src_;
  unordered_map<char, vector<int>> index_;
};

SubsequenceFinder::SubsequenceFinder(const string &src) : src_{src} {
  for (auto i = 0; i < src_.size(); ++i) {
    index_[src_[i]].emplace_back(i);
  }
}

string SubsequenceFinder::GetLongestSubsequence(const vector<string> &strings) {
  string longest_subseq;
  for (const auto &s : strings) {
    if (IsSubsequence(s) && s.size() > longest_subseq.size()) {
      longest_subseq = s;
    }
  }
  return longest_subseq;
}

bool SubsequenceFinder::IsSubsequence(const string &s) {
  auto last = -1;
  for (auto c : s) {
    auto find_it = index_.find(c);
    if (find_it == index_.end()) {
      return false;
    }
    auto &indices = find_it->second;
    auto index_it = upper_bound(indices.begin(), indices.end(), last);
    if (index_it == indices.end()) {
      return false;
    }
    last = *index_it;
  }
  return true;
}

int main() {
  size_t t;
  size_t num_words;
  vector<string> words;
  string src;

  cin >> t;
  for (size_t i = 0; i < t; ++i) {
    cin >> num_words;
    words.resize(num_words);
    for (size_t j = 0; j < num_words; ++j) {
      cin >> words[j];
    }
    cin >> src;
    cout << SubsequenceFinder(src).GetLongestSubsequence(words) << endl;
  }
  return 0;
}
