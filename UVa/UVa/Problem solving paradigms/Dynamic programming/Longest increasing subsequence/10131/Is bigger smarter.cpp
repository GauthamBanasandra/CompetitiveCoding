//
// Created by Gautham on 17-11-2018.
//

// WA

#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

struct Elephant {
  Elephant() : weight(0), iq(0) {}
  Elephant(int weight, int iq) : weight(weight), iq(iq) {}

  std::string Hash() const {
    return std::to_string(weight) + " " + std::to_string(iq);
  }

  int weight;
  int iq;
};

using Elephants = std::vector<Elephant>;

void Print(const Elephants &elephants, const std::string &msg = "") {
  std::cout << msg << std::endl;
  for (const auto &elephant : elephants) {
    std::cout << elephant.weight << "\t" << elephant.iq << std::endl;
  }
  std::cout << std::endl;
}

std::unordered_map<std::string, std::size_t> ElephantsIndices(const Elephants &elephants) {
  std::unordered_map<std::string, std::size_t> m;

  for (std::size_t i = 0, len = elephants.size(); i < len; ++i) {
    m[elephants[i].Hash()] = i;
  }
  return m;
}

std::vector<std::size_t> GetData(Elephants &elephants) {
  auto indices = ElephantsIndices(elephants);
  std::sort(elephants.begin(), elephants.end(), [](const Elephant &a, const Elephant &b) -> bool {
    /*if (a.weight == b.weight) {
      return a.iq < b.iq;
    }*/
    return a.weight < b.weight;
  });

  auto len = elephants.size();
  std::vector<std::size_t> lis;
  lis.reserve(len);

  std::vector<std::size_t> m;
  m.reserve(len + 1);
  m.emplace_back(0);

  std::vector<std::size_t> predecessors(len);

  for (std::size_t i = 0; i < len; ++i) {
    auto find_it = std::lower_bound(m.begin() + 1,
                                    m.end(),
                                    elephants[i],
                                    [&elephants](const std::size_t &i_m, const Elephant &elephant) -> bool {
                                      return elephants[i_m - 1].weight < elephant.weight;
                                    });
    auto i_m = std::distance(m.begin(), find_it);
    if (find_it == m.end()) {
      m.emplace_back(i + 1);
    } else {
      *find_it = i + 1;
    }

    predecessors[i] = m[i_m - 1];
  }

  for (auto i = m[m.size() - 1]; i > 0; i = predecessors[i - 1]) {
    std::cout << elephants[i - 1].Hash() << "\t" << indices[elephants[i - 1].Hash()] + 1 << std::endl;
    lis.emplace_back(indices[elephants[i - 1].Hash()] + 1);
  }

  std::reverse(lis.begin(), lis.end());
  return lis;
}

int main() {
  int weight, iq;
  std::vector<Elephant> elephants{
      /*{6008, 1300}, // 1
      {6000, 2100}, // 2
      {500, 2000},  // 3
      {1000, 4000}, // 4
      {1100, 3000}, // 5
      {6000, 2000}, // 6
      {8000, 1400}, // 7
      {6000, 1200}, // 8
      {2000, 1900}  // 9*/

      {1, 1},
      {1, 2},
      {1, 9998},
      {1, 9999},
      {1, 10000},
      {2, 1},
      {2, 2},
      {2, 9998},
      {2, 9999},
      {2, 10000},
      {9998, 1},
      {9998, 2},
      {9998, 9998},
      {9998, 9999},
      {9998, 10000},
      {9999, 1},
      {9999, 2},
      {9999, 9998},
      {9999, 9999},
      {9999, 10000},
      {10000, 1},
      {10000, 2},
      {10000, 9998},
      {10000, 9999},
      {10000, 10000},
      {1, 1},
      {2, 1},
      {9998, 1},
      {9999, 1},
      {10000, 1},
      {1, 2},
      {2, 2},
      {9998, 2},
      {9999, 2},
      {10000, 2},
      {1, 9998},
      {2, 9998},
      {9998, 9998},
      {9999, 9998},
      {10000, 9998},
      {1, 9999},
      {2, 9999},
      {9998, 9999},
      {9999, 9999},
      {10000, 9999},
      {1, 10000},
      {2, 10000},
      {9998, 10000},
      {9999, 10000},
      {10000, 10000},
  };

  /*elephants.clear();
  std::string line;
  while (std::getline(std::cin, line), !line.empty()) {
    std::istringstream tokenizer(line);
    tokenizer >> weight >> iq;
    elephants.emplace_back(weight, iq);
  }*/

  auto indices = GetData(elephants);
  std::cout << indices.size() << std::endl;
  for (const auto &index : indices) {
    std::cout << index << std::endl;
  }
  return 0;
}