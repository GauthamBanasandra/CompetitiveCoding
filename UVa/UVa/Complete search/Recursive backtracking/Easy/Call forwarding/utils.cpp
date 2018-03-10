//
// Created by gauth on 10-03-2018.
//

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using mss = std::unordered_map<std::string, std::string>;

void Print(const std::unordered_map<int, mss> forwarding_table) {
  for (auto entry : forwarding_table) {
    for (auto inner_entry : entry.second) {
      std::cout << entry.first << " : " << inner_entry.first << " -> " << inner_entry.second << std::endl;
    }
  }
}