//
// Created by Gautham Banasandra on 22/06/18.
//

#include <vector>
#include <iostream>

using ll = long long;

void Print(const std::vector<ll> &sequence) {
  for (const auto number : sequence) {
    std::cout << number << std::endl;
  }

  std::cout << "Size : " << sequence.size() << std::endl;
}