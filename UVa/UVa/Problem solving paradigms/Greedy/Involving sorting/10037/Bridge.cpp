//
// Created by gautham on 7/8/18.
//

#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <string>

enum class Protocol { kMoveSourceToDestination, kMoveDestinationToSource };
enum class Command { kMoveFastestGroup, kMoveSlowestGroup, kMoveFastest };

using Group = std::pair<int, int>;

struct Event {
  Event() : protocol(Protocol::kMoveSourceToDestination), p1_time(-1), p2_time(-1) {}
  Event(Protocol protocol, int p1_time, int p2_time) : protocol(protocol), p1_time(p1_time), p2_time(p2_time) {}

  Protocol protocol;
  int p1_time;
  int p2_time;
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

  auto it = crossing_times_.begin();
  auto fastest = *it;
  crossing_times_.erase(it);
  source.crossing_times_.emplace(fastest);
  return fastest;
}

Group Site::GetFastestGroup() const {
  assert(crossing_times_.size() >= 2);
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

int main() {
  std::multiset<int> crossing_times{4, 5, 1, 2, 1, 1, 5, 6};
  Site source(crossing_times, "source");
  Site destination("destination");

  std::cout << "Initial" << std::endl;
  source.Print();

  auto relays = source.GetFastestGroup();
  std::cout << "Relays : " << relays.first << " " << relays.second << std::endl;

  std::cout << "\nMoving fastest group from source to destination" << std::endl;
  source.MoveFastestGroup(destination);
  source.Print();
  destination.Print();

  std::cout << "\nMoving fastest from destination to source" << std::endl;
  destination.MoveFastest(source);
  source.Print();
  destination.Print();

  std::cout << "\nMoving slowest group from source to destination" << std::endl;
  source.MoveSlowestGroup(destination);
  source.Print();
  destination.Print();

  std::cout << "\nMoving fastest from destination to source" << std::endl;
  destination.MoveFastest(source);
  source.Print();
  destination.Print();

  return 0;
}