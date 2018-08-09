//
// Created by gautham on 9/8/18.
//

// WA
#include <list>
#include <vector>
#include <iostream>
#include <string>

struct Table {
  Table() : id(-1), capacity(-1) {}
  Table(int id, int capacity) : id(id), capacity(capacity) {}

  bool operator<(const Table &other) const {
    return capacity == other.capacity ? id < other.id : capacity > other.capacity;
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
  Arrangement(bool is_possible, std::vector<std::vector<int>> order)
      : is_possible(is_possible), order(std::move(order)) {}

  bool is_possible;
  std::vector<std::vector<int>> order;
};
class HotelManager {
 public:
  HotelManager(const std::vector<int> &tables, const std::vector<int> &teams);
  Arrangement Assign();

 private:
  std::list<Table> tables_;
  std::list<Team> teams_;
};

HotelManager::HotelManager(const std::vector<int> &tables, const std::vector<int> &teams) {
  for (std::size_t i = 0; i < tables.size(); ++i) {
    tables_.emplace_back(i + 1, tables[i]);
  }

  for (std::size_t i = 0; i < teams.size(); ++i) {
    teams_.emplace_back(i + 1, teams[i]);
  }

  tables_.sort();
}

Arrangement HotelManager::Assign() {
  std::vector<std::vector<int>> order(teams_.size());

  while (!tables_.empty() && !teams_.empty()) {
    auto table_it = tables_.begin();
    if (table_it->capacity < teams_.size()) {
      return {false};
    }

    for (auto team_it = teams_.begin(); team_it != teams_.end();) {
      order[team_it->id - 1].emplace_back(table_it->id);
      --(team_it->num);

      if (team_it->num <= 0) {
        team_it = teams_.erase(team_it);
      } else {
        ++team_it;
      }
    }

    tables_.pop_front();
  }
  return {true, order};
}

int main() {
  std::vector<int> teams{8, 6, 2};
  std::vector<int> tables{6, 11, 10, 10, 5, 5, 4, 11};

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