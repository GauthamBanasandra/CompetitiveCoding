// WA

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace uva_10603 {
using ll = long long;
const auto infinity = std::numeric_limits<int>::max();
const auto infinity_ll = std::numeric_limits<ll>::max();

class Mixer {
public:
  Mixer(int max_a, int max_b, int max_c, int target);
  std::pair<ll, ll> GetShortestDistance() const;

private:
  void BuildGraph(int a, int b, int c, std::unordered_set<ll> &lineage);
  void InitializeDestinations();

  static ll GetHash(ll a, ll b, ll c);

  const int max_a_;
  const int max_b_;
  const int max_c_;
  int target_;
  const ll source_;
  std::vector<ll> destinations_;
  std::vector<std::tuple<int, int, int>> nodes_;
  std::unordered_map<ll, std::unordered_map<ll, int>> adj_list_;
};

Mixer::Mixer(const int max_a, const int max_b, const int max_c,
             const int target)
    : max_a_(max_a), max_b_(max_b), max_c_(max_c), target_(target),
      source_(GetHash(0, 0, max_c)) {
  std::unordered_set<ll> lineage;
  lineage.insert(GetHash(0, 0, max_c_));
  BuildGraph(0, 0, max_c_, lineage);
  InitializeDestinations();
}

std::pair<ll, ll> Mixer::GetShortestDistance() const {
  std::unordered_map<ll, ll> min_cost;
  std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>,
                      std::greater<>>
      order;
  min_cost[source_] = 0;
  order.emplace(0, source_);

  while (!order.empty()) {
    const auto [current_cost, node] = order.top();
    order.pop();

    auto find_min_cost_node_it = min_cost.find(node);
    assert(find_min_cost_node_it != min_cost.end());
    if (current_cost > find_min_cost_node_it->second) {
      continue;
    }
    const auto min_cost_node = find_min_cost_node_it->second;

    auto find_adj_node_it = adj_list_.find(node);
    assert(find_adj_node_it != adj_list_.end());
    for (const auto &[adj_node, adj_cost] : find_adj_node_it->second) {
      const auto cost = min_cost_node + adj_cost;
      auto find_min_cost_adj_node_it = min_cost.find(adj_node);
      const auto min_cost_adj_node = find_min_cost_adj_node_it != min_cost.end()
                                         ? find_min_cost_adj_node_it->second
                                         : infinity;
      if (cost < min_cost_adj_node) {
        min_cost[adj_node] = cost;
        order.emplace(cost, adj_node);
      }
    }
  }
  const auto min_cost_dst =
      *std::min_element(destinations_.begin(), destinations_.end(),
                        [&min_cost](const ll a, const ll b) -> bool {
                          const auto find_a_it = min_cost.find(a);
                          assert(find_a_it != min_cost.end());
                          const auto find_b_it = min_cost.find(b);
                          assert(find_b_it != min_cost.end());
                          return find_a_it->second < find_b_it->second;
                        });
  return std::make_pair((*min_cost.find(min_cost_dst)).second, target_);
}

void Mixer::BuildGraph(const int a, const int b, const int c,
                       std::unordered_set<ll> &lineage) {
  nodes_.emplace_back(a, b, c);
  const auto node = GetHash(a, b, c);

  if (a > 0 && b < max_b_) {
    const auto rem_b = max_b_ - b;
    const auto new_a = a <= rem_b ? 0 : a - rem_b;
    const auto new_b = a <= rem_b ? a + b : max_b_;
    const auto adj_node = GetHash(new_a, new_b, c);

    if (lineage.find(adj_node) == lineage.end()) {
      lineage.insert(adj_node);
      adj_list_[node][adj_node] = adj_list_[adj_node][node] = a - new_a;
      BuildGraph(new_a, new_b, c, lineage);
      lineage.erase(adj_node);
    }
  }

  if (a > 0 && c < max_c_) {
    const auto rem_c = max_c_ - c;
    const auto new_a = a <= rem_c ? 0 : a - rem_c;
    const auto new_c = a <= rem_c ? a + c : max_c_;
    const auto adj_node = GetHash(new_a, b, new_c);

    if (lineage.find(adj_node) == lineage.end()) {
      lineage.insert(adj_node);
      adj_list_[node][adj_node] = adj_list_[adj_node][node] = a - new_a;
      BuildGraph(new_a, b, new_c, lineage);
      lineage.erase(adj_node);
    }
  }

  if (b > 0 && a < max_a_) {
    const auto rem_a = max_a_ - a;
    const auto new_b = b <= rem_a ? 0 : b - rem_a;
    const auto new_a = b <= rem_a ? b + a : max_a_;
    const auto adj_node = GetHash(new_a, new_b, c);

    if (lineage.find(adj_node) == lineage.end()) {
      lineage.insert(adj_node);
      adj_list_[node][adj_node] = adj_list_[adj_node][node] = b - new_b;
      BuildGraph(new_a, new_b, c, lineage);
      lineage.erase(adj_node);
    }
  }

  if (b > 0 && c < max_c_) {
    const auto rem_c = max_c_ - c;
    const auto new_b = b <= rem_c ? 0 : b - rem_c;
    const auto new_c = b <= rem_c ? b + c : max_c_;
    const auto adj_node = GetHash(a, new_b, new_c);

    if (lineage.find(adj_node) == lineage.end()) {
      lineage.insert(adj_node);
      adj_list_[node][adj_node] = adj_list_[adj_node][node] = b - new_b;
      BuildGraph(a, new_b, new_c, lineage);
      lineage.erase(adj_node);
    }
  }

  if (c > 0 && a < max_a_) {
    const auto rem_a = max_a_ - a;
    const auto new_c = c <= rem_a ? 0 : c - rem_a;
    const auto new_a = c <= rem_a ? c + a : max_a_;
    const auto adj_node = GetHash(new_a, b, new_c);

    if (lineage.find(adj_node) == lineage.end()) {
      lineage.insert(adj_node);
      adj_list_[node][adj_node] = adj_list_[adj_node][node] = c - new_c;
      BuildGraph(new_a, b, new_c, lineage);
      lineage.erase(adj_node);
    }
  }

  if (c > 0 && b < max_b_) {
    const auto rem_b = max_b_ - b;
    const auto new_c = c <= rem_b ? 0 : c - rem_b;
    const auto new_b = c <= rem_b ? c + b : max_b_;
    const auto adj_node = GetHash(a, new_b, new_c);

    if (lineage.find(adj_node) == lineage.end()) {
      lineage.insert(adj_node);
      adj_list_[node][adj_node] = adj_list_[adj_node][node] = c - new_c;
      BuildGraph(a, new_b, new_c, lineage);
      lineage.erase(adj_node);
    }
  }
}

void Mixer::InitializeDestinations() {
  auto closest_target = infinity;
  for (const auto &[a, b, c] : nodes_) {
    if (a <= target_ && target_ - a < closest_target) {
      closest_target = target_ - a;
    }

    if (b <= target_ && target_ - b < closest_target) {
      closest_target = target_ - b;
    }

    if (c <= target_ && target_ - c < closest_target) {
      closest_target = target_ - c;
    }
  }

  target_ -= closest_target;
  for (const auto &[a, b, c] : nodes_) {
    if (a == target_ || b == target_ || c == target_) {
      destinations_.emplace_back(GetHash(a, b, c));
    }
  }
}

ll Mixer::GetHash(const ll a, const ll b, const ll c) {
  ll hash = 10000000000000;
  hash += a * 100000000;
  hash += b * 10000;
  hash += c;
  return hash;
}
} // namespace uva_10603

int main(int argc, char *argv[]) {
  size_t t = 0;
  auto a = 0, b = 0, c = 0, d = 0;

  std::cin >> t;
  while (t--) {
    std::cin >> a >> b >> c >> d;
    auto [cost, target] = uva_10603::Mixer(a, b, c, d).GetShortestDistance();
    std::cout << cost << ' ' << target << std::endl;
  }
  return 0;
}
