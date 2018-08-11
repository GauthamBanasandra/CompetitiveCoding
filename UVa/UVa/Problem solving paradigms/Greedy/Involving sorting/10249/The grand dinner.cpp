//
// Created by gautham on 9/8/18.
//

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <cassert>
#include <ios>

struct Table {
  Table() : id(-1), capacity(-1) {}
  Table(int id, int capacity) : id(id), capacity(capacity) {}

  bool operator<(const Table &other) const {
    return capacity == other.capacity ? id < other.id : capacity < other.capacity;
  }

  int id;
  int capacity;
};

struct Team {
  Team() : id(-1), num(-1) {}
  Team(int id, int num) : id(id), num(num) {}

  int id;
  int num;
};

struct Arrangement {
  Arrangement() : is_possible(false) {}
  Arrangement(bool is_possible) : is_possible(is_possible) {}
  Arrangement(bool is_possible, std::vector<std::unordered_set<int>> order)
      : is_possible(is_possible), order(std::move(order)) {}

  bool is_possible;
  std::vector<std::unordered_set<int>> order;
};

class HotelManager {
 public:
  HotelManager(const std::vector<int> &tables, const std::vector<int> &teams);
  Arrangement Assign();

 private:
  void Assign(Table &table, std::vector<std::unordered_set<int>> &order);

  std::priority_queue<Table, std::vector<Table>, std::less<Table>> tables_;
  std::list<Team> teams_;
};

HotelManager::HotelManager(const std::vector<int> &tables, const std::vector<int> &teams) {
  for (std::size_t i = 0; i < tables.size(); ++i) {
    tables_.emplace(i + 1, tables[i]);
  }

  for (std::size_t i = 0; i < teams.size(); ++i) {
    teams_.emplace_back(i + 1, teams[i]);
  }
}

Arrangement HotelManager::Assign() {
  std::vector<std::unordered_set<int>> order(teams_.size());

  while (!tables_.empty() && !teams_.empty()) {
    Table table = tables_.top();
    tables_.pop();
    assert(table.capacity > 0);

    // It's guaranteed that all the slots in the table will be exhausted
    Assign(table, order);
  }

  if (teams_.empty()) {
    return {true, order};
  } else {
    return {false};
  }
}

void HotelManager::Assign(Table &table, std::vector<std::unordered_set<int>> &order) {
  // Until there's some space in the table or if there are any people to be assigned
  while (table.capacity > 0 && !teams_.empty()) {
    Team team = teams_.front();
    assert(team.num > 0);

    auto &seating = order[team.id - 1];
    if (seating.find(table.id) != seating.end()) {
      // Found that this table had already been assigned to this team
      // Break out because there can't be 2 team members in the same table
      return;
    }

    seating.insert(table.id);
    --table.capacity;
    --team.num;

    // Add team members back to queue only if there are any left to be assigned
    if (team.num > 0) {
      teams_.emplace_back(team);
    }

    teams_.pop_front();
  }
}

int main() {
  std::ios::sync_with_stdio(false);

  // The following example is a counter example, I'm guessing UVa has a weak test case
  std::vector<int> teams{8, 9, 7, 16, 4, 8, 5, 16, 6, 7, 14, 4, 6, 11, 12};
  std::vector<int>
      tables{14, 6, 8, 2, 6, 7, 14, 18, 15, 4, 1, 8, 7, 10, 14, 3, 5};

  /*
   * Expected output for the above input is -
   *  1
      8 9 1 15 7 14 3 12
      8 9 1 15 7 14 6 13 12
      8 9 1 15 7 14 3
      8 9 1 15 7 14 5 6 13 2 12 3 17 10 16 4
      8 9 1 15
      8 9 7 1 15 14 12 5
      8 9 7 1 15
      8 9 7 1 15 2 14 3 13 6 5 12 17 10 16 4
      8 9 7 1 15 13
      8 9 7 1 15 14 2
      8 9 7 6 3 15 1 14 2 13 5 12 17 10
      8 9 7 6
      8 9 7 3 15 1
      8 9 6 2 12 5 13 14 17 1 15
      8 7 3 9 11 16 10 15 1 17 14 13
   */

  // This program returns 0 as the output, which is incorrect

  int num_teams, num_tables;
  while (std::cin >> num_teams >> num_tables, num_teams || num_tables) {
    teams.resize(static_cast<std::size_t>(num_teams));
    tables.resize(static_cast<std::size_t>(num_tables));

    for (int i = 0; i < num_teams; ++i) {
      std::cin >> teams[i];
    }

    for (int i = 0; i < num_tables; ++i) {
      std::cin >> tables[i];
    }

    HotelManager manager(tables, teams);
    auto arrangement = manager.Assign();
    if (arrangement.is_possible) {
      std::cout << 1 << std::endl;
      for (auto &order : arrangement.order) {
        std::string output;
        for (auto table : order) {
          output += std::to_string(table) + " ";
        }

        if (!output.empty()) {
          output.pop_back();
        }
        std::cout << output << std::endl;
      }
    } else {
      std::cout << 0 << std::endl;
    }
  }

  return 0;
}