//
// Created by Gautham on 01-11-2018.
//

#include <iostream>
#include <vector>
#include <ios>

using Plot = std::vector<std::vector<long>>;
void Print(const Plot &plot);

struct Deal {
  Deal() : area(0), cost(0) {}
  Deal(size_t area, long cost) : area(area), cost(cost) {}

  std::size_t area;
  long cost;
};

class Broker {
 public:
  Broker(Plot plot, long money);

  Deal GetBestDeal() const;

 private:
  Deal GetDeal(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const;

  Plot cumulative_plot_;
  const long money_;
};

Broker::Broker(Plot plot, const long money) : cumulative_plot_(std::move(plot)), money_(money) {
  for (std::size_t i = 0, row_len = cumulative_plot_.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = cumulative_plot_[i].size(); j < column_len; ++j) {
      if (i > 0) {
        cumulative_plot_[i][j] += cumulative_plot_[i - 1][j];
      }
      if (j > 0) {
        cumulative_plot_[i][j] += cumulative_plot_[i][j - 1];
      }
      if (i > 0 && j > 0) {
        cumulative_plot_[i][j] -= cumulative_plot_[i - 1][j - 1];
      }
    }
  }
}

Deal Broker::GetBestDeal() const {
  Deal best_deal;
  for (std::size_t i = 0, row_len = cumulative_plot_.size(); i < row_len; ++i) {
    for (std::size_t j = 0, column_len = cumulative_plot_[i].size(); j < column_len; ++j) {
      for (std::size_t k = i; k < row_len; ++k) {
        for (std::size_t l = j; l < column_len; ++l) {
          auto deal = GetDeal(i, j, k, l);
          if (deal.cost > money_) {
            continue;
          }

          if ((deal.area > best_deal.area) || (deal.area == best_deal.area && deal.cost < best_deal.cost)) {
            best_deal = deal;
          }
        }
      }
    }
  }
  return best_deal;
}

Deal Broker::GetDeal(std::size_t i, std::size_t j, std::size_t k, std::size_t l) const {
  auto cost = cumulative_plot_[k][l];
  if (i > 0) {
    cost -= cumulative_plot_[i - 1][l];
  }
  if (j > 0) {
    cost -= cumulative_plot_[k][j - 1];
  }
  if (i > 0 && j > 0) {
    cost += cumulative_plot_[i - 1][j - 1];
  }
  auto area = (k - i + 1) * (l - j + 1);
  return {area, cost};
}

int main() {
  std::ios::sync_with_stdio(false);

  int t;
  std::size_t n, m;
  long k;
  Plot plot;

  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    std::cin >> n >> m >> k;

    plot.resize(n);
    for (std::size_t p = 0; p < n; ++p) {
      plot[p].resize(m);
      for (int q = 0; q < m; ++q) {
        std::cin >> plot[p][q];
      }
    }

    auto best_deal = Broker(plot, k).GetBestDeal();
    std::cout << "Case #" << i << ": " << best_deal.area << " " << best_deal.cost << std::endl;
  }
  return 0;
}