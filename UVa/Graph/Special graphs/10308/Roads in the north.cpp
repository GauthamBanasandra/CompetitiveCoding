#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace uva_10308 {
using Distance = int;
using Node = size_t;
using EdgeList = std::vector<std::tuple<Node, Node, Distance>>;

class Explorer {
public:
  Explorer(size_t num_nodes, const EdgeList &edge_list);

  Distance GetDiameter() const;

private:
  std::pair<Node, Distance> GetFarthestNode(Node source) const;

  const size_t num_nodes_;
  const Node any_node_{1};
  std::vector<std::vector<std::pair<Node, Distance>>> adj_list_;
};

Explorer::Explorer(size_t num_nodes, const EdgeList &edge_list)
    : num_nodes_{num_nodes} {
  adj_list_.resize(num_nodes_);

  for (const auto &[u, v, distance] : edge_list) {
    adj_list_[u].emplace_back(v, distance);
    adj_list_[v].emplace_back(u, distance);
  }
}

Distance Explorer::GetDiameter() const {
  auto [x, _] = GetFarthestNode(any_node_);
  auto [y, diameter] = GetFarthestNode(x);
  return diameter;
}

std::pair<Node, Distance> Explorer::GetFarthestNode(Node source) const {
  std::vector<Distance> distances(num_nodes_, -1);
  std::queue<Node> order;
  order.emplace(source);
  distances[source] = 0;

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    for (const auto &[adj_node, adj_distance] : adj_list_[node]) {
      if (distances[adj_node] == -1) {
        distances[adj_node] = distances[node] + adj_distance;
        order.emplace(adj_node);
      }
    }
  }
  const auto max_elem_it = std::max_element(distances.begin(), distances.end());
  return {std::distance(distances.begin(), max_elem_it), *max_elem_it};
}
} // namespace uva_10308

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  uva_10308::Node u;
  uva_10308::Node v;
  uva_10308::Distance distance;
  std::string line;

  while (!std::cin.eof()) {
    size_t num_nodes{0};
    uva_10308::EdgeList edge_list;
    while (std::getline(std::cin, line), !line.empty()) {
      std::istringstream tokenizer(line);
      tokenizer >> u >> v >> distance;
      edge_list.emplace_back(u, v, distance);

      num_nodes = std::max(num_nodes, std::max(u, v));
    }

    std::cout << uva_10308::Explorer(num_nodes + 1, edge_list).GetDiameter()
              << std::endl;
  }
  return 0;
}
