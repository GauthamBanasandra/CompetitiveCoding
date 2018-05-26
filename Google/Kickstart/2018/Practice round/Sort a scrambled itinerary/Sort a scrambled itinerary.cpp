//
// Created by gauth on 24-02-2018.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using ui = unsigned int;

int main() {
  ui t, n;
  std::string departure, arrival;
  std::unordered_set<std::string> arrivals;
  std::unordered_map<std::string, std::string> itinerary;

  std::cin >> t;
  for (ui c = 1; c <= t; ++c) {
    itinerary.clear();
    arrivals.clear();

    std::cin >> n;
    std::cin.ignore();

    for (ui i = 0; i < n; ++i) {
      std::getline(std::cin, departure);
      std::getline(std::cin, arrival);

      arrivals.emplace(arrival);
      itinerary[departure] = arrival;
    }

    for (const auto &item : itinerary) {
      if (arrivals.find(item.first) == arrivals.end()) {
        departure = item.first;
        break;
      }
    }

    printf("Case #%u:", c);
    while (!itinerary.empty()) {
      arrival = itinerary[departure];
      std::cout << ' ' << departure << '-' << arrival;
      itinerary.erase(departure);
      departure = arrival;
    }

    std::cout << std::endl;
  }

  return 0;
}