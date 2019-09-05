// WIP

#include <algorithm>
#include <limits>
#include <tuple>
#include <vector>

using Cost = int;
using Node = size_t;
template <typename T> using AdjacencyMatrix = std::vector<std::vector<T>>;

const auto infinity = std::numeric_limits<Cost>::max();
enum class RoadFor { kYoung, KMature };
enum class RoadDirection { kUnidirectional, kBidirectional };

class Navigator {
public:
  Navigator(
      const std::vector<std::tuple<RoadFor, RoadDirection, Node, Node, Cost>>
          &edge_list);

private:
  size_t num_nodes_{0};
  AdjacencyMatrix<Cost> adj_matrix_;
};

Navigator::Navigator(
    const std::vector<std::tuple<RoadFor, RoadDirection, Node, Node, Cost>>
        &edge_list) {
  adj_matrix_.resize(26, std::vector<Cost>(infinity, 26));
  for (const auto &[road_for, direction, u, v, cost] : edge_list) {
    adj_matrix_[u][v] = std::min(adj_matrix_[u][v], cost);
    if (direction == RoadDirection::kBidirectional) {
      adj_matrix_[v][u] = std::min(adj_matrix_[v][u], cost);
    }
  }
}

int main(int argc, char *argv[]) { return 0; }
