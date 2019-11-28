// WA

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
public:
  Graph(std::vector<std::string> &words1, std::vector<std::string> &words2,
        std::vector<std::vector<std::string>> &pairs);

  bool IsSimilar() const;

private:
  bool DFS(size_t node, const std::unordered_set<size_t> &target_nodes,
           std::vector<int> &visited) const;
  std::vector<size_t> GetIntersection() const;

  size_t num_nodes_{0};
  std::unordered_map<std::string, size_t> word_index_;
  std::unordered_set<size_t> words1_indices_;
  std::unordered_set<size_t> words2_indices_;
  const std::vector<std::string> &words1_;
  const std::vector<std::string> &words2_;
  const std::vector<std::vector<std::string>> &pairs_;
  std::vector<std::vector<size_t>> adj_list_;
};

class Solution {
public:
  bool areSentencesSimilarTwo(std::vector<std::string> &words1,
                              std::vector<std::string> &words2,
                              std::vector<std::vector<std::string>> &pairs);
};

Graph::Graph(std::vector<std::string> &words1, std::vector<std::string> &words2,
             std::vector<std::vector<std::string>> &pairs)
    : words1_{words1}, words2_{words2}, pairs_{pairs} {
  for (const auto &word : words1) {
    if (word_index_.find(word) == word_index_.end()) {
      word_index_[word] = num_nodes_;
      words1_indices_.insert(num_nodes_++);
    }
  }
  for (const auto &word : words2) {
    if (word_index_.find(word) == word_index_.end()) {
      word_index_[word] = num_nodes_;
      words2_indices_.insert(num_nodes_++);
    }
  }

  for (const auto &words : pairs) {
    for (const auto &word : words) {
      if (word_index_.find(word) == word_index_.end()) {
        word_index_[word] = num_nodes_++;
      }
    }
  }

  adj_list_.resize(num_nodes_);
  for (const auto &words : pairs) {
    auto u = word_index_[words.front()];
    auto v = word_index_[words.back()];
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);
  }

  for (const auto &index : GetIntersection()) {
    words1_indices_.erase(index);
    words2_indices_.erase(index);
  }
}

bool Graph::IsSimilar() const {
  if (words1_.size() != words2_.size()) {
    return false;
  }
  {
    std::vector<int> visited(num_nodes_);
    for (const auto index : words1_indices_) {
      if (!DFS(index, words2_indices_, visited)) {
        return false;
      }
    }
  }

  {
    std::vector<int> visited(num_nodes_);
    for (const auto &index : words2_indices_) {
      if (!DFS(index, words1_indices_, visited)) {
        return false;
      }
    }
  }
  return true;
}

bool Graph::DFS(const size_t node,
                const std::unordered_set<size_t> &target_nodes,
                std::vector<int> &visited) const {
  visited[node] = 1;
  if (target_nodes.find(node) != target_nodes.end()) {
    return true;
  }

  for (const auto &adj_node : adj_list_[node]) {
    if (visited[adj_node] == 0 && DFS(adj_node, target_nodes, visited)) {
      return true;
    }
  }
  return false;
}

std::vector<size_t> Graph::GetIntersection() const {
  std::vector<size_t> intersection;
  for (const auto &index : words2_indices_) {
    if (words1_indices_.find(index) != words1_indices_.end()) {
      intersection.emplace_back(index);
    }
  }
  return intersection;
}

bool Solution::areSentencesSimilarTwo(
    std::vector<std::string> &words1, std::vector<std::string> &words2,
    std::vector<std::vector<std::string>> &pairs) {
  return Graph(words1, words2, pairs).IsSimilar();
}

int main(int argc, char *argv[]) {}
