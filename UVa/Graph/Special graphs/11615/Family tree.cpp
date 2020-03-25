#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <queue>

namespace uva_11615 {
using Node = int;

class FamilyTree {
public:
  FamilyTree(const int num_levels, const Node p1, const Node p2)
      : num_nodes_{(1 << num_levels) - 1}, person_{std::max(p1, p2)} {}

  int CountUniqueNodes() const;

private:
  const int num_nodes_;
  const Node person_;
};

int FamilyTree::CountUniqueNodes() const {
  auto count = 0;
  std::queue<Node> order;

  auto add_child = [this, &order](const Node node) {
    if (node <= num_nodes_) {
      order.emplace(node);
    }
  };

  auto left_child = [](const int node) -> Node { return node << 1; };
  auto right_child = [](const int node) -> Node { return (node << 1) + 1; };

  add_child(left_child(person_));
  add_child(right_child(person_));

  while (!order.empty()) {
    ++count;
    const auto node = order.front();
    order.pop();

    add_child(left_child(node));
    add_child(right_child(node));
  }
  return num_nodes_ - count;
}
} // namespace uva_11615

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t t;
  int num_generations;
  uva_11615::Node p1;
  uva_11615::Node p2;

  std::cin >> t;
  while (t--) {
    std::cin >> num_generations >> p1 >> p2;
    std::cout
        << uva_11615::FamilyTree(num_generations, p1, p2).CountUniqueNodes()
        << std::endl;
  }
  return 0;
}
