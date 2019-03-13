//
// Created by gauth on 17-01-2018.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>

void print(const std::vector<float> &drive_ratio);

int main() {
  int f, r, ft, rt;
  std::string line;
  std::vector<int> front_teeth, rear_teeth;
  std::vector<float> drive_ratio;

  while (std::getline(std::cin, line), line != "0") {
    std::istringstream fr_tokenizer(line);
    fr_tokenizer >> f >> r;

    front_teeth.clear();
    rear_teeth.clear();
    front_teeth.assign(f, 0);
    rear_teeth.assign(r, 0);

    std::getline(std::cin, line);
    std::istringstream ft_tokenizer(line);
    for (int i = 0; i < f; ++i) {
      ft_tokenizer >> front_teeth[i];
    }

    std::getline(std::cin, line);
    std::istringstream rt_tokenizer(line);
    for (int i = 0; i < r; ++i) {
      rt_tokenizer >> rear_teeth[i];
    }

    drive_ratio.clear();
    drive_ratio.assign(f * r, 0);
    auto c = 0;
    for (int i = 0; i < f; ++i) {
      for (int j = 0; j < r; ++j) {
        drive_ratio[c++] = static_cast<float>(rear_teeth[j]) / front_teeth[i];
      }
    }

    std::sort(drive_ratio.begin(), drive_ratio.end());
    float max = 0;
    for (std::size_t i = 0; i < drive_ratio.size() - 1; ++i) {
      max = std::max(max, drive_ratio[i + 1] / drive_ratio[i]);
    }

    std::cout << std::setprecision(2) << std::fixed << roundf(max * 100) / 100 << std::endl;
  }

  return 0;
}
