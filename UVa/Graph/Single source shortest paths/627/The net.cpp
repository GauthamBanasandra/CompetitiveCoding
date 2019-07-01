#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace uva_627 {
const auto infinity = std::numeric_limits<int>::max();

class RouterNet {
public:
  explicit RouterNet(const size_t num_nodes,
                     const std::vector<std::vector<size_t>> &adj_list)
      : num_nodes_(num_nodes), adj_list_(adj_list) {}

  std::vector<size_t> GetShortestPath(size_t start_node, size_t end_node) const;

private:
  std::pair<bool, std::vector<size_t>> BFS(size_t start_node,
                                           size_t end_node) const;

  const size_t num_nodes_;
  const std::vector<std::vector<size_t>> &adj_list_;
};

std::vector<size_t> RouterNet::GetShortestPath(const size_t start_node,
                                               const size_t end_node) const {
  auto [is_reachable, parent] = BFS(start_node, end_node);

  std::vector<size_t> path;
  if (!is_reachable) {
    return path;
  }

  for (auto node = end_node; node != start_node; node = parent[node]) {
    path.emplace_back(node);
  }
  path.emplace_back(start_node);
  std::reverse(path.begin(), path.end());
  return path;
}

std::pair<bool, std::vector<size_t>>
RouterNet::BFS(const size_t start_node, const size_t end_node) const {
  std::vector<size_t> parent(num_nodes_);
  std::vector<int> visited(num_nodes_, infinity);

  std::queue<size_t> order;
  order.push(start_node);
  visited[start_node] = 0;
  parent[start_node] = start_node;

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    for (const auto adj_node : adj_list_[node]) {
      if (visited[adj_node] == infinity) {
        order.push(adj_node);
        visited[adj_node] = visited[node] + 1;
        parent[adj_node] = node;
        // Update the parent of adj_node only if it has been visited and visit
        // order of current node is lower
      } else if (visited[node] < visited[adj_node] && node < parent[adj_node]) {
        parent[adj_node] = node;
      }
    }
  }
  return {visited[end_node] != infinity, parent};
}
} // namespace uva_627

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_nodes, node, adj_node, num_queries, start_node, end_node;
  char delimiter;
  std::string line;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    std::istringstream num_nodes_tokenizer(line);
    num_nodes_tokenizer >> num_nodes;
    ++num_nodes;

    std::vector<std::vector<size_t>> adj_list;
    adj_list.resize(num_nodes);

    for (size_t i = 0; i < num_nodes - 1; ++i) {
      std::getline(std::cin, line);
      std::istringstream node_tokenizer(line);
      node_tokenizer >> node;
      while (node_tokenizer >> delimiter >> adj_node) {
        adj_list[node].emplace_back(adj_node);
      }
    }

    uva_627::RouterNet network(num_nodes, adj_list);

    std::getline(std::cin, line);
    std::istringstream num_queries_tokenizer(line);
    num_queries_tokenizer >> num_queries;

    std::cout << "-----" << std::endl;
    for (size_t i = 0; i < num_queries; ++i) {
      std::getline(std::cin, line);
      std::istringstream node_tokenizer(line);
      node_tokenizer >> start_node >> end_node;

      auto path = network.GetShortestPath(start_node, end_node);
      if (path.empty()) {
        std::cout << "connection impossible" << std::endl;
      } else {
        auto separator = "";
        for (const auto n : path) {
          std::cout << separator << n;
          separator = " ";
        }
        std::cout << std::endl;
      }
    }
  }
  return 0;
}
