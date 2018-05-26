//
// Created by gauth on 20-01-2018.
//

#include <array>
#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>

void Print(const std::vector<int> &nums);

std::string HashScores(int s1, int s2, int s3) {
  std::array<int, 3> scores{s1, s2, s3};
  std::sort(scores.begin(), scores.end());
  std::string scores_hash;
  for (const auto &s: scores) {
    scores_hash += std::to_string(s) + " ";
  }

  scores_hash.pop_back();
  return scores_hash;
}

int main() {
  std::unordered_set<int> possible_unique_scores;
  for (int i = 0, j = 0; i < 21 * 3; i += 3, ++j) {
    possible_unique_scores.insert(j);
    possible_unique_scores.insert(j * 2);
    possible_unique_scores.insert(j * 3);
  }

  std::vector<int> possible_scores(possible_unique_scores.begin(), possible_unique_scores.end());
  possible_scores.push_back(50);

  int score;
  std::string delimiter(70, '*');
  std::unordered_set<std::string> combinations;
  while (std::cin >> score, score > 0) {
    int n_p = 0;
    combinations.clear();
    for (int i = 0; i < possible_scores.size(); ++i) {
      for (int j = 0; j < possible_scores.size(); ++j) {
        for (int k = 0; k < possible_scores.size(); ++k) {
          if (possible_scores[i] + possible_scores[j] + possible_scores[k] == score) {
            ++n_p;
            combinations.insert(HashScores(possible_scores[i], possible_scores[j], possible_scores[k]));
          }
        }
      }
    }

    if (n_p) {
      printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n", score, combinations.size());
      printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n", score, n_p);
    } else {
      printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n", score);
    }

    std::cout << delimiter << std::endl;
  }

  std::cout << "END OF OUTPUT" << std::endl;
  return 0;
}