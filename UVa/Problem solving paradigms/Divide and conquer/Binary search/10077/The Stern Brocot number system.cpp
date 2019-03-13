//
// Created by Gautham Banasandra on 07/06/18.
//

#include <limits>
#include <string>
#include <iostream>
#include <cassert>

using ll = long long;

struct Fraction {
  Fraction(ll numerator, ll denominator) : numerator(numerator), denominator(denominator) {}

  bool operator!=(const Fraction &other) const {
    return (numerator != other.numerator) || (denominator != other.denominator);
  }

  ll numerator;
  ll denominator;
};

std::string GetRepresentation(const Fraction &target) {
  std::string representation;
  Fraction low(0, 1);
  Fraction high(1, 0);
  Fraction mid(low.numerator + high.numerator, low.denominator + high.denominator);
  auto target_f = static_cast<double>(target.numerator) / target.denominator;

  while (mid != target) {
    auto low_f = static_cast<double>(low.numerator) / low.denominator;
    auto mid_f = static_cast<double>(mid.numerator) / mid.denominator;
    auto high_f = high.denominator == 0 ? std::numeric_limits<double>::max() : (static_cast<double>(high.numerator)
        / high.denominator);
    if ((low_f <= target_f) && (target_f <= mid_f)) {
      high = mid;
      representation += "L";
    } else if ((mid_f <= target_f) && (target_f <= high_f)) {
      low = mid;
      representation += "R";
    } else {
      assert(false);
    }

    mid.numerator = low.numerator + high.numerator;
    mid.denominator = low.denominator + high.denominator;
  }

  return representation;
}

int main() {
  Fraction target(0, 0);

  while (std::cin >> target.numerator >> target.denominator, (target.numerator != 1) || (target.denominator != 1)) {
    std::cout << GetRepresentation(target) << std::endl;
  }

  return 0;
}