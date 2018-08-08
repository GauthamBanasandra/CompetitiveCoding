//
// Created by gautham on 7/8/18.
//

#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <algorithm>

enum class Protocol { kMoveSourceToDestination, kMoveDestinationToSource };
enum class Command { kMoveFastestGroup, kMoveSlowestGroup, kMoveFastest };

using Group = std::pair<int, int>;

struct Event {
  Event() : protocol(Protocol::kMoveSourceToDestination), first(-1), second(-1) {}
  Event(Protocol protocol, int first, int second) : protocol(protocol), first(first), second(second) {}

  Protocol protocol;
  int first;
  int second;
};

class Site {
 public:
  explicit Site(std::string tag) : tag_(std::move(tag)) {}
  Site(std::multiset<int> &crossing_times, std::string tag) : crossing_times_(crossing_times), tag_(std::move(tag)) {}

  Group MoveFastestGroup(Site &destination);
  Group MoveSlowestGroup(Site &destination);
  int MoveFastest(Site &source);
  Group GetFastestGroup() const;

  bool IsEmpty() const { return crossing_times_.empty(); }
  bool Contains(int crossing_time) const { return crossing_times_.find(crossing_time) != crossing_times_.end(); }

  void Print() const;

 private:
  const std::string tag_;
  std::multiset<int> crossing_times_;
};

Group Site::MoveFastestGroup(Site &destination) {
  assert(crossing_times_.size() >= 2);
  assert(tag_ == "source");

  auto it = crossing_times_.begin();
  auto first = *it;
  it = crossing_times_.erase(it);
  auto second = *it;
  crossing_times_.erase(it);

  destination.crossing_times_.emplace(first);
  destination.crossing_times_.emplace(second);
  return {first, second};
}

Group Site::MoveSlowestGroup(Site &destination) {
  assert(crossing_times_.size() >= 2);
  assert(tag_ == "source");

  auto it = crossing_times_.rbegin();
  auto second = *it;
  crossing_times_.erase((++it).base());
  it = crossing_times_.rbegin();
  auto first = *it;
  crossing_times_.erase((++it).base());

  destination.crossing_times_.emplace(first);
  destination.crossing_times_.emplace(second);
  return {first, second};
}

int Site::MoveFastest(Site &source) {
  assert(!IsEmpty());
  assert(tag_ == "destination");

  auto it = crossing_times_.begin();
  auto fastest = *it;
  crossing_times_.erase(it);
  source.crossing_times_.emplace(fastest);
  return fastest;
}

Group Site::GetFastestGroup() const {
  assert(crossing_times_.size() >= 2);
  assert(tag_ == "source");

  auto it = crossing_times_.begin();
  return {*it, *(++it)};
}

void Site::Print() const {
  std::cout << tag_ << std::endl;
  for (auto &crossing_time : crossing_times_) {
    std::cout << crossing_time << " ";
  }
  std::cout << std::endl;
}

class BridgeCrossing {
 public:
  BridgeCrossing(Site source, Site destination);
  std::vector<Event> Start();
  static void SpecialCase(int crossing_time);

 private:
  Command GetCommand(Protocol protocol) const;
  Event Execute(Protocol protocol, Command command);
  Protocol NextProtocol(Protocol protocol) const {
    return protocol == Protocol::kMoveSourceToDestination ? Protocol::kMoveDestinationToSource
                                                          : Protocol::kMoveSourceToDestination;
  }

  Group relays_;
  Site source_;
  Site destination_;
};

std::vector<Event> BridgeCrossing::Start() {
  std::vector<Event> events;
  auto protocol = Protocol::kMoveSourceToDestination;

  while (!source_.IsEmpty()) {
    auto command = GetCommand(protocol);
    auto event = Execute(protocol, command);
    events.emplace_back(event);
    protocol = NextProtocol(protocol);
  }
  return events;
}

Command BridgeCrossing::GetCommand(Protocol protocol) const {
  switch (protocol) {
    case Protocol::kMoveSourceToDestination:
      if (!destination_.Contains(relays_.first) && !destination_.Contains(relays_.second)) {
        return Command::kMoveFastestGroup;
      }

      if ((!destination_.Contains(relays_.first) && destination_.Contains(relays_.second)) ||
          (destination_.Contains(relays_.first) && destination_.Contains(relays_.second) &&
              (relays_.first == relays_.second))) {
        return Command::kMoveSlowestGroup;
      }

      assert(false);

    case Protocol::kMoveDestinationToSource:return Command::kMoveFastest;
  }
}

Event BridgeCrossing::Execute(Protocol protocol, Command command) {
  switch (command) {
    case Command::kMoveFastestGroup: {
      auto group = source_.MoveFastestGroup(destination_);
      return {protocol, group.first, group.second};
    }

    case Command::kMoveSlowestGroup: {
      auto group = source_.MoveSlowestGroup(destination_);
      return {protocol, group.first, group.second};
    }

    case Command::kMoveFastest: {
      auto person = destination_.MoveFastest(source_);
      return {protocol, person, -1};
    }
  }
}

BridgeCrossing::BridgeCrossing(Site source, Site destination)
    : source_(std::move(source)), destination_(std::move(destination)) {
  relays_ = source_.GetFastestGroup();
}

void BridgeCrossing::SpecialCase(int crossing_time) {
  std::cout << crossing_time << std::endl << crossing_time << std::endl;
}

void PrintStrategy(const std::vector<Event> &events) {
  std::ostringstream output;

  long total_time = 0;
  for (auto &event : events) {
    switch (event.protocol) {
      case Protocol::kMoveSourceToDestination: {
        output << event.first << " " << event.second << std::endl;
        total_time += std::max(event.first, event.second);
        break;
      }

      case Protocol::kMoveDestinationToSource: {
        output << event.first << std::endl;
        total_time += event.first;
        break;
      }
    }
  }

  std::cout << total_time << std::endl;
  std::cout << output.str();
}

int main() {
  int num_crossing_times = 0, crossing_time = 0, t = 0;
  std::multiset<int> crossing_times{
      1,
      10,
      10,
      10,
      100,
      100,
  };

  Site source(crossing_times, "source");
  Site destination("destination");
  BridgeCrossing crossing(source, destination);
  auto events = crossing.Start();
  PrintStrategy(events);

  /*std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    if (i > 1) {
      std::cout << std::endl;
    }

    std::cin >> num_crossing_times;
    if (num_crossing_times == 1) {
      std::cin >> crossing_time;
      BridgeCrossing::SpecialCase(crossing_time);
      continue;
    }

    crossing_times.clear();
    for (int j = 0; j < num_crossing_times; ++j) {
      std::cin >> crossing_time;
      crossing_times.insert(crossing_time);
    }

    Site source(crossing_times, "source");
    Site destination("destination");
    BridgeCrossing crossing(source, destination);
    auto events = crossing.Start();
    PrintStrategy(events);
  }*/
  return 0;
}