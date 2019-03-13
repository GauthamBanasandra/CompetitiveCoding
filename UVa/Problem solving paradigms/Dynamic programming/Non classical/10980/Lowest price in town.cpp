#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

namespace uva10981
{
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
		// Had gone wrong here. I had assumed that the length will always be 4.
		std::string cents;
		cents.resize(cost.size() - 1, ' ');
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

		// The problem is wrong as it will always print the requested k as item count
		// But it may have chosen items more than k
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
}

int main(int argc, char* argv[])
{
	std::string line, price;
	std::size_t m, t = 0;
	int n, k;
	std::vector<uva10981::Deal> deals;

	while (std::getline(std::cin, line), !std::cin.eof())
	{
		deals.clear();
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

		uva10981::Selector selector(deals);

		std::getline(std::cin, line);
		std::istringstream k_tokenizer(line);
		while (k_tokenizer >> k)
		{
			selector.Buy(k).Print(k);
		}
	}
	return 0;
}
