// WA

#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Graph {
public:
  Graph(const std::string &s1, const std::string &s2);

  bool CanConvert() const;

private:
  bool HasMultipleOutgoingEdges() const;
  bool HasCycle() const;
  bool HasCycle(char node, std::unordered_set<char> &stack) const;

  const std::string &s1_;
  const std::string &s2_;
  std::unordered_map<char, std::unordered_set<char>> adj_list_;
};

class Solution {
public:
  bool canConvert(std::string str1, std::string str2);
};

Graph::Graph(const std::string &s1, const std::string &s2) : s1_{s1}, s2_{s2} {
  for (size_t i = 0, len = s1.size(); i < len; ++i) {
    if (s1_[i] != s2_[i]) {
      adj_list_[s1_[i]].insert(s2_[i]);
    }
  }
}

bool Graph::CanConvert() const {
  if (HasCycle() && adj_list_.size() >= 26) {
    return false;
  }
  return !HasMultipleOutgoingEdges();
}

bool Solution::canConvert(std::string str1, std::string str2) {
  return Graph(str1, str2).CanConvert();
}

bool Graph::HasMultipleOutgoingEdges() const {
  std::unordered_map<char, char> adj_list;
  for (size_t i = 0, len = s1_.size(); i < len; ++i) {
    auto find_it = adj_list.find(s1_[i]);
    if (find_it == adj_list.end()) {
      adj_list[s1_[i]] = s2_[i];
    } else if (find_it->second != s2_[i]) {
      return true;
    }
  }
  return false;
}

bool Graph::HasCycle() const {
  std::unordered_set<char> stack;
  for (const auto &[u, _] : adj_list_) {
    stack.clear();
    if (HasCycle(u, stack)) {
      return true;
    }
  }
  return false;
}

bool Graph::HasCycle(const char node, std::unordered_set<char> &stack) const {
  if (stack.find(node) != stack.end()) {
    return true;
  }

  auto find_it = adj_list_.find(node);
  if (find_it == adj_list_.end()) {
    return false;
  }

  stack.insert(node);
  for (const auto &adj_node : find_it->second) {
    if (HasCycle(adj_node, stack)) {
      return true;
    }
  }
  stack.erase(node);
  return false;
}

int main(int argc, char *argv[]) {
  std::cout << Solution().canConvert("aabcc", "ccdee") << std::endl;
  std::cout << Solution().canConvert("leetcode", "codeleet") << std::endl;
  std::cout << Solution().canConvert("abcdefghijklmnopqrstuvwxyz",
                                     "bcdefghijklmnopqrstuvwxyza")
            << std::endl;
  return 0;
}
