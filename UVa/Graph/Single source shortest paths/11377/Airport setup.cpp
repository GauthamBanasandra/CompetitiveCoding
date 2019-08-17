// WA

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

namespace uva_11377 {
const auto unvisited = -1;

namespace ds {
class ufds {
public:
  explicit ufds(std::size_t size);
  std::size_t find_set(std::size_t i);
  bool is_same_set(std::size_t i, std::size_t j);
  void union_set(std::size_t i, std::size_t j);

  std::size_t size;
  std::vector<std::size_t> parent_index;
  std::vector<std::size_t> rank;
};

inline ufds::ufds(const std::size_t size) : size(size) {
  rank.assign(size, 0);

  for (std::size_t i = 0; i < size; ++i) {
    parent_index.emplace_back(i);
  }
}

inline std::size_t ufds::find_set(const std::size_t i) {
  if (parent_index[i] == i) {
    return i;
  }

  parent_index[i] = find_set(parent_index[i]);
  return parent_index[i];
}

inline bool ufds::is_same_set(const std::size_t i, const std::size_t j) {
  return find_set(i) == find_set(j);
}

inline void ufds::union_set(const std::size_t i, const std::size_t j) {
  if (!is_same_set(i, j)) {
    const auto parent_i = find_set(i);
    const auto parent_j = find_set(j);
    if (rank[parent_i] > rank[parent_j]) {
      parent_index[parent_j] = parent_i;
    } else {
      parent_index[parent_i] = parent_j;
      if (rank[parent_i] == rank[parent_j]) {
        ++rank[parent_j];
      }
    }
  }
}
} // namespace ds

class Planner {
public:
  Planner(size_t num_nodes, const std::unordered_set<size_t> &special_nodes,
          const std::vector<std::pair<size_t, size_t>> &edge_list);

  int GetMinNumAirports(size_t source, size_t destination);

private:
  int GetNumAirports(const std::vector<size_t> &parent, const size_t source,
                     const size_t destination) const;

  const size_t num_nodes_;
  ds::ufds connected_nodes_;
  std::vector<std::vector<size_t>> adj_list_;
  std::unordered_set<size_t> special_nodes_;
};

Planner::Planner(const size_t num_nodes,
                 const std::unordered_set<size_t> &special_nodes,
                 const std::vector<std::pair<size_t, size_t>> &edge_list)
    : num_nodes_(num_nodes + 1), connected_nodes_(num_nodes + 1) {
  for (const auto &[u, v] : edge_list) {
    if (special_nodes.find(u) != special_nodes.end() &&
        special_nodes.find(v) != special_nodes.end()) {
      connected_nodes_.union_set(u, v);
    }
  }

  adj_list_.resize(num_nodes_);
  for (const auto &[u, v] : edge_list) {
    auto u_id = connected_nodes_.find_set(u);
    auto v_id = connected_nodes_.find_set(v);
    if (u_id != v_id) {
      adj_list_[u_id].emplace_back(v_id);
      adj_list_[v_id].emplace_back(u_id);
    }
  }

  for (const auto node : special_nodes) {
    special_nodes_.emplace(connected_nodes_.find_set(node));
  }
}

int Planner::GetMinNumAirports(const size_t source, const size_t destination) {
  if (source == destination) {
    return 0;
  }

  std::vector<int> visited(num_nodes_, unvisited);
  std::vector<size_t> parent(num_nodes_);
  std::queue<size_t> order;

  auto source_id = connected_nodes_.find_set(source);
  const auto destination_id = connected_nodes_.find_set(destination);

  visited[source_id] = 0;
  order.emplace(source_id);

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    for (const auto adj_node : adj_list_[node]) {
      if (visited[adj_node] == unvisited) {
        parent[adj_node] = node;
        visited[adj_node] = visited[node] + 1;
        order.emplace(adj_node);
      }
      if (adj_node == destination_id) {
        return GetNumAirports(parent, source_id, destination_id);
      }
    }
  }
  return -1;
}

int Planner::GetNumAirports(const std::vector<size_t> &parent,
                            const size_t source,
                            const size_t destination) const {
  auto num_airports = 0;
  for (auto node = destination; node != 0; node = parent[node]) {
    if (special_nodes_.find(node) == special_nodes_.end()) {
      ++num_airports;
    }
    if (node == source) {
      break;
    }
  }
  return num_airports;
}
} // namespace uva_11377

int main(int argc, char *argv[]) {
  size_t x = 0, n = 0, m = 0, k = 0, q = 0, source = 0, destination = 0,
         city = 0;
  std::vector<std::pair<size_t, size_t>> edge_list;

  std::cin >> x;

  for (size_t t = 1; t <= x; ++t) {
    std::cin >> n >> m >> k;
    std::unordered_set<size_t> special_nodes;

    for (size_t i = 0; i < k; ++i) {
      std::cin >> city;
      special_nodes.insert(city);
    }

    edge_list.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> edge_list[i].first >> edge_list[i].second;
    }

    uva_11377::Planner planner(n, special_nodes, edge_list);

    std::cout << "Case " << t << ':' << std::endl;
    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
      std::cin >> source >> destination;
      std::cout << planner.GetMinNumAirports(source, destination) << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
