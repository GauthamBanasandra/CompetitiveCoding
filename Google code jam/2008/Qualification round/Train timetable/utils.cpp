//
// Created by gauth on 14-01-2018.
//

#include <iostream>
#include <queue>

enum class event_type { A, B };
void print(std::priority_queue<std::pair<int, event_type>> event_queue) {
  while (!event_queue.empty()) {
    auto event = event_queue.top();
    event_queue.pop();
    std::cout << -event.first << "\t" << (event.second == event_type::A ? 'A' : 'B') << std::endl;
  }
}