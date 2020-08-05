#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <list>
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace uva_10054 {
using NodeId = size_t;
using Edge = std::pair<NodeId, NodeId>;
using EdgeList = std::vector<Edge>;

struct Node {
  NodeId id{0};
  bool use_edge{true};

  explicit Node(const NodeId node_id) : id{node_id} {}
};

class PathFinder {
  using AdjacencyList = std::unordered_map<NodeId, std::vector<Node>>;

public:
  PathFinder(const EdgeList &edge_list);

  std::list<Edge> FindEulerian();

private:
  void Find(NodeId node_id, std::list<Edge> &tour,
            const std::list<Edge>::iterator &tour_it);

  std::unordered_map<NodeId, size_t> in_degree_;
  AdjacencyList adj_list_;
  const EdgeList &edge_list_;
};

PathFinder::PathFinder(const EdgeList &edge_list) : edge_list_{edge_list} {
  for (const auto &[u, v] : edge_list_) {
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);

    ++in_degree_[u];
    ++in_degree_[v];
  }
}

std::list<Edge> PathFinder::FindEulerian() {
  const auto num_odd_degree_nodes = std::count_if(
      in_degree_.begin(), in_degree_.end(),
      [](const std::pair<const NodeId, size_t> &node_id_in_degree) -> bool {
        return (node_id_in_degree.second & 1) == 1;
      });
  if (num_odd_degree_nodes != 0) {
    return {};
  }

  const auto start_node = edge_list_.front().first;
  std::list<Edge> tour;
  Find(start_node, tour, tour.begin());

  if (tour.size() != edge_list_.size()) {
    return {};
  }

  std::reverse(tour.begin(), tour.end());
  return tour;
}

void PathFinder::Find(NodeId node_id, std::list<Edge> &tour,
                      const std::list<Edge>::iterator &tour_it) {
  for (auto &adj_node : adj_list_.at(node_id)) {
    if (!adj_node.use_edge) {
      continue;
    }
    adj_node.use_edge = false;

    for (auto &a_node : adj_list_.at(adj_node.id)) {
      if (a_node.id == node_id && a_node.use_edge) {
        a_node.use_edge = false;
        break;
      }
    }

    Find(adj_node.id, tour, tour.emplace(tour_it, node_id, adj_node.id));
  }
}
} // namespace uva_10054

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t{0};
  size_t num_beads{0};
  uva_10054::EdgeList beads;

  std::cin >> t;
  for (size_t case_num = 1; case_num <= t; ++case_num) {
    std::cin >> num_beads;
    beads.resize(num_beads);

    for (size_t i = 0; i < num_beads; ++i) {
      std::cin >> beads[i].first >> beads[i].second;
    }

    if (case_num > 1) {
      std::cout << std::endl;
    }
    uva_10054::PathFinder path_finder(beads);
    auto path = path_finder.FindEulerian();

    std::cout << "Case #" << case_num << std::endl;
    for (const auto &[u, v] : path) {
      std::cout << u << ' ' << v << std::endl;
    }

    if (path.empty()) {
      std::cout << "some beads may be lost" << std::endl;
    }
  }

  return 0;
}
