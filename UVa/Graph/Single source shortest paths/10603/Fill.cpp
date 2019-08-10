// WIP

#include <cassert>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

using ll = long long;

class Mixer {
public:
  Mixer(int max_a, int max_b, int max_c, int target);

private:
  void BuildGraph(int a, int b, int c);

  static ll GetHash(const ll a, const ll b, const ll c) {
    return a * 100000000 + b * 10000 + c;
  }

  const int max_a_;
  const int max_b_;
  const int max_c_;
  const int target_;
  std::vector<std::tuple<int, int, int>> nodes_;
  std::unordered_map<ll, std::unordered_map<ll, int>> adj_list_;
};

Mixer::Mixer(const int max_a, const int max_b, const int max_c,
             const int target)
    : max_a_(max_a), max_b_(max_b), max_c_(max_c), target_(target) {}

void Mixer::BuildGraph(const int a, const int b, const int c) {
  nodes_.emplace_back(a, b, c);
  const auto node = GetHash(a, b, c);

  if (a > 0 && b < max_b_) {
    const auto rem_b = max_b_ - b;
    const auto new_a = a <= rem_b ? 0 : a - rem_b;
    const auto new_b = a <= rem_b ? a + b : max_b_;
    const auto adj_node = GetHash(new_a, new_b, c);
    assert(adj_list_[node].find(adj_node) == adj_list_[node].end());
    adj_list_[node][adj_node] = a - new_a;
    BuildGraph(new_a, new_b, c);
  }

  if (a > 0 && c < max_c_) {
    const auto rem_c = max_c_ - c;
    const auto new_a = a <= rem_c ? 0 : a - rem_c;
    const auto new_c = a <= rem_c ? a + c : max_c_;
    const auto adj_node = GetHash(new_a, b, new_c);
    assert(adj_list_[node].find(adj_node) == adj_list_[node].end());
    adj_list_[node][adj_node] = a - new_a;
    BuildGraph(new_a, b, new_c);
  }

  if (b > 0 && a < max_a_) {
    const auto rem_a = max_a_ - a;
    const auto new_b = b <= rem_a ? 0 : b - rem_a;
    const auto new_a = b <= rem_a ? b + a : max_a_;
    const auto adj_node = GetHash(new_a, new_b, c);
    assert(adj_list_[node].find(adj_node) == adj_list_[node].end());
    adj_list_[node][adj_node] = b - new_b;
    BuildGraph(new_a, new_b, c);
  }

  if (b > 0 && c < max_c_) {
    const auto rem_c = max_c_ - c;
    const auto new_b = b <= rem_c ? 0 : b - rem_c;
    const auto new_c = b <= rem_c ? b + c : max_c_;
    const auto adj_node = GetHash(a, new_b, new_c);
    assert(adj_list_[node].find(adj_node) == adj_list_[node].end());
    adj_list_[node][adj_node] = b - new_b;
    BuildGraph(a, new_b, new_c);
  }

  if (c > 0 && a < max_a_) {
    const auto rem_a = max_a_ - a;
    const auto new_c = c <= rem_a ? 0 : c - rem_a;
    const auto new_a = c <= rem_a ? c + a : max_a_;
    const auto adj_node = GetHash(new_a, b, new_c);
    assert(adj_list_[node].find(adj_node) == adj_list_[node].end());
    adj_list_[node][adj_node] = c - new_c;
    BuildGraph(new_a, b, new_c);
  }

  if (c > 0 && b < max_b_) {
    const auto rem_b = max_b_ - b;
    const auto new_c = c <= rem_b ? 0 : c - rem_b;
    const auto new_b = c <= rem_b ? c + b : max_c_;
    const auto adj_node = GetHash(a, new_b, new_c);
    assert(adj_list_[node].find(adj_node) == adj_list_[node].end());
    adj_list_[node][adj_node] = c - new_c;
    BuildGraph(a, new_b, new_c);
  }
}

int main(int argc, char *argv[]) {}
