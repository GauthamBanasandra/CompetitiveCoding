#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <ostream>
#include <unordered_set>
#include <utility>
#include <vector>

namespace round_435 {
using Node = size_t;
using EdgeList = std::vector<std::pair<Node, Node>>;

class Graph {
public:
  Graph(size_t num_nodes, const EdgeList &edge_list);

  [[nodiscard]] size_t GetMaxConnectingEdges() const {
    return std::max(GetMaxConnectingEdges(1), GetMaxConnectingEdges(0));
  }

private:
  [[nodiscard]] size_t GetMaxConnectingEdges(int init_colour) const;
  [[nodiscard]] std::pair<std::unordered_set<Node>, std::unordered_set<Node>>
  Partition(int init_colour) const;
  void Partition(Node node, std::vector<int> &colour,
                 std::vector<int> &visited) const;

  const size_t num_nodes_;
  std::vector<std::unordered_set<Node>> adj_list_;
};

Graph::Graph(const size_t num_nodes, const EdgeList &edge_list)
    : num_nodes_(num_nodes) {
  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list) {
    adj_list_[u - 1].insert(v - 1);
    adj_list_[v - 1].insert(u - 1);
  }
}

size_t Graph::GetMaxConnectingEdges(const int init_colour) const {
  size_t edges = 0;
  auto [partition1, partition2] = Partition(init_colour);
  for (const auto &node : partition1) {
    // This is the key to solving this problem
    // The idea is that, we first partition the graph into a bipartite graph and
    // we have the 2 partitions as 2 unordered sets
    // Here's the reasoning for the below assertion - since the graph is a
    // bipartite graph, it would imply that the adjacent nodes must belong to
    // the other set. The size of this set must be less than the other partition
    // as there could exist other nodes which need not be adjacent to the node
    // and yet part of the other partition
    // In other words, the adjacent nodes are only a subset of the other
    // partition
    assert(partition2.size() >= adj_list_[node].size());
    edges += partition2.size() - adj_list_[node].size();
  }
  return edges;
}

std::pair<std::unordered_set<Node>, std::unordered_set<Node>>
Graph::Partition(const int init_colour) const {
  std::vector<int> visited(num_nodes_);
  std::vector<int> colour(num_nodes_);
  colour[0] = init_colour;

  Partition(0, colour, visited);

  std::unordered_set<Node> partition1, partition2;
  for (Node node = 0; node < num_nodes_; ++node) {
    (colour[node] == 1 ? partition1 : partition2).insert(node);
  }
  return std::make_pair(std::move(partition1), std::move(partition2));
}

void Graph::Partition(const Node node, std::vector<int> &colour,
                      std::vector<int> &visited) const {
  if (visited[node] == 1) {
    return;
  }
  visited[node] = 1;

  for (const auto &adj_node : adj_list_[node]) {
    if (visited[adj_node] == 0) {
      colour[adj_node] = 1 - colour[node];
      Partition(adj_node, colour, visited);
    }
  }
}
} // namespace round_435

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t n;
  round_435::EdgeList edge_list;

  std::cin >> n;
  edge_list.resize(n - 1);
  for (size_t i = 0; i < n - 1; ++i) {
    std::cin >> edge_list[i].first >> edge_list[i].second;
  }

  std::cout << round_435::Graph(n, edge_list).GetMaxConnectingEdges()
            << std::endl;
  return 0;
}
