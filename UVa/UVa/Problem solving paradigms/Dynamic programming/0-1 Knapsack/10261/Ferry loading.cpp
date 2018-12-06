//
// Created by Gautham on 06-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

class Ferry {
 public:
  Ferry(ll port_len, ll starboard_len, const std::vector<ll> &cars);
  ll Direct();

 private:
  ll Direct(std::size_t i, ll port_len, ll starboard_len);

  const ll port_len_;
  const ll starboard_len_;
  const std::vector<ll> &cars_;
  std::vector<ll> memo_;
};

Ferry::Ferry(const ll port_len, const ll starboard_len, const std::vector<ll> &cars)
    : port_len_(port_len), starboard_len_(starboard_len), cars_(cars) {
  memo_.resize(cars_.size(), -1);
}

ll Ferry::Direct(std::size_t i, ll port_len, ll starboard_len) {
  if (i >= cars_.size()) {
    return 0;
  }

  auto &memo = memo_[i];
  if (memo != -1) {
    return memo;
  }

  if (cars_[i] > port_len && cars_[i] > starboard_len) {
    return 0;
  }

  if (cars_[i] <= port_len && cars_[i] > starboard_len) {
    return Direct(i + 1, port_len - cars_[i], starboard_len) + 1;
  }

  if (cars_[i] > port_len && cars_[i] <= starboard_len) {
    return Direct(i + 1, port_len, starboard_len - cars_[i]) + 1;
  }

  auto l = Direct(i + 1, port_len - cars_[i], starboard_len);
  auto r = Direct(i + 1, port_len, starboard_len - cars_[i]);
  memo = std::max(l, r) + 1;
  return memo;
}

ll Ferry::Direct() {
  return Direct(0, port_len_, starboard_len_);
}

int main() {
//  ll ferry_len = 98;
//  ll ferry_len = 20;
  ll ferry_len = 50;
  ll port_len = ferry_len * 100, starboard_len = ferry_len * 100;
  std::vector<ll> cars{
      2500,
      3000,
      1000,
      1000,
      1500,
      700,
      800

      /*3551,
      8043,
      6203,
      1798,
      1190*/

      /*101,
      207,
      155,
      143,
      512,
      335,
      108,
      977,
      567,
      201,
      188,
      311,
      112*/
  };

  std::cout << Ferry(port_len, starboard_len, cars).Direct() << std::endl;
  return 0;
}