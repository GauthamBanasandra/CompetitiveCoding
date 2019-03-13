//
// Created by gauth on 11-03-2018.
//

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

void Print(const std::unordered_map<int, std::unordered_set<int>> &graph);

inline std::string GetHash(int a, int b) {
  return a < b ? std::to_string(a) + " " + std::to_string(b) : std::to_string(b) + " " + std::to_string(a);
}

inline bool Visited(const std::unordered_set<std::string> &visited_edges, int a, int b) {
  return visited_edges.find(GetHash(a, b)) != visited_edges.end();
}

inline void AddVisit(std::unordered_set<std::string> &visited_edges, int a, int b) {
  visited_edges.insert(GetHash(a, b));
}

inline void RemoveVisit(std::unordered_set<std::string> &visited_edges, int a, int b) {
  visited_edges.erase(GetHash(a, b));
}

int MaxPathLength(std::unordered_map<int, std::unordered_set<int>> &graph,
                  std::unordered_set<std::string> &visited_edges,
                  int p) {
  int max_length = 0;
  for (const auto &n : graph[p]) {
    if (!Visited(visited_edges, n, p)) {
      AddVisit(visited_edges, n, p);
      max_length = std::max(max_length, MaxPathLength(graph, visited_edges, n) + 1);
      RemoveVisit(visited_edges, n, p);
    }
  }

  return max_length;
}

int MaxPathLength(std::unordered_map<int, std::unordered_set<int>> &graph) {
  int max_length = 0;
  for (const auto &p : graph) {
    std::unordered_set<std::string> visited_edges;
    max_length = std::max(max_length, MaxPathLength(graph, visited_edges, p.first));
  }

  return max_length;
}

int main() {
  int n, m, a, b;
  std::unordered_map<int, std::unordered_set<int>> graph;

  while (std::cin >> n >> m, n && m) {
    graph.clear();
    for (int i = 0; i < m; ++i) {
      std::cin >> a >> b;
      graph[a].insert(b);
      graph[b].insert(a);
    }

    std::cout << MaxPathLength(graph) << std::endl;
  }

  return 0;
}