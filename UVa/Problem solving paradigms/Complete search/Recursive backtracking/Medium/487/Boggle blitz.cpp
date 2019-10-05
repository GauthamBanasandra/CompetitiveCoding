//
// Created by gauth on 15-04-2018.
//

#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace uva487 {
struct LexicographicComparator {
  bool operator()(const std::string &s1, const std::string &s2) const {
    if (s1.length() == s2.length()) {
      return s1 < s2;
    }

    return s1.length() < s2.length();
  }
};

using LegalWordsContainer = std::set<std::string, LexicographicComparator>;

enum Direction {
  k_north,
  k_south,
  k_east,
  k_west,
  k_north_east,
  k_north_west,
  k_south_east,
  k_south_west,
  k_last
};

struct Pos {
  Pos(bool is_valid, int row, int column)
      : is_valid(is_valid), row(row), column(column) {}

  bool is_valid;
  int row;
  int column;
};

class BoggleBlitzLayout {
public:
  explicit BoggleBlitzLayout(int n);

  void Visit(const Pos &pos);

  void UndoVisit(const Pos &pos);

  bool IsVisited(const Pos &pos);

private:
  int n;
  std::vector<int> grid;
};

BoggleBlitzLayout::BoggleBlitzLayout(int n) : n(n) {
  grid = std::vector<int>(n, 0);
}

inline void BoggleBlitzLayout::Visit(const Pos &pos) {
  assert(pos.is_valid);
  grid[pos.row] |= (1 << pos.column);
}

inline void BoggleBlitzLayout::UndoVisit(const Pos &pos) {
  assert(pos.is_valid);
  grid[pos.row] &= ~(1 << pos.column);
}

inline bool BoggleBlitzLayout::IsVisited(const Pos &pos) {
  assert(pos.is_valid);
  return static_cast<bool>(grid[pos.row] & (1 << pos.column));
}

class BoggleBlitz {
public:
  BoggleBlitz(int n, std::vector<std::string> grid)
      : n(n), grid(std::move(grid)) {}

  LegalWordsContainer Solve();

private:
  bool IsLegal(const Pos &pos, const Pos &next_pos);

  Pos GetNextPos(const Pos &pos, Direction d);

  void NextWord(Pos &pos, std::string &word, BoggleBlitzLayout &layout,
                LegalWordsContainer &legal_words);

  int n;
  std::vector<std::string> grid;
};

inline Pos BoggleBlitz::GetNextPos(const Pos &pos, Direction d) {
  Pos next_pos{false, pos.row, pos.column};

  switch (d) {
  case k_north:
    next_pos.row -= 1;
    break;

  case k_south:
    next_pos.row += 1;
    break;

  case k_east:
    next_pos.column += 1;
    break;

  case k_west:
    next_pos.column -= 1;
    break;

  case k_north_east:
    next_pos.row -= 1;
    next_pos.column += 1;
    break;

  case k_north_west:
    next_pos.row -= 1;
    next_pos.column -= 1;
    break;

  case k_south_east:
    next_pos.row += 1;
    next_pos.column += 1;
    break;

  case k_south_west:
    next_pos.row += 1;
    next_pos.column -= 1;
    break;

  case k_last:
    assert(false);
    break;
  }

  next_pos.is_valid = (next_pos.row < n && next_pos.row >= 0) &&
                      (next_pos.column < n && next_pos.column >= 0);
  return next_pos;
}

inline bool BoggleBlitz::IsLegal(const Pos &pos, const Pos &next_pos) {
  assert(pos.is_valid);
  assert(next_pos.is_valid);
  return grid[pos.row][pos.column] < grid[next_pos.row][next_pos.column];
}

void BoggleBlitz::NextWord(Pos &pos, std::string &word,
                           BoggleBlitzLayout &layout,
                           LegalWordsContainer &legal_words) {
  if (word.length() >= 3) {
    legal_words.insert(word);
  }

  for (int direction = Direction::k_north; direction != Direction::k_last;
       ++direction) {
    auto next_pos = GetNextPos(pos, static_cast<Direction>(direction));
    if (!next_pos.is_valid || !IsLegal(pos, next_pos) ||
        layout.IsVisited(next_pos)) {
      continue;
    }

    word += grid[next_pos.row][next_pos.column];
    layout.Visit(next_pos);

    NextWord(next_pos, word, layout, legal_words);

    layout.UndoVisit(next_pos);
    word.pop_back();
  }
}

LegalWordsContainer BoggleBlitz::Solve() {
  LegalWordsContainer legal_words;
  std::string word;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      Pos pos{true, i, j};
      word = grid[i][j];
      BoggleBlitzLayout layout(n);
      layout.Visit(pos);
      NextWord(pos, word, layout, legal_words);
    }
  }

  return legal_words;
}
} // namespace uva487

int main() {
  int t, n;
  std::string line;
  std::vector<std::string> grid;

  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    std::cin >> n;
    grid.clear();
    grid.reserve(static_cast<unsigned long>(n));
    for (int j = 0; j < n; ++j) {
      std::cin >> line;
      grid.emplace_back(line);
    }

    auto legal_words = uva487::BoggleBlitz(n, grid).Solve();
    if (i > 0) {
      std::cout << std::endl;
    }

    for (const auto &word : legal_words) {
      std::cout << word << std::endl;
    }
  }

  return 0;
}