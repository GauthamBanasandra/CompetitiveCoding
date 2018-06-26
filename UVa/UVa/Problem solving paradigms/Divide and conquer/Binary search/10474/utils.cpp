//
// Created by Gautham Banasandra on 08/06/18.
//

#include <iostream>
#include <vector>

void Print(const std::vector<int> &marbles) {
  for (const int marble : marbles) {
    std::cout << marble << " ";
  }

  std::cout << std::endl;
}