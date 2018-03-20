//
// Created by gauth on 19-03-2018.
//

#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using ul = unsigned long;
using AdjacencyList = std::unordered_map<int, std::vector<int>>;

void Print(const AdjacencyList &adj_list);

namespace unique_edge {
class GapHash {
 public:
  std::size_t static Hash(const std::pair<ul, ul> &k) {
    return k.first > k.second ? k.first * 10000 + k.second : k.second * 10000 + k.first;
  }

  std::size_t operator()(const std::pair<ul, ul> &k) const {
    return Hash(k);
  }
};

struct GapHashEquality {
  bool operator()(const std::pair<std::size_t, std::size_t> &lhs,
                  const std::pair<std::size_t, std::size_t> &rhs) const {
    return GapHash::Hash(lhs) == GapHash::Hash(rhs);
  }
};

using Edge = std::pair<int, int>;
using WalkEdges = std::unordered_map<Edge, int, GapHash, GapHashEquality>;

class Graph {
 public:
  Graph(int max_walk_length, AdjacencyList adj_list)
      : max_walk_length(max_walk_length), adj_list(std::move(adj_list)) {}

  std::vector<std::string> Walk();

  int max_walk_length;
  AdjacencyList adj_list;

 private:
  bool IsVisited(const Edge &edge, const WalkEdges &walk_edges);
  void Walk(int walk_length, int node, WalkEdges &walk_edges, std::vector<std::string> &n_walks);
  void AddVisit(const Edge &edge, WalkEdges &walk_edges, int walk_sequence);
  void RemoveVisit(const Edge &edge, WalkEdges &walk_edges);
  void CollectWalk(const WalkEdges &walk_edges, std::vector<std::string> &n_walks);
};

void Graph::Walk(int walk_length, int node, WalkEdges &walk_edges, std::vector<std::string> &n_walks) {
  if (walk_length == max_walk_length) {
    CollectWalk(walk_edges, n_walks);
    return;
  }

  for (const auto n : adj_list[node]) {
    auto edge = std::make_pair(node, n);
    if (IsVisited(edge, walk_edges)) {
      continue;
    }

    AddVisit(edge, walk_edges, walk_length);
    Walk(walk_length + 1, n, walk_edges, n_walks);
    RemoveVisit(edge, walk_edges);
  }
}

bool Graph::IsVisited(const Edge &edge, const WalkEdges &walk_edges) {
  return walk_edges.find(edge) != walk_edges.end();
}

void Graph::AddVisit(const Edge &edge, WalkEdges &walk_edges, int walk_sequence) {
  walk_edges[edge] = walk_sequence;
}

void Graph::RemoveVisit(const Edge &edge, WalkEdges &walk_edges) {
  walk_edges.erase(edge);
}

std::vector<std::string> Graph::Walk() {
  std::vector<std::string> walk_n;
  WalkEdges walk_edges;

  Walk(0, 1, walk_edges, walk_n);
  std::sort(walk_n.begin(), walk_n.end());

  return walk_n;
}

void Graph::CollectWalk(const WalkEdges &walk_edges, std::vector<std::string> &n_walks) {
  std::vector<int> walk_sequence(max_walk_length + 1, 0);
  for (const auto &k : walk_edges) {
    if (k.second == 0) {
      walk_sequence[k.second] = k.first.first;
    }

    walk_sequence[k.second + 1] = k.first.second;
  }

  std::string walk_str = "(";
  for (const auto seq : walk_sequence) {
    walk_str += std::to_string(seq) + ",";
  }

  walk_str[walk_str.length() - 1] = ')';
  n_walks.emplace_back(walk_str);
}
};

int main() {
  AdjacencyList adj_list;
  int n_nodes, max_walk_len, x;
  std::string line;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    std::istringstream tokenizer(line);
    tokenizer >> n_nodes >> max_walk_len;
    adj_list.clear();

    for (auto i = 1; i <= n_nodes; ++i) {
      std::getline(std::cin, line);
      std::istringstream row_tokenizer(line);
      for (auto j = 1; j <= n_nodes; ++j) {
        row_tokenizer >> x;
        if (x) {
          adj_list[i].emplace_back(j);
        }
      }
    }

    if (max_walk_len >= 5) {
      std::cout << "no walk of length " << max_walk_len << std::endl << std::endl;
      std::getline(std::cin, line);
      continue;
    }

    unique_edge::Graph graph(max_walk_len, adj_list);
    auto unique_n_walks = graph.Walk();
    if (unique_n_walks.empty()) {
      std::cout << "no walk of length " << max_walk_len << std::endl;
    } else {
      for (const auto &walk : unique_n_walks) {
        std::cout << walk << std::endl;
      }
    }

    std::cout << std::endl;
    std::getline(std::cin, line);
  }

  return 0;
}