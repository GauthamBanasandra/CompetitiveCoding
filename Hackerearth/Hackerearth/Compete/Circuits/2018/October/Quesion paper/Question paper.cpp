// TLE
#include <iostream>
#include <unordered_set>
#include <ios>

using ll = long long;

std::size_t CountDifferentScores(const ll n, const int correct_value, const int incorrect_value) {
  std::unordered_set<ll> uniq_scores;
  for (ll i = 0; i <= n; ++i) {
    for (ll j = 0; j <= i; ++j) {
      const auto num_correct = j;
      const auto num_incorrect = i - j;
      auto score = (num_correct * correct_value) - (num_incorrect * incorrect_value);
      uniq_scores.insert(score);
    }
  }
  return uniq_scores.size();
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  int t, a, b;
  ll n;

  std::cin >> t;

  while (t-- > 0) {
    std::cin >> n >> a >> b;
    std::cout << CountDifferentScores(n, a, b) << std::endl;
  }
}
