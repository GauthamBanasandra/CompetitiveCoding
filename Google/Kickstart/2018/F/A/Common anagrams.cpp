//
// Created by gautham on 1/10/18.
//

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
#include <iostream>
#include <cassert>
#include <ios>

using FrequencyTable = std::unordered_map<char, int>;
using AllSubStr = std::list<std::string>;

class Anagrams {
 public:
  explicit Anagrams(const std::string &b);
  std::size_t GetCommon(const std::string &a) const;

 private:
  bool MatchAnagram(const std::string &a_sub, FrequencyTable f) const;
  AllSubStr GetSubstrings(const std::string &a) const;

  std::unordered_map<std::size_t, std::list<FrequencyTable>> data_;
};

Anagrams::Anagrams(const std::string &b) {
  for (std::size_t i = 0, b_len = b.length(); i < b_len; ++i) {
    for (std::size_t j = i; j < b_len; ++j) {
      FrequencyTable f;
      for (auto c : b.substr(i, j - i + 1)) {
        ++f[c];
      }
      data_[j - i + 1].emplace_back(f);
    }
  }
}

std::size_t Anagrams::GetCommon(const std::string &a) const {
  std::size_t num = 0;
  for (const auto &a_sub : GetSubstrings(a)) {
    auto a_sub_len = a_sub.length();
    auto data_it = data_.find(a_sub_len);
    assert(data_it != data_.end());

    auto len = data_it->first;

    for (const auto &f : data_it->second) {
      if (MatchAnagram(a_sub, f)) {
        ++num;
        break;
      }
    }
  }
  return num;
}

bool Anagrams::MatchAnagram(const std::string &a_sub, FrequencyTable f) const {
  for (auto c : a_sub) {
    auto f_it = f.find(c);
    if (f_it == f.end()) {
      return false;
    }

    --f_it->second;
    if (f_it->second == 0) {
      f.erase(f_it);
    }
  }
  return f.empty();
}

AllSubStr Anagrams::GetSubstrings(const std::string &a) const {
  AllSubStr unique;
  for (std::size_t i = 0, a_len = a.length(); i < a_len; ++i) {
    for (std::size_t j = i; j < a_len; ++j) {
      unique.emplace_back(a.substr(i, j - i + 1));
    }
  }
  return unique;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::string a, b;
  int t, l;

  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    std::cin >> l;
    std::cin >> a >> b;
    std::cout << "Case #" << i << ": " << Anagrams(b).GetCommon(a) << std::endl;
  }
  return 0;
}