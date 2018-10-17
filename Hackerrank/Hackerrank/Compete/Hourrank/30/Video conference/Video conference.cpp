//
// Created by gautham on 2/10/18.
//

// WA

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

std::vector<std::string> GetShortNames(const std::vector<std::string> &full_names) {
  std::vector<std::string> short_names;
  std::unordered_set<std::string> fragments;
  std::unordered_map<std::string, int> frequency;

  for (const auto &full_name : full_names) {
    std::string prefix;
    for (std::size_t i = 0; i < full_name.length(); ++i) {
      auto short_name = full_name.substr(0, i + 1);
      if (fragments.find(short_name) == fragments.end()) {
        prefix = short_name;
        break;
      }
    }

    std::string short_name = prefix;
    if (prefix.empty()) {
      assert(fragments.find(full_name) != fragments.end());
      if (frequency.find(full_name) == frequency.end()) {
        ++frequency[full_name];
      }
      short_name = full_name;
    }

    if (frequency[short_name] != 0) {
      short_name += " " + std::to_string(frequency[short_name] + 1);
    }
    short_names.emplace_back(short_name);

    for (std::size_t i = 0; i < full_name.length(); ++i) {
      fragments.emplace(full_name.substr(0, i + 1));
    }
  }
  return short_names;
}

int main() {
  std::vector<std::string> short_names{
      "alvin",
      "alice",
      "alvin",
  };

  for (auto &short_name : GetShortNames(short_names)) {
    std::cout << short_name << std::endl;
  }
  return 0;
}