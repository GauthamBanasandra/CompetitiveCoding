//
// Created by Gautham Banasandra on 01/07/18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct Dimension {
  Dimension() : num_rows(1), num_columns(1) {}
  Dimension(int num_rows, int num_columns) : num_rows(num_rows), num_columns(num_columns) {}

  Dimension TopLeft() const {
    return {static_cast<int>(std::ceil(num_rows / 2.0)), static_cast<int>(std::ceil(num_columns / 2.0))};
  }

  Dimension TopRight() const {
    const auto &top_left = TopLeft();
    return {top_left.num_rows, num_columns - top_left.num_columns};
  }

  Dimension BottomLeft() const {
    const auto &top_left = TopLeft();
    return {num_rows - top_left.num_rows, top_left.num_columns};
  }

  Dimension BottomRight() const {
    const auto &top_left = TopLeft();
    return {num_rows - top_left.num_rows, num_columns - top_left.num_columns};
  }

  int num_rows;
  int num_columns;
};

struct Point {
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}

  Point TopLeft() const {
    return {x, y};
  }

  Point TopRight(const Dimension &dimension) const {
    return {x, y + dimension.num_columns};
  }

  Point BottomLeft(const Dimension &dimension) const {
    return {x + dimension.num_rows, y};
  }

  Point BottomRight(const Dimension &dimension) const {
    return {x + dimension.num_rows, y + dimension.num_columns};
  }

  int x;
  int y;
};

using TopLeftInfo = std::pair<Point, Dimension>;
using TopRightInfo = std::pair<Point, Dimension>;
using BottomLeftInfo = std::pair<Point, Dimension>;
using BottomRightInfo = std::pair<Point, Dimension>;

class Matrix {
 public:
  explicit Matrix(std::string data, Dimension dimension) : data_(std::move(data)), dimension_(dimension) {}

  std::string Get(const Point &point) const;

  const Dimension dimension_;

 private:
  std::string data_;
};

std::string Matrix::Get(const Point &point) const {
  auto i = (point.x * dimension_.num_columns) + point.y;
  assert(i < data_.length());

  char data[2]{data_[i], '\0'};
  return std::string(data);
}

class Compressor {
 public:
  Compressor(const std::string &data, Dimension dimension) : data_(Matrix(data, dimension)) {};

  std::string Compress() const;

 private:
  std::string Compress(Point &point, Dimension &dimension) const;
  Point ComputeTopRight(const Point &top_left_begin, const Dimension &top_left_dim) const;
  Point ComputeBottomLeft(const Point &top_left_begin, const Dimension &top_left_dim) const;
  Point ComputeBottomRight(const Point &top_left_begin, const Dimension &top_left_dim) const;
  bool AllSame(const std::string &data) const;

  Matrix data_;
};

std::string Compressor::Compress() const {
  Point begin{0, 0};
  auto dimension = data_.dimension_;
  return Compress(begin, dimension);
}

std::string Compressor::Compress(Point &point, Dimension &dimension) const {
  assert((dimension.num_rows >= 1) && (dimension.num_columns >= 1));

  if ((dimension.num_rows == 1) && (dimension.num_columns == 1)) {
    return data_.Get(point);
  }

  std::string res;
  auto top_left_dim = dimension.TopLeft();
  res += Compress(point, top_left_dim);

  if (dimension.num_columns > 1) {
    auto top_right_begin = ComputeTopRight(point, top_left_dim);
    auto top_right_dim = dimension.TopRight();
    res += Compress(top_right_begin, top_right_dim);
  }

  if (dimension.num_rows > 1) {
    auto bottom_left_begin = ComputeBottomLeft(point, top_left_dim);
    auto bottom_left_dim = dimension.BottomLeft();
    res += Compress(bottom_left_begin, bottom_left_dim);
  }

  if ((dimension.num_columns > 1) && (dimension.num_rows > 1)) {
    auto bottom_right_begin = ComputeBottomRight(point, top_left_dim);
    auto bottom_right_dim = dimension.BottomRight();
    res += Compress(bottom_right_begin, bottom_right_dim);
  }

  if (AllSame(res)) {
    char data[2]{res[0], '\0'};
    return std::string(data);
  }

  return "D" + res;
}

Point Compressor::ComputeTopRight(const Point &top_left_begin, const Dimension &top_left_dim) const {
  return {top_left_begin.x, top_left_begin.y + top_left_dim.num_columns};
}

Point Compressor::ComputeBottomLeft(const Point &top_left_begin, const Dimension &top_left_dim) const {
  return {top_left_begin.x + top_left_dim.num_rows, top_left_begin.y};
}

Point Compressor::ComputeBottomRight(const Point &top_left_begin, const Dimension &top_left_dim) const {
  return {top_left_begin.x + top_left_dim.num_rows, top_left_begin.y + top_left_dim.num_columns};
}

bool Compressor::AllSame(const std::string &data) const {
  assert(data.length() > 1);

  auto test = data[0];
  for (std::size_t i = 1; i < data.length(); ++i) {
    if (test != data[i]) {
      return false;
    }
  }

  return true;
}

int main() {
  std::string data = "101111";
  Dimension dimension{1, 6};

  std::cout << Compressor(data, dimension).Compress() << std::endl;
  return 0;
}