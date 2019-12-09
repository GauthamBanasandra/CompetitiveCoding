// TLE

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace lc_212 {
class CrossWord {
public:
  CrossWord(const std::vector<std::vector<char>> &board,
            const std::vector<std::string> &words);

  [[nodiscard]] std::vector<std::string> GetMatchingWords() const;

private:
  static int GetHash(const int i, const int j) { return i * 10 + j; }
  bool Match(const std::string &word, size_t i, int row, int col,
             std::unordered_set<int> &used) const;

  [[nodiscard]] bool IsOutside(const int r, const int c) const {
    return r < 0 || r >= num_rows_ || c < 0 || c >= num_cols_;
  }

  const std::vector<std::vector<char>> &board_;
  const std::vector<std::string> &words_;
  std::unordered_map<char, std::vector<std::pair<int, int>>> letter_idx_;
  int num_rows_{0};
  int num_cols_{0};
  std::vector<std::pair<int, int>> directions_{
      {0, 1}, {1, 0}, {-1, 0}, {0, -1}};
};

CrossWord::CrossWord(const std::vector<std::vector<char>> &board,
                     const std::vector<std::string> &words)
    : board_{board}, words_{words} {
  num_rows_ = board_.size();
  num_cols_ = board_.front().size();

  for (auto i = 0; i < num_rows_; ++i) {
    for (auto j = 0; j < num_cols_; ++j) {
      letter_idx_[board_[i][j]].emplace_back(i, j);
    }
  }
}

std::vector<std::string> CrossWord::GetMatchingWords() const {
  std::vector<std::string> matching_words;
  for (const auto &word : words_) {
    auto find_it = letter_idx_.find(word.front());
    if (find_it == letter_idx_.end()) {
      continue;
    }
    for (const auto &[row, col] : find_it->second) {
      std::unordered_set<int> used;
      used.insert(GetHash(row, col));
      if (Match(word, 1, row, col, used)) {
        matching_words.emplace_back(word);
        break;
      }
    }
  }
  return matching_words;
}

bool CrossWord::Match(const std::string &word, const size_t i, const int row,
                      const int col, std::unordered_set<int> &used) const {
  if (i == word.size()) {
    return true;
  }

  for (auto [r, c] : directions_) {
    r += row;
    c += col;
    auto hash = GetHash(r, c);
    if (IsOutside(r, c) || used.find(hash) != used.end() ||
        board_[r][c] != word[i]) {
      continue;
    }
    used.insert(hash);
    if (Match(word, i + 1, r, c, used)) {
      return true;
    }
    used.erase(hash);
  }
  return false;
}
} // namespace lc_212

class Solution {
public:
  std::vector<std::string> findWords(std::vector<std::vector<char>> &board,
                                     std::vector<std::string> &words);
};

std::vector<std::string>
Solution::findWords(std::vector<std::vector<char>> &board,
                    std::vector<std::string> &words) {
  return lc_212::CrossWord(board, words).GetMatchingWords();
}

int main(int argc, char *argv[]) { return 0; }
