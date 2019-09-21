// WIP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Node = size_t;

struct UniquePairs {
  UniquePairs(const std::unordered_map<Node, std::string> &idx_node)
      : idx_node_{idx_node} {}

  void Add(Node u, Node v);
  std::vector<std::pair<std::string, std::string>> Get() const {
    return pairs_;
  }

private:
  const std::unordered_map<Node, std::string> &idx_node_;
  std::unordered_set<std::string> unique_;
  std::vector<std::pair<std::string, std::string>> pairs_;
};

class Scheduler {

public:
  Scheduler(const std::vector<std::vector<std::string>> &sequences,
            const std::vector<std::pair<std::string, std::string>> &messages);

  std::vector<std::pair<std::string, std::string>> GetConcurrentEvents();

private:
  size_t num_nodes_{0};
  std::vector<std::vector<int>> adj_matrix_;
  std::unordered_map<Node, std::string> idx_node_;
};

void UniquePairs::Add(const Node u, const Node v) {
  const auto hash =
      std::to_string(std::min(u, v)) + " " + std::to_string(std::max(u, v));
  if (unique_.find(hash) == unique_.end()) {
    unique_.insert(hash);

    const auto find_u_it = idx_node_.find(u);
    assert(find_u_it != idx_node_.end());
    const auto find_v_it = idx_node_.find(v);
    assert(find_v_it != idx_node_.end());
    pairs_.emplace_back(find_u_it->second, find_v_it->second);
  }
}

Scheduler::Scheduler(
    const std::vector<std::vector<std::string>> &sequences,
    const std::vector<std::pair<std::string, std::string>> &messages) {
  size_t index = 0;
  std::unordered_map<std::string, Node> node_idx;
  const auto add_node = [this, &node_idx, &index](const std::string &node) {
    if (node_idx.find(node) == node_idx.end()) {
      node_idx[node] = index;
      idx_node_[index] = node;
      ++index;
    }
  };

  for (const auto &sequence : sequences) {
    for (const auto &node : sequence) {
      add_node(node);
    }
  }
  for (const auto &[u, v] : messages) {
    add_node(u);
    add_node(v);
  }
  num_nodes_ = node_idx.size();

  adj_matrix_.resize(num_nodes_, std::vector<int>(num_nodes_));
  for (const auto &sequence : sequences) {
    if (sequence.size() < 2) {
      continue;
    }
    for (size_t i = 1, len = sequence.size(); i < len; ++i) {
      const auto u = node_idx[sequence[i - 1]];
      const auto v = node_idx[sequence[i]];
      adj_matrix_[u][v] = 1;
    }
  }
  for (const auto &message : messages) {
    const auto u = node_idx[message.first];
    const auto v = node_idx[message.second];
    adj_matrix_[u][v] = 1;
  }
}

std::vector<std::pair<std::string, std::string>>
Scheduler::GetConcurrentEvents() {
  for (Node k = 0; k < num_nodes_; ++k) {
    for (Node i = 0; i < num_nodes_; ++i) {
      for (Node j = 0; j < num_nodes_; ++j) {
        adj_matrix_[i][j] |= adj_matrix_[i][k] & adj_matrix_[k][j];
      }
    }
  }

  UniquePairs unique_pairs(idx_node_);
  for (Node i = 0; i < num_nodes_; ++i) {
    for (Node j = 0; j < num_nodes_; ++j) {
      if (i != j && adj_matrix_[i][j] == 0) {
        unique_pairs.Add(i, j);
      }
    }
  }
  return unique_pairs.Get();
}

int main(int argc, char *argv[]) {
  size_t num_sequences, sequence_len, num_messages, t = 0;
  std::vector<std::vector<std::string>> sequences;
  std::vector<std::pair<std::string, std::string>> messages;

  while (std::cin >> num_sequences, num_sequences != 0) {
    sequences.resize(num_sequences);
    for (size_t i = 0; i < num_sequences; ++i) {
      std::cin >> sequence_len;
      sequences[i].resize(sequence_len);
      for (size_t j = 0; j < sequence_len; ++j) {
        std::cin >> sequences[i][j];
      }
    }

    std::cin >> num_messages;
    messages.resize(num_messages);
    for (size_t i = 0; i < num_messages; ++i) {
      std::cin >> messages[i].first >> messages[i].second;
    }

    std::cout << "Case " << ++t << ", ";

    auto concurrent_events =
        Scheduler(sequences, messages).GetConcurrentEvents();
    if (concurrent_events.empty()) {
      std::cout << "no concurrent events." << std::endl;
    } else {
      std::cout << concurrent_events.size()
                << " concurrent events:" << std::endl;
      auto separator = "";
      auto num_concurrent_events = 0;
      for (const auto &[e1, e2] : concurrent_events) {
        std::cout << separator << '(' << e1 << ',' << e2 << ')';
        separator = " ";
        ++num_concurrent_events;
        if (num_concurrent_events >= 2) {
          break;
        }
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
