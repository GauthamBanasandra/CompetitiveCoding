//
// Created by Gautham on 13-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

namespace uva10819
{
	struct Item {
		Item() : price(0), value(0) {}
		Item(int price, int value) : price(price), value(value) {}

		int price;
		int value;
	};

	class Selector {
	public:
		explicit Selector(const std::vector<Item> &items, std::size_t budget);
		int Select();

	private:
		int Select(std::size_t i, int money_left, int money_spent, bool voucher_used);

		std::vector<std::vector<int>> memo_;
		const std::vector<Item> &items_;
		const int budget_;
	};

	Selector::Selector(const std::vector<Item> &items, const std::size_t budget)
		: items_(items), budget_(static_cast<int>(budget)) {
		memo_.resize(items_.size());
		for (auto &row : memo_) {
			row.resize(budget + 201, -1);
		}
	}

	int Selector::Select() {
		return Select(0, budget_, 0, false);
	}

	int Selector::Select(std::size_t i, int money_left, int money_spent, bool voucher_used) {
		if (i >= items_.size()) {
			return 0;
		}

		const auto &item = items_[i];
		if (money_spent + item.price > 2000 && !voucher_used) {
			money_left += 200;
			voucher_used = true;
		}

		if (item.price > money_left) {
			return Select(i + 1, money_left, money_spent, voucher_used);
		}

		auto &memo = memo_[i][money_left];
		if (memo != -1) {
			return memo;
		}

		return memo = std::max(Select(i + 1, money_left, money_spent, voucher_used),
		                       Select(i + 1, money_left - item.price, money_spent + item.price, voucher_used) + item.value);
	}
}

int main() {
  int budget = 1801;
  std::size_t num_items;
  std::vector<uva10819::Item> items{
      {2000, 3},
      {1900, 1},
      {101, 1}
  };

//  std::cout << Selector(items, static_cast<std::size_t>(budget)).Select() << std::endl;

  while (std::cin >> budget >> num_items, !std::cin.eof()) {
    items.resize(num_items);
    for (std::size_t i = 0; i < num_items; ++i) {
      std::cin >> items[i].price >> items[i].value;
    }

    std::sort(items.begin(), items.end(), [](const uva10819::Item &a, const uva10819::Item &b)->bool{
      return a.price < b.price;
    });
    std::cout << uva10819::Selector(items, static_cast<std::size_t>(budget)).Select() << std::endl;
  }
  return 0;
}