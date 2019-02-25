// WA

#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

const auto infinity = std::numeric_limits<long>::max();

struct Deal
{
	Deal() = default;
	Deal(const long num_items, const long cost) :num_items(num_items), cost(cost) {}
	Deal(int num_items, const std::string &cost);

	void Print(int k) const;

	long num_items{ -1 };
	long cost{ -1 };
};

class Selector
{
public:
	Selector(const std::vector<Deal> &deals);

	Deal Buy(long k);

private:
	std::vector<Deal> memo_;
	const std::vector<Deal> &deals_;
};

Deal::Deal(const int num_items, const std::string& cost) :num_items(num_items)
{
	std::string cents;
	cents.resize(4, ' ');
	std::size_t i_digit = 0;
	for (const auto d : cost)
	{
		if (d == '.')
		{
			continue;
		}
		cents[i_digit++] = d;
	}

	this->cost = std::stoi(cents);
}

void Deal::Print(const int k = -1) const
{
	const auto prefix_print = [](const long number)
	{
		if (number < 10)
		{
			std::cout << 0 << number;
		}
		else
		{
			std::cout << number;
		}
	};

	std::cout << "Buy " << (k == -1 ? num_items : k) << " for $" << cost / 100 << ".";
	prefix_print(cost % 100);
	std::cout << std::endl;
}

Selector::Selector(const std::vector<Deal>& deals) : deals_(deals)
{
	memo_.resize(100 + 1);
}

Deal Selector::Buy(const long k)
{
	if (k <= 0)
	{
		return {};
	}

	auto &memo = memo_[k];
	if (memo.num_items != -1)
	{
		return memo;
	}

	Deal best_deal{ infinity, infinity };
	for (const auto& deal : deals_)
	{
		auto cumulative = Buy(k - deal.num_items);
		if (cumulative.num_items != -1)
		{
			cumulative.num_items += deal.num_items;
			cumulative.cost += deal.cost;
		}
		else
		{
			cumulative = deal;
		}

		if (cumulative.cost < best_deal.cost)
		{
			best_deal = cumulative;
		}
	}
	return memo = best_deal;
}

int main(int argc, char* argv[])
{
	/*std::vector<Deal> deals1{
		{1, "22.00"},
		{2, "22.00"},
		{4, "60.00"}
	};
	Selector selector1(4, deals1);
	selector1.Buy(2).Print(2);
	selector1.Buy(4).Print(4);
	std::cout << std::endl;

	std::vector<Deal> deals2{
		{1, "25.00"},
		{2, "48.00"},
		{2, "46.00"}
	};
	Selector selector2(2, deals2);
	selector2.Buy(2).Print(2);
	std::cout << std::endl;

	std::vector<Deal> deals3{
		{1, "22.00"},
		{2, "22.00"},
		{4, "40.00"}
	};
	Selector selector3(4, deals3);
	selector3.Buy(1).Print(1);
	selector3.Buy(2).Print(2);
	selector3.Buy(3).Print(3);*/

	std::string line, price;
	std::size_t m, t = 0;
	int n, k;
	std::vector<Deal> deals;

	while (std::getline(std::cin, line), !std::cin.eof())
	{
		std::cout << "Case " << ++t << ":" << std::endl;
		std::istringstream tokenizer(line);
		tokenizer >> price >> m;

		deals.reserve(m + 1);
		deals.emplace_back(1, price);
		for (std::size_t i = 0; i < m; ++i)
		{
			std::getline(std::cin, line);
			std::istringstream item_tokenizer(line);

			item_tokenizer >> n >> price;
			deals.emplace_back(n, price);
		}

		Selector selector(deals);

		std::getline(std::cin, line);
		std::istringstream k_tokenizer(line);
		while (k_tokenizer >> k)
		{
			selector.Buy(k).Print(k);
		}
	}
	return 0;
}
