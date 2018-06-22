//
// Created by Gautham Banasandra on 22/06/18.
//

#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

using ll = long long;

void Print(const std::vector<ll> &sequence);

ll nod(ll n) {
  ll num_divisors = 0;

  for (ll i = 1; i <= sqrt(n); ++i) {
    if (n % i) {
      continue;
    }

    num_divisors = n / i == i ? num_divisors + 1 : num_divisors + 2;
  }

  return num_divisors;
}

std::vector<ll> GetSequence(ll max_n) {
  std::vector<ll> sequence;
  sequence.reserve(max_n);

  for (ll n = 1; n <= max_n; n += nod(n)) {
    sequence.emplace_back(n);
  }

  return sequence;
}

int main() {
  std::ios::sync_with_stdio(false);

  ll a, b, t = 0;
  auto sequence = GetSequence(1000010l);

  std::cin >> t;
  for (ll i = 1; i <= t; ++i) {
    std::cin >> a >> b;
    auto a_it = std::lower_bound(sequence.begin(), sequence.end(), a);
    auto b_it = std::lower_bound(sequence.rbegin(), sequence.rend(), b, std::greater<ll>());
    std::cout << "Case " << i << ": " << std::distance(a_it, (++b_it).base() + 1) << std::endl;
  }

  return 0;
}