//
// Created by gauth on 14-01-2018.
//

#include <iostream>
#include <queue>

enum class event_type { kDepartFromA, kArriveAtA, kDepartFromB, kArriveAtB };

void print(std::priority_queue<std::pair<int, event_type>> event_queue);

int main() {
  int n, na, nb, t, n_trains_a, n_trains_b;
  std::string departure, arrival;
  std::priority_queue<std::pair<int, event_type>> event_queue;

  std::cin >> n;
  for (auto i = 0; i < n; ++i) {
    std::cin >> t;
    std::cin >> na >> nb;
    std::cin.ignore();
    while (na-- > 0) {
      std::cin >> departure >> arrival;

      auto hh_i = departure.find(':');
      event_queue.emplace(-(std::stoi(departure.substr(0, hh_i)) * 60 + std::stoi(departure.substr(hh_i + 1))),
                          event_type::kDepartFromA);

      hh_i = arrival.find(':');
      event_queue.emplace(-(std::stoi(arrival.substr(0, hh_i)) * 60 + std::stoi(arrival.substr(hh_i + 1)) + t),
                          event_type::kArriveAtB);
    }

    while (nb-- > 0) {
      std::cin >> departure >> arrival;

      auto hh_i = departure.find(':');
      event_queue.emplace(-(std::stoi(departure.substr(0, hh_i)) * 60 + std::stoi(departure.substr(hh_i + 1))),
                          event_type::kDepartFromB);

      hh_i = arrival.find(':');
      event_queue.emplace(-(std::stoi(arrival.substr(0, hh_i)) * 60 + std::stoi(arrival.substr(hh_i + 1)) + t),
                          event_type::kArriveAtA);
    }

    na = nb = n_trains_a = n_trains_b = 0;
    while (!event_queue.empty()) {
      const auto &event = event_queue.top();
      switch (event.second) {
        case event_type::kDepartFromA:
          if (n_trains_a > 0) {
            --n_trains_a;
          } else {
            ++na;
          }
          break;

        case event_type::kArriveAtA:++n_trains_a;
          break;

        case event_type::kDepartFromB:
          if (n_trains_b > 0) {
            --n_trains_b;
          } else {
            ++nb;
          }
          break;

        case event_type::kArriveAtB:++n_trains_b;
          break;
      }

      event_queue.pop();
    }

    printf("Case #%d: %d %d\n", i + 1, na, nb);
  }

  return 0;
}