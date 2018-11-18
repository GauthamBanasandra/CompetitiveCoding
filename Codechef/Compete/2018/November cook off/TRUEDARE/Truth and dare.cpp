//
// Created by Gautham on 18-11-2018.
//

#include <unordered_set>
#include <iostream>

int main() {
  int t, task, n;
  std::unordered_set<int> ram_truth, ram_dare;

  std::cin >> t;
  while (t--) {
    ram_truth.clear();
    ram_dare.clear();

    std::cin >> n;
    while (n--) {
      std::cin >> task;
      ram_truth.emplace(task);
    }

    std::cin >> n;
    while (n--) {
      std::cin >> task;
      ram_dare.emplace(task);
    }

    auto win = true;
    std::cin >> n;
    while (n--) {
      std::cin >> task;
      if (ram_truth.find(task) == ram_truth.end()) {
        win = false;
      }
    }

    std::cin >> n;
    while (n--) {
      std::cin >> task;
      if (ram_dare.find(task) == ram_truth.end()) {
        win = false;
      }
    }

    std::cout << (win ? "yes" : "no") << std::endl;
  }
  return 0;
}