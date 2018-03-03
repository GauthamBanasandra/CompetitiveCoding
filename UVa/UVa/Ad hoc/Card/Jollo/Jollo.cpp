//
// Created by gauth on 03-03-2018.
//

#include <iostream>
#include <vector>

enum class Victory { k_prince, k_princess };
const int n_cards = 3;

Victory BeginGame(const std::vector<int> &princess_cards, const std::vector<int> &prince_cards) {
  /*
   (3 x 3) x (2 x 2) x (1 x 1)
   The following loop generates the above permutation.
   In each item (a, b) , the first card belongs to the princess and the second cards belongs to the prince.
   */
  for (int i = 0; i < n_cards; ++i) {
    for (int j = 0; j < n_cards; ++j) {
      for (int k = 0; k < n_cards; ++k) {
        if (i == k) {
          continue;
        }

        for (int l = 0; l < n_cards; ++l) {
          if (j == l) {
            continue;
          }

          for (int m = 0; m < n_cards; ++m) {
            if (m == i || m == k) {
              continue;
            }

            for (int n = 0; n < n_cards; ++n) {
              if (n == j || n == l) {
                continue;
              }

              auto prince_wins = 0, princess_wins = 0;
              if (princess_cards[i] > prince_cards[j]) {
                ++princess_wins;
              } else {
                ++prince_wins;
              }

              if (princess_cards[k] > prince_cards[l]) {
                ++princess_wins;
              } else {
                ++prince_wins;
              }

              if (princess_cards[m] > prince_cards[n]) {
                ++princess_wins;
              } else {
                ++prince_wins;
              }

              if (princess_wins > prince_wins) {
                return Victory::k_princess;
              }
            }
          }
        }
      }
    }
  }

  return Victory::k_prince;
}

int main() {
  int a, b, c, x, y;
  std::vector<int> princess_cards, prince_cards;

  while (std::cin >> a >> b >> c >> x >> y, a || b || c || x || y) {
    princess_cards.clear();
    prince_cards.clear();

    princess_cards.emplace_back(a);
    princess_cards.emplace_back(b);
    princess_cards.emplace_back(c);

    prince_cards.emplace_back(x);
    prince_cards.emplace_back(y);
    prince_cards.emplace_back(0);

    int z;
    auto victory = Victory::k_princess;
    for (z = 1; z <= 52; ++z) {
      if (z == a || z == b || z == c || z == x || z == y) {
        continue;
      }

      prince_cards[n_cards - 1] = z;
      victory = BeginGame(princess_cards, prince_cards);
      if (victory == Victory::k_prince) {
        break;
      }
    }

    switch (victory) {
      case Victory::k_prince:std::cout << z << std::endl;
        break;

      case Victory::k_princess:std::cout << -1 << std::endl;
        break;
    }
  }

  return 0;
}