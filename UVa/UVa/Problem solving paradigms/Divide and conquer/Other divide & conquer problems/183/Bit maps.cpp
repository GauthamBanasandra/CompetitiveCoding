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
    return {num_rows - top_left.num_rows, num_columns};
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

  return {1, data_[i]};
}

class Compressor {
 public:
  Compressor(const std::string &data, Dimension dimension) : data_(Matrix(data, dimension)) {};

  std::string Compress() const;

 private:
  std::string Compress(Point &point, Dimension &dimension) const;
  TopLeftInfo ComputeTopLeft(const Point &begin, const Dimension &parent_dim) const;
  TopRightInfo ComputeTopRight(const TopLeftInfo &top_left_info, const Dimension &parent_dim) const;
  BottomLeftInfo ComputeBottomLeft(const TopLeftInfo &top_left_info, const Dimension &parent_dim) const;
  BottomRightInfo ComputeBottomRight(const TopLeftInfo &top_left_info, const Dimension &parent_dim) const;

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
  return std::string();
}

TopLeftInfo Compressor::ComputeTopLeft(const Point &begin, const Dimension &parent_dim) const {
  Dimension top_left_dim{static_cast<int>(std::ceil(parent_dim.num_rows / 2.0)),
                         static_cast<int>(std::ceil(parent_dim.num_columns / 2.0))};
  return TopLeftInfo{begin, top_left_dim};
}

TopRightInfo Compressor::ComputeTopRight(const TopLeftInfo &top_left_info, const Dimension &parent_dim) const {
  const auto &top_left_begin = top_left_info.first;
  const auto &top_left_dim = top_left_info.second;

  Dimension top_right_dim{top_left_dim.num_rows, parent_dim.num_columns - top_left_dim.num_columns};
  Point top_right_begin{top_left_begin.x, top_left_begin.y + top_left_dim.num_columns};
  return TopRightInfo{top_right_begin, top_right_dim};
}

BottomLeftInfo Compressor::ComputeBottomLeft(const TopLeftInfo &top_left_info, const Dimension &parent_dim) const {
  const auto &top_left_begin = top_left_info.first;
  const auto &top_left_dim = top_left_info.second;

  Dimension bottom_left_dim{parent_dim.num_rows - top_left_dim.num_rows, parent_dim.num_columns};
  Point bottom_left_begin{top_left_begin.x + top_left_dim.num_rows, top_left_begin.y};
  return BottomLeftInfo{bottom_left_begin, bottom_left_dim};
}

BottomRightInfo Compressor::ComputeBottomRight(const TopLeftInfo &top_left_info, const Dimension &parent_dim) const {
  const auto &top_left_begin = top_left_info.first;
  const auto &top_left_dim = top_left_info.second;

  Dimension bottom_right_dim{parent_dim.num_rows - top_left_dim.num_rows,
                             parent_dim.num_columns - top_left_dim.num_columns};
  Point bottom_right_begin{top_left_begin.x + top_left_dim.num_rows, top_left_begin.y + top_left_dim.num_columns};
  return BottomRightInfo{bottom_right_begin, bottom_right_dim};
}

int main() {
  std::string data = "12345678";
  Dimension dimension{2, 4};

  Matrix matrix(data, dimension);
  Point point{1, 3};
  std::cout << matrix.Get(point) << std::endl;
  return 0;
}