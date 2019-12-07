#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lc_269 {
class Graph {
  enum class NodeState { kUnvisited, kExplored, kVisited };

public:
  explicit Graph(const std::vector<std::string> &words);

  [[nodiscard]] std::string GetAlphabets() const;

private:
  [[nodiscard]] bool HasCycle() const;
  bool HasCycle(char node, std::unordered_map<char, NodeState> &state) const;
  [[nodiscard]] std::string TopologicalSort() const;
  void DFS(char node, std::string &order,
           std::unordered_set<char> &visited) const;

  const std::vector<std::string> &words_;
  std::unordered_map<char, std::unordered_set<char>> adj_list_;
  std::unordered_set<char> all_nodes_;
};

Graph::Graph(const std::vector<std::string> &words) : words_{words} {
  const auto add_links = [this](const std::string &word) {
    for (size_t i = 1, len = word.size(); i < len; ++i) {
      if (word[i - 1] != word[i]) {
        adj_list_[word[i - 1]].insert(word[i]);
      }
    }
  };

  for (size_t i = 1, len = words_.size(); i < len; ++i) {
    const auto &first = words_[i - 1];
    const auto &second = words_[i];

    for (size_t j = 0, word_len = std::min(first.size(), second.size());
         j < word_len; ++j) {
      if (first[j] != second[j]) {
        adj_list_[first[j]].insert(second[j]);
        break;
      }
    }
  }

  for (const auto &word : words_) {
    for (const auto &c : word) {
      all_nodes_.insert(c);
    }
  }
  std::unordered_set<char> all_nodes;
  all_nodes.reserve(all_nodes_.size());
  for (const auto node : all_nodes_) {
    all_nodes.insert(node);
  }
  // This is very important. Need to add a dummy start node
  // Otherwise, the topological sorting won't contain all the nodes
  adj_list_.emplace('\0', all_nodes);
}

std::string Graph::GetAlphabets() const {
  if (HasCycle()) {
    return "";
  }
  return TopologicalSort();
}

bool Graph::HasCycle() const {
  std::unordered_map<char, NodeState> state;
  for (const auto &node : all_nodes_) {
    state[node] = NodeState::kUnvisited;
  }

  for (const auto &node : all_nodes_) {
    if (state[node] == NodeState::kUnvisited && HasCycle(node, state)) {
      return true;
    }
  }
  return false;
}

bool Graph::HasCycle(const char node,
                     std::unordered_map<char, NodeState> &state) const {
  if (state[node] == NodeState::kVisited) {
    return false;
  }

  state[node] = NodeState::kExplored;

  const auto find_it = adj_list_.find(node);
  if (find_it != adj_list_.end()) {
    for (const auto &adj_node : find_it->second) {
      if (state[adj_node] == NodeState::kUnvisited) {
        if (HasCycle(adj_node, state)) {
          return true;
        }
      } else if (state[adj_node] == NodeState::kExplored) {
        return true;
      }
    }
  }

  state[node] = NodeState::kVisited;
  return false;
}

std::string Graph::TopologicalSort() const {
  std::string order;
  std::unordered_set<char> visited;
  DFS('\0', order, visited);
  order.pop_back();
  std::reverse(order.begin(), order.end());
  return order;
}

void Graph::DFS(const char node, std::string &order,
                std::unordered_set<char> &visited) const {
  visited.insert(node);
  auto find_it = adj_list_.find(node);
  if (find_it != adj_list_.end()) {
    for (const auto &adj_node : find_it->second) {
      if (visited.find(adj_node) == visited.end()) {
        DFS(adj_node, order, visited);
      }
    }
  }
  order.push_back(node);
}
} // namespace lc_269

class Solution {
public:
  std::string alienOrder(std::vector<std::string> &words);
};

std::string Solution::alienOrder(std::vector<std::string> &words) {
  return lc_269::Graph(words).GetAlphabets();
}

int main(int argc, char *argv[]) {
  // std::vector<std::string> words{"wrt", "wrf", "er", "ett", "rftt"};
  std::vector<std::string> words{"ab", "adc"};
  std::cout << Solution().alienOrder(words) << std::endl;
  return 0;
}
