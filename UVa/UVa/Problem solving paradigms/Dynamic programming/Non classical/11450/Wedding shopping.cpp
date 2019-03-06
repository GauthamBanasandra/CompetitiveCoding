#include <vector>
#include <string>
#include <iostream>
#include <ios>

namespace uva11450
{
	class Selector
	{
	public:
		Selector(const std::vector<std::vector<int>> &garments, int money);

		std::string Select();

	private:
		const int money_;
		const std::vector<std::vector<int>>& garments_;
		std::vector<std::vector<short>> memo_;
	};

	Selector::Selector(const std::vector<std::vector<int>>& garments, const int money) :money_(money), garments_(garments)
	{
		memo_.resize(garments_.size(), std::vector<short>(money_ + 1));
	}

	std::string Selector::Select()
	{
		for (const auto model : garments_.front())
		{
			if (money_ - model < 0)
			{
				continue;
			}
			memo_[0][money_ - model] = 1;
		}

		for (std::size_t i = 1, len = garments_.size(); i < len; ++i)
		{
			for (auto j = 0; j <= money_; ++j)
			{
				if (memo_[i - 1][j] == 0)
				{
					continue;
				}

				for (const auto model : garments_[i])
				{
					if (j - model < 0)
					{
						continue;
					}
					memo_[i][j - model] = 1;
				}
			}
		}

		auto i_min = 0;
		for (const auto value : memo_.back())
		{
			if (value == 1)
			{
				break;
			}
			++i_min;
		}

		if (i_min > money_)
		{
			return "no solution";
		}
		return std::to_string(money_ - i_min);
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int money;
	std::size_t t;
	std::size_t num_garments;
	std::size_t num_models;
	std::vector<std::vector<int>> garments;

	std::cin >> t;
	while (t--)
	{
		std::cin >> money >> num_garments;
		garments.resize(num_garments);

		for (std::size_t i = 0; i < num_garments; ++i)
		{
			std::cin >> num_models;
			garments[i].resize(num_models);

			for (std::size_t j = 0; j < num_models; ++j)
			{
				std::cin >> garments[i][j];
			}
		}

		uva11450::Selector selector(garments, money);
		std::cout << selector.Select() << std::endl;
	}
	return 0;
}
