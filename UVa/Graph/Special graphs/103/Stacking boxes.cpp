// WIP

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

std::vector<size_t> SortBoxes(std::vector<std::vector<int>> &boxes) {
  for (auto &box : boxes) {
    std::sort(box.begin(), box.end());
  }

  std::vector<size_t> box_indices(boxes.size());
  std::iota(box_indices.begin(), box_indices.end(), 0);

  std::sort(box_indices.begin(), box_indices.end(),
            [&boxes](const size_t &i, const size_t &j) -> bool {
              return boxes[i] < boxes[j];
            });

  std::vector<size_t> nesting_order;
  nesting_order.reserve(boxes.size());
  nesting_order.emplace_back(box_indices.front());

  for (size_t i = 1, prev = 0, num_boxes = boxes.size(); i < num_boxes; ++i) {
    auto eliminate = false;
    for (size_t j = 0, num_dimensions = boxes[i].size(); j < num_dimensions;
         ++j) {
      if (boxes[box_indices[prev]][j] >= boxes[box_indices[i]][j]) {
        eliminate = true;
      }
    }
    if (!eliminate) {
      nesting_order.emplace_back(box_indices[i]);
      prev = i;
    }
  }

  std::transform(nesting_order.begin(), nesting_order.end(),
                 nesting_order.begin(),
                 [](const size_t &index) -> size_t { return index + 1; });
  return nesting_order;
}

int main(int argc, char *argv[]) {
  size_t num_boxes, num_dimensions;
  std::vector<std::vector<int>> boxes;

  while (std::cin >> num_boxes >> num_dimensions, !std::cin.eof()) {
    boxes.resize(num_boxes);
    for (size_t i = 0; i < num_boxes; ++i) {
      boxes[i].resize(num_dimensions);
      for (size_t j = 0; j < num_dimensions; ++j) {
        std::cin >> boxes[i][j];
      }
    }

    auto order = SortBoxes(boxes);
    std::cout << order.size() << std::endl;

    auto separator = "";
    for (const auto &index : order) {
      std::cout << separator << index;
      separator = " ";

      // auto sep = "";
      // for (const auto &dimension : boxes[index - 1]) {
      //  std::cout << sep << dimension;
      //  sep = " ";
      //}
      // std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
