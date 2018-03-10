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
const int max_time = 8784;

void Print(const std::unordered_map<int, mss> forwarding_table);

void AddForwardingTableEntry(std::unordered_map<int, mss> &forwarding_table,
                             const std::string &source,
                             int time,
                             int duration,
                             const std::string &target) {
  for (int t = time; t <= time + duration; ++t) {
    assert(t <= max_time);
    forwarding_table[t][source] = target;
  }
}

std::string MakeCall(std::unordered_map<int, mss> &forwarding_table,
                     std::unordered_set<std::string> &forwarding_chain,
                     const int time,
                     std::string &extension) {
  if (forwarding_chain.find(extension) != forwarding_chain.end()) {
    return "9999";
  }

  if ((forwarding_table.find(time) == forwarding_table.end())
      || (forwarding_table[time].find(extension) == forwarding_table[time].end())) {
    return extension;
  }

  forwarding_chain.insert(extension);
  return MakeCall(forwarding_table, forwarding_chain, time, forwarding_table[time][extension]);
}

int main() {
  int n;
  std::string source, time, duration, target, extension;
  std::string line;

  std::cin >> n;
  std::cin.ignore();
  std::cout << "CALL FORWARDING OUTPUT" << std::endl;

  for (int i = 0; i < n; ++i) {
    std::unordered_map<int, mss> forwarding_table;

    while (std::getline(std::cin, line), line != "0000") {
      std::istringstream tokenizer(line);
      tokenizer >> source;
      tokenizer >> time;
      tokenizer >> duration;
      tokenizer >> target;
      AddForwardingTableEntry(forwarding_table, source, atoi(time.c_str()), atoi(duration.c_str()), target);
    }

    printf("SYSTEM %d\n", i + 1);
    while (std::getline(std::cin, line), line != "9000") {
      std::unordered_set<std::string> forwarding_chain;
      std::istringstream tokenizer(line);
      tokenizer >> time;
      tokenizer >> extension;

      printf("AT %s CALL TO %s RINGS %s\n",
             time.c_str(),
             extension.c_str(),
             MakeCall(forwarding_table, forwarding_chain, atoi(time.c_str()), extension).c_str());
    }
  }

  std::cout << "END OF OUTPUT" << std::endl;
  return 0;
}