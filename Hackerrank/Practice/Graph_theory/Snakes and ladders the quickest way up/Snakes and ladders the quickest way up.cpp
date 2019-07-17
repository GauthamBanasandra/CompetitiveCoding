// WA

#include <iostream>
#include <queue>
#include <vector>

const auto unvisited = -1;

class SnakesAndLadders {
public:
  SnakesAndLadders(const std::vector<std::pair<size_t, size_t>> &snakes,
                   const std::vector<std::pair<size_t, size_t>> &ladders);

  int GetMinDiceRolls() const;

private:
  int DFS(int node) const;

  std::vector<int> adj_list_;
};

SnakesAndLadders::SnakesAndLadders(
    const std::vector<std::pair<size_t, size_t>> &snakes,
    const std::vector<std::pair<size_t, size_t>> &ladders) {
  adj_list_.resize(101, -1);

  const auto add_edge =
      [this](const std::vector<std::pair<size_t, size_t>> &edges) -> void {
    for (const auto &[u, v] : edges) {
      adj_list_[u] = static_cast<int>(v);
    }
  };

  add_edge(snakes);
  add_edge(ladders);
}

int SnakesAndLadders::GetMinDiceRolls() const {
  std::vector<int> visited(101, unvisited);
  visited[1] = 0;
  std::queue<int> order;
  order.push(0);

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();

    if (node == 100) {
      return visited[100] + 1;
    }

    for (auto i = 1; i <= 6; ++i) {
      const auto next_node = node + i;
      if (next_node > 100 || visited[next_node] != unvisited) {
        continue;
      }

      visited[next_node] = visited[node] + 1;
      order.push(next_node);
      if (adj_list_[next_node] != -1) {
        const auto forward_node = DFS(next_node);
        if (visited[forward_node] == unvisited) {
          visited[forward_node] = visited[node] + 1;
          order.push(forward_node);
        }
      }
    }
  }
  return visited[100];
}

int SnakesAndLadders::DFS(const int node) const {
  if (adj_list_[node] != -1) {
    return DFS(adj_list_[node]);
  }
  return node;
}

int main(int argc, char *argv[]) {
  size_t t = 0, num_snakes = 0, num_ladders = 0;
  std::vector<std::pair<size_t, size_t>> snakes, ladders;

  std::cin >> t;
  while (t--) {
    std::cin >> num_ladders;
    ladders.resize(num_ladders);
    for (size_t i = 0; i < num_ladders; ++i) {
      std::cin >> ladders[i].first >> ladders[i].second;
    }

    std::cin >> num_snakes;
    snakes.resize(num_snakes);
    for (size_t i = 0; i < num_snakes; ++i) {
      std::cin >> snakes[i].first >> snakes[i].second;
    }

    std::cout << SnakesAndLadders(snakes, ladders).GetMinDiceRolls()
              << std::endl;
  }
  return 0;
}
