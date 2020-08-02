#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

namespace uva_291 {
using NodeId = size_t;

struct Node {
  NodeId id{0};
  bool use_edge{true};

  Node(const NodeId node_id) : id{node_id} {}
};

class PathFinder {
public:
  PathFinder(size_t num_nodes,
             const std::vector<std::pair<NodeId, NodeId>> &edge_list,
             bool is_directed);

  std::vector<std::vector<NodeId>> FindAll(NodeId start_node);

private:
  void Find(NodeId node_id, size_t num_edges_rem, std::vector<NodeId> &tour,
            std::vector<std::vector<NodeId>> &tours);

  const size_t num_nodes_;
  std::vector<std::vector<Node>> adj_list_;
  const std::vector<std::pair<NodeId, NodeId>> &edge_list_;
};

PathFinder::PathFinder(const size_t num_nodes,
                       const std::vector<std::pair<NodeId, NodeId>> &edge_list,
                       const bool is_directed)
    : num_nodes_{num_nodes}, edge_list_{edge_list} {
  adj_list_.resize(num_nodes_);

  for (const auto &[u, v] : edge_list) {
    adj_list_[u].emplace_back(v);
    if (!is_directed) {
      adj_list_[v].emplace_back(u);
    }
  }
}

std::vector<std::vector<NodeId>> PathFinder::FindAll(const NodeId start_node) {
  std::vector<NodeId> tour;
  tour.reserve(num_nodes_);
  std::vector<std::vector<NodeId>> tours;

  tour.emplace_back(start_node);
  Find(start_node, edge_list_.size(), tour, tours);

  std::sort(tours.begin(), tours.end());
  return tours;
}

void PathFinder::Find(const NodeId node_id, const size_t num_edges_rem,
                      std::vector<NodeId> &tour,
                      std::vector<std::vector<NodeId>> &tours) {
  if (num_edges_rem == 0) {
    tours.emplace_back(tour);
    return;
  }

  for (auto &adj_node : adj_list_[node_id]) {
    if (!adj_node.use_edge) {
      continue;
    }

    adj_node.use_edge = false;
    Node *a_node_ptr{nullptr};
    for (auto &a_node : adj_list_[adj_node.id]) {
      if (a_node.id == node_id && a_node.use_edge) {
        a_node_ptr = &a_node;
        a_node.use_edge = false;
        break;
      }
    }

    tour.emplace_back(adj_node.id);
    Find(adj_node.id, num_edges_rem - 1, tour, tours);
    assert(a_node_ptr != nullptr);
    adj_node.use_edge = a_node_ptr->use_edge = true;
    tour.pop_back();
  }
}
} // namespace uva_291

int main(int argc, char *argv[]) {
  std::vector<std::pair<uva_291::NodeId, uva_291::NodeId>> edge_list{
      {1 - 1, 5 - 1}, {5 - 1, 3 - 1}, {3 - 1, 2 - 1}, {2 - 1, 1 - 1},
      {1 - 1, 3 - 1}, {5 - 1, 2 - 1}, {5 - 1, 4 - 1}, {4 - 1, 3 - 1}};

  uva_291::PathFinder path_finder(5, edge_list, false);
  for (const auto &tour : path_finder.FindAll(1 - 1)) {
    for (const auto &node_id : tour) {
      std::cout << node_id + 1;
    }
    std::cout << std::endl;
  }

  return 0;
}
