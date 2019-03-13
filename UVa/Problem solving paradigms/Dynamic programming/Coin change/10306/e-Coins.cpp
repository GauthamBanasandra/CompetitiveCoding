#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr auto infinity = std::numeric_limits<long>::max();

struct ECoin
{
	ECoin() :conventional_value(0), info_tech_value(0) {}
	ECoin(const long conventional_value, const long info_tech_value) : conventional_value(conventional_value), info_tech_value(info_tech_value) {}

	long EModulus() const { return conventional_value * conventional_value + info_tech_value * info_tech_value; }
	ECoin operator+(const ECoin& other) const { return { conventional_value + other.conventional_value, info_tech_value + other.info_tech_value }; }

	long conventional_value;
	long info_tech_value;
};

class ChangeMaker
{
public:
	ChangeMaker(const std::vector<ECoin> &e_coins, const long target);
	long Count() { return Count(ECoin()); }

private:
	long Count(ECoin sum);

	const long target_;
	std::vector<std::vector<long>> memo_;
	const std::vector<ECoin> &e_coins_;
};

ChangeMaker::ChangeMaker(const std::vector<ECoin>& e_coins, const long target) : target_(target * target), e_coins_(e_coins)
{
	memo_.resize(500, std::vector<long>(500, -1));
}

long ChangeMaker::Count(ECoin sum)
{
	const auto value = sum.EModulus();
	if (target_ - value < 0)
	{
		return infinity;
	}

	if (target_ - value == 0)
	{
		return 0;
	}

	auto &memo = memo_[sum.conventional_value][sum.info_tech_value];
	if (memo != -1)
	{
		return memo;
	}

	auto min_coins = infinity;
	for (const auto &e_coin : e_coins_)
	{
		min_coins = std::min(min_coins, Count(sum + e_coin));
	}
	return memo = min_coins == infinity ? infinity : min_coins + 1;
}

int main(int argc, char* argv[])
{
	auto n = 0;
	std::size_t num_coins;
	long target = 12;
	std::vector<ECoin> e_coins;

	std::cin >> n;
	while (n-- > 0)
	{
		std::cin >> num_coins >> target;
		e_coins.resize(num_coins);
		for (std::size_t i = 0; i < num_coins; ++i)
		{
			std::cin >> e_coins[i].conventional_value >> e_coins[i].info_tech_value;
		}

		const auto min_coins = ChangeMaker(e_coins, target).Count();
		if (min_coins == infinity)
		{
			std::cout << "not possible" << std::endl;
		}
		else
		{
			std::cout << min_coins << std::endl;
		}
	}
	return 0;
}
