#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace uva_429 {
const auto infinity = std::numeric_limits<int>::max();

class WordNet {
public:
  explicit WordNet(const std::vector<std::string> &words);

  int ShortestPath(const std::string &start_word,
                   const std::string &end_word) const;

private:
  static bool IsEditDistance1(const std::string &a, const std::string &b);
  int BFS(size_t start_node, size_t end_node) const;

  const std::vector<std::string> &words_;
  std::vector<std::vector<size_t>> adj_list_;
};

WordNet::WordNet(const std::vector<std::string> &words) : words_(words) {
  const auto len = words_.size();
  adj_list_.resize(len);

  for (size_t i = 0; i < len; ++i) {
    for (auto j = i + 1; j < len; ++j) {
      if (IsEditDistance1(words_[i], words_[j])) {
        adj_list_[i].emplace_back(j);
        adj_list_[j].emplace_back(i);
      }
    }
  }
}

int WordNet::ShortestPath(const std::string &start_word,
                          const std::string &end_word) const {
  const auto start_word_it =
      std::find(words_.begin(), words_.end(), start_word);
  assert(start_word_it != words_.end());

  const auto end_word_it = std::find(words_.begin(), words_.end(), end_word);
  assert(end_word_it != words_.end());
  return BFS(std::distance(words_.begin(), start_word_it),
             std::distance(words_.begin(), end_word_it));
}

bool WordNet::IsEditDistance1(const std::string &a, const std::string &b) {
  if (a.size() != b.size()) {
    return false;
  }

  auto tolerate = true;
  for (size_t i = 0, len = a.size(); i < len; ++i) {
    if (a[i] == b[i]) {
      continue;
    }
    if (tolerate) {
      tolerate = false;
      continue;
    }
    return false;
  }
  return !tolerate;
}

int WordNet::BFS(const size_t start_node, const size_t end_node) const {
  std::queue<size_t> order;
  order.push(start_node);

  std::vector<int> visited(words_.size(), infinity);
  visited[start_node] = 0;

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    for (const auto adj_node : adj_list_[node]) {
      if (visited[adj_node] != infinity) {
        continue;
      }

      visited[adj_node] = visited[node] + 1;
      order.push(adj_node);
    }
  }
  return visited[end_node];
}
} // namespace uva_429

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t = 0, c = 0;
  std::string line;
  std::string word;
  std::string start_word;
  std::string end_word;

  std::getline(std::cin, line);
  std::istringstream t_tokenizer(line);
  t_tokenizer >> t;

  std::getline(std::cin, line);
  while (t--) {
    std::vector<std::string> words;
    while (std::getline(std::cin, line), line.front() != '*') {
      std::istringstream word_tokenizer(line);
      word_tokenizer >> word;
      words.emplace_back(word);
    }

    if (c++ > 0) {
      std::cout << std::endl;
    }

    while (true) {
      std::getline(std::cin, line);
      if (line.empty() || line.front() == '\n' || line.front() == '\r') {
        break;
      }

      std::istringstream word_tokenizer(line);
      word_tokenizer >> start_word >> end_word;
      std::cout << line << ' '
                << uva_429::WordNet(words).ShortestPath(start_word, end_word)
                << std::endl;
    }
  }
  return 0;
}
