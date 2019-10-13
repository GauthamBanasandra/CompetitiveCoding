// WA

#include <algorithm>
#include <iostream>
#include <ostream>
#include <tuple>
#include <vector>

class Scheduler {
public:
  explicit Scheduler(std::vector<std::vector<int>> &cubes);

  int GetMaximumHeight() const;

private:
  std::vector<std::tuple<int, int, int>> cubes_;
};

Scheduler::Scheduler(std::vector<std::vector<int>> &cubes) {
  for (auto &cube : cubes) {
    std::sort(cube.begin(), cube.end());
  }

  cubes_.reserve(3 * cubes.size());
  for (auto &cube : cubes) {
    cubes_.emplace_back(cube[0], cube[1], cube[2]);
    cubes_.emplace_back(cube[1], cube[0], cube[2]);
    cubes_.emplace_back(cube[2], cube[0], cube[1]);
  }
  std::sort(cubes_.begin(), cubes_.end(),
            [](const std::tuple<int, int, int> &a,
               const std::tuple<int, int, int> &b) -> bool {
              return std::get<0>(a) < std::get<0>(b);
            });

  std::vector<std::tuple<int, int, int>> t_cubes;
  t_cubes.reserve(cubes.size());
  t_cubes.emplace_back(cubes_.front());
  for (auto cube : cubes_) {
    if (std::get<0>(t_cubes.back()) != std::get<0>(cube)) {
      t_cubes.emplace_back(cube);
    } else if (std::get<1>(cube) < std::get<1>(t_cubes.back())) {
      t_cubes.back() = cube;
    }
  }
  std::swap(cubes_, t_cubes);
}

int Scheduler::GetMaximumHeight() const {
  std::vector<int> max_height(cubes_.size() + 1);
  std::vector<int> lis{0};

  for (const auto &cube : cubes_) {
    auto a_it =
        std::lower_bound(lis.begin() + 1, lis.end(), std::get<1>(cube),
                         [](const int &element, const int &key) -> bool {
                           return element < key;
                         });
    auto b_it =
        std::lower_bound(lis.begin() + 1, lis.end(), std::get<2>(cube),
                         [](const int &element, const int &key) -> bool {
                           return element < key;
                         });
    auto it = lis.end();
    if (std::distance(lis.begin(), a_it) > std::distance(lis.begin(), b_it)) {
      it = a_it;
    } else if (std::distance(lis.begin(), b_it) >
               std::distance(lis.begin(), a_it)) {
      it = b_it;
    }

    const auto i = std::distance(lis.begin(), it);
    max_height[i] = max_height[i - 1] + std::get<2>(cube);

    if (it == lis.end()) {
      lis.emplace_back(std::get<1>(cube));
    } else {
      *it = std::get<1>(cube);
    }
  }
  return *std::max_element(max_height.begin(), max_height.end());
}

int main(int argc, char *argv[]) {
  size_t c = 0, num_cubes;
  std::vector<std::vector<int>> cubes;

  while (std::cin >> num_cubes, num_cubes != 0) {
    cubes.resize(num_cubes);
    for (size_t i = 0; i < num_cubes; ++i) {
      cubes[i].resize(3);
      std::cin >> cubes[i][0] >> cubes[i][1] >> cubes[i][2];
    }
    std::cout << "Case " << ++c
              << ": maximum height = " << Scheduler(cubes).GetMaximumHeight()
              << std::endl;
  }
  return 0;
}
