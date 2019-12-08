#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace lc_720 {
struct Node {
  Node() { next.resize(range, nullptr); }

  const size_t range = 26;
  size_t value{0};
  std::vector<Node *> next;
};

class Trie {
public:
  void Put(const std::string &key, size_t value);
  [[nodiscard]] std::string GetLongestIncrementalKey() const;

private:
  Node *Put(Node *node, const std::string &key, size_t value,
            size_t depth) const;
  void GetLongestIncrementalKey(Node *node, std::string &prefix,
                                std::string &longest_prefix) const;

  Node *root_{new Node};
};

void Trie::Put(const std::string &key, const size_t value) {
  root_ = Put(root_, key, value, 0);
}

std::string Trie::GetLongestIncrementalKey() const {
  std::string prefix;
  std::string longest_prefix;
  for (auto i = 0; i < 26; ++i) {
    prefix.push_back(i + 'a');
    GetLongestIncrementalKey(root_->next[i], prefix, longest_prefix);
    prefix.pop_back();
  }
  return longest_prefix;
}

Node *Trie::Put(Node *node, const std::string &key, const size_t value,
                const size_t depth) const {
  if (node == nullptr) {
    node = new Node;
  }
  if (depth == key.size()) {
    node->value = value;
    return node;
  }
  const auto c = key[depth] - 'a';
  node->next[c] = Put(node->next[c], key, value, depth + 1);
  return node;
}

void Trie::GetLongestIncrementalKey(Node *node, std::string &prefix,
                                    std::string &longest_prefix) const {
  if (node == nullptr || node->value == 0) {
    return;
  }
  if (prefix.size() > longest_prefix.size() ||
      prefix.size() == longest_prefix.size() && prefix < longest_prefix) {
    longest_prefix = prefix;
  }
  for (auto i = 0; i < 26; ++i) {
    prefix.push_back(i + 'a');
    GetLongestIncrementalKey(node->next[i], prefix, longest_prefix);
    prefix.pop_back();
  }
}
} // namespace lc_720

class Solution {
public:
  std::string longestWord(std::vector<std::string> &words);
};

std::string Solution::longestWord(std::vector<std::string> &words) {
  lc_720::Trie trie;
  for (const auto &word : words) {
    trie.Put(word, word.size());
  }
  return trie.GetLongestIncrementalKey();
}

int main(int argc, char *argv[]) {
  std::vector<std::string> words{"a",  "banana", "app",  "appl",
                                 "ap", "apply",  "apple"};
  std::cout << Solution().longestWord(words) << std::endl;
  return 0;
}
