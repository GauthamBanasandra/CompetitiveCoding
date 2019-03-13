//
// Created by gauth on 03-07-2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <string>
#include <sstream>
#include <cassert>

void Print(const std::vector<int> &elements);

void Print(const std::vector<std::pair<int, int>> &chamber_assignment, double imbalance) {
  for (std::size_t i = 0; i < chamber_assignment.size(); ++i) {
    const auto first = chamber_assignment[i].first;
    const auto second = chamber_assignment[i].second;

    if (first != 0 && second != 0) {
      printf(" %ld: %d %d\n", i, first, second);
    } else if ((first == 0) && (second != 0)) {
      printf(" %ld: %d\n", i, second);
    } else if ((second == 0) && (first != 0)) {
      printf(" %ld: %d\n", i, first);
    } else if ((first == 0) && (second == 0)) {
      printf(" %ld:\n", i);
    }
  }

  printf("IMBALANCE = %.5lf\n", imbalance);
}

void AssignChambers(std::size_t num_chambers, std::vector<int> &specimen_mass) {
  double mean = std::accumulate(specimen_mass.begin(), specimen_mass.end(), 0.0) / static_cast<double>(num_chambers);
  specimen_mass.resize(num_chambers * 2);
  auto num_specimen = specimen_mass.size();
  std::sort(specimen_mass.begin(), specimen_mass.end());
  assert((num_chambers * 2) == num_specimen);

  double imbalance = 0.0;
  std::vector<std::pair<int, int>> chamber_assignment;
  for (std::size_t i = 0; i < num_chambers; ++i) {
    chamber_assignment.emplace_back(specimen_mass[i], specimen_mass[num_specimen - i - 1]);
    double chamber_mass = specimen_mass[i] + specimen_mass[num_specimen - i - 1];
    imbalance += std::abs(chamber_mass - mean);
  }

  Print(chamber_assignment, imbalance);
}

int main() {
  std::size_t num_chambers = 0, num_specimen = 0, t = 0;
  std::string line;
  std::vector<int> specimen_mass;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    specimen_mass.clear();
    std::istringstream tokenizer(line);
    tokenizer >> num_chambers >> num_specimen;

    specimen_mass.resize(num_specimen);
    std::getline(std::cin, line);
    std::istringstream mass_tokenizer(line);
    for (std::size_t i = 0; i < num_specimen; ++i) {
      mass_tokenizer >> specimen_mass[i];
    }

    printf("Set #%ld\n", ++t);
    AssignChambers(num_chambers, specimen_mass);
    printf("\n");
  }

  return 0;
}