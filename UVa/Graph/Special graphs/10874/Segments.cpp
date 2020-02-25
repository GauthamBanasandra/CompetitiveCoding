#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

namespace uva_10874 {
using Length = int;

class Minimizer {
public:
  Minimizer(size_t num_points, const std::vector<std::pair<int, int>> &points);

  Length MinimumPathLength();

private:
  enum Position {
    kLeft,
    kRight,
    Count // Not a position
  };

  Length MinimumPathLength(size_t row, Position position);
  Length GetLastRowLength(Position position) const;

  const size_t num_points_;
  const std::vector<std::pair<int, int>> &points_;
  std::vector<std::vector<Length>> memo_;
};

Minimizer::Minimizer(const size_t num_points,
                     const std::vector<std::pair<int, int>> &points)
    : num_points_{num_points}, points_{points} {
  memo_.resize(Position::Count, std::vector<Length>(num_points_, -1));
}

Length Minimizer::MinimumPathLength() {
  const auto distance = points_.front().first - 1;
  return MinimumPathLength(0, Position::kLeft) + distance;
}

Length Minimizer::MinimumPathLength(const size_t row, const Position position) {
  if (row == num_points_ - 1) {
    return GetLastRowLength(position);
  }

  auto &memo = memo_[position][row];
  if (memo != -1) {
    return memo;
  }

  const auto current_len = points_[row].second - points_[row].first;
  const auto current_pos =
      position == Position::kLeft ? points_[row].second : points_[row].first;

  const auto choose_left = MinimumPathLength(row + 1, Position::kLeft) +
                           current_len +
                           std::abs(points_[row + 1].first - current_pos) + 1;
  const auto choose_right = MinimumPathLength(row + 1, Position::kRight) +
                            current_len +
                            std::abs(points_[row + 1].second - current_pos) + 1;
  return memo = std::min(choose_left, choose_right);
}

Length Minimizer::GetLastRowLength(const Position position) const {
  const auto distance = points_.back().second - points_.back().first;
  const auto extra = static_cast<int>(num_points_) - points_.back().second;
  return (position == Position::kLeft ? distance : 2 * distance) + extra;
}
} // namespace uva_10874

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t num_points;
  std::vector<std::pair<int, int>> points;

  while (std::cin >> num_points, num_points) {
    points.resize(num_points);
    for (size_t i = 0; i < num_points; ++i) {
      std::cin >> points[i].first >> points[i].second;
    }

    std::cout << uva_10874::Minimizer(num_points, points).MinimumPathLength()
              << std::endl;
  }
  return 0;
}
