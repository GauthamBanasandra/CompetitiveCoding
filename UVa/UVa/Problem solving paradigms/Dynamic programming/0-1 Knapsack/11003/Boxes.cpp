//
// Created by Gautham on 13-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

struct Box {
  Box() = default;
  Box(int weight, int load) : weight(weight), load(load) {}
  int weight{};
  int load{};
};

class BoxSelector {
 public:
  explicit BoxSelector(const std::vector<Box> &boxes, std::size_t max_load, std::size_t max_weight);

  int Select();

 private:
  int Select(std::size_t i, int load_left);

  const int max_load_;
  const int max_weight_;
  std::vector<std::vector<int>> memo_;
  const std::vector<Box> &boxes_;
};

BoxSelector::BoxSelector(const std::vector<Box> &boxes, const std::size_t max_load, const std::size_t max_weight)
    : boxes_(boxes), max_load_(static_cast<int>(max_load)), max_weight_(static_cast<int>(max_weight)) {
  memo_.resize(boxes_.size());
  for (auto &row : memo_) {
    row.resize(10001, -1);
  }
}

int BoxSelector::Select() {
  return Select(0, 10000);
}

int BoxSelector::Select(std::size_t i, int load_left) {
  if (i >= boxes_.size()) {
    return 0;
  }

  if (boxes_[i].weight > load_left) {
    return Select(i + 1, load_left);
  }

  auto &memo = memo_[i][load_left];
  if (memo != -1) {
    return memo;
  }

  return memo = std::max(Select(i + 1, load_left),
                         Select(i + 1, std::min(load_left - boxes_[i].weight, boxes_[i].load)) + 1);
}

int main() {
  std::size_t num_boxes;
  std::vector<Box> boxes{
      {28, 84},
      {22, 65},
      {38, 19},
      {38, 66},
      {1, 34},
      {36, 26},
      {37, 82},
      {23, 69},
      {21, 65},
      {19, 65}
  };

  while (std::cin >> num_boxes, num_boxes) {
    std::size_t max_weight = 0, max_load = 0;
    boxes.resize(num_boxes);
    for (std::size_t i = 0; i < num_boxes; ++i) {
      std::cin >> boxes[i].weight >> boxes[i].load;

      max_weight = std::max(max_weight, static_cast<std::size_t>(boxes[i].weight));
      max_load = std::max(max_load, static_cast<std::size_t>(boxes[i].load));
    }

    std::cout << BoxSelector(boxes, max_load, max_weight).Select() << std::endl;
  }

//  std::cout << BoxSelector(boxes, max_load).Select() << std::endl;
  return 0;
}