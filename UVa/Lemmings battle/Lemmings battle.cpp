#include <iostream>
#include <set>
#include <queue>

enum class lemmings_race { blue, green };

enum class outcome { live, die, both_die };

class lemmings
{
public:
	lemmings(const int power, const lemmings_race race) : power(power), race(race) {}
	outcome fight(lemmings &other);

	int power;
	lemmings_race race;
};

inline outcome lemmings::fight(lemmings& other)
{
	if (power < other.power)
	{
		other.power -= power;
		power = 0;
		return outcome::die;
	}

	if (power > other.power)
	{
		power -= other.power;
		other.power = 0;
		return outcome::live;
	}

	power = other.power = 0;
	return outcome::both_die;
}

struct lemmings_comparator
{
	bool operator()(const lemmings& lem1, const lemmings& lem2) const
	{
		if (lem1.power > lem2.power)
		{
			return true;
		}

		return false;
	}
};

struct battle
{
	battle(const lemmings& blue_lemming, const lemmings& green_lemming)
		: blue_lemming(blue_lemming),
		green_lemming(green_lemming)
	{
	}

	lemmings blue_lemming;
	lemmings green_lemming;
};

class deadly_war
{
public:
	deadly_war(std::multiset<lemmings, lemmings_comparator> &&blue_lemmings, std::multiset<lemmings, lemmings_comparator> &&green_lemmings,
		const long battle_grounds)
		: blue_lemmings(move(blue_lemmings)),
		green_lemmings(move(green_lemmings)),
		battle_grounds_(battle_grounds)
	{
	}


	bool is_war_over();
	bool next_round();

	std::multiset<lemmings, lemmings_comparator> blue_lemmings;
	std::multiset<lemmings, lemmings_comparator> green_lemmings;

private:
	std::queue<battle> battles_;
	long int battle_grounds_;
};

inline bool deadly_war::is_war_over()
{
	if (blue_lemmings.empty() && green_lemmings.empty())
	{
		std::cout << "green and blue died" << std::endl;
		return true;
	}

	if (green_lemmings.empty())
	{
		std::cout << "blue wins" << std::endl;
		for (const auto & blue_lemming : blue_lemmings)
		{
			std::cout << blue_lemming.power << std::endl;
		}

		return true;
	}

	if (blue_lemmings.empty())
	{
		std::cout << "green wins" << std::endl;
		for (const auto & green_lemming : green_lemmings)
		{
			std::cout << green_lemming.power << std::endl;
		}

		return true;
	}

	return false;
}

bool deadly_war::next_round()
{
	if (is_war_over())
	{
		return false;
	}

	while (battles_.size() < battle_grounds_ && !blue_lemmings.empty() && !green_lemmings.empty())
	{
		const auto &blue_lemming_it = blue_lemmings.begin();
		const auto &green_lemming_it = green_lemmings.begin();
		const battle battle{ *blue_lemming_it, *green_lemming_it };
		blue_lemmings.erase(blue_lemming_it);
		green_lemmings.erase(green_lemming_it);

		battles_.push(std::move(battle));
	}

	while (!battles_.empty())
	{
		auto &battle = battles_.front();
		switch (battle.blue_lemming.fight(battle.green_lemming))
		{
		case outcome::live:
			blue_lemmings.insert(std::move(battle.blue_lemming));
			break;

		case outcome::die:
			green_lemmings.insert(std::move(battle.green_lemming));
			break;

		case outcome::both_die:;
		default:
			break;
		}

		battles_.pop();
	}

	return true;
}

void print_lemmings(std::multiset<lemmings, lemmings_comparator> green_lemmings, std::multiset<lemmings, lemmings_comparator> blue_lemmings)
{
	std::cout << "Green lemmings:" << std::endl;
	for (auto green_lemming : green_lemmings)
	{
		std::cout << green_lemming.power << std::endl;
	}

	std::cout << "Blue lemmings:" << std::endl;
	for (auto blue_lemming : blue_lemmings)
	{
		std::cout << blue_lemming.power << std::endl;
	}

	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	int n, c = 0;
	long int b, sg, sb, power;
	std::cin >> n;
	std::multiset<lemmings, lemmings_comparator> green_lemmings;
	std::multiset<lemmings, lemmings_comparator> blue_lemmings;
	while (n--)
	{
		blue_lemmings.clear();
		green_lemmings.clear();
		std::cin >> b >> sg >> sb;
		while (sg--)
		{
			std::cin >> power;
			lemmings green(power, lemmings_race::green);
			green_lemmings.insert(std::move(green));
		}

		while (sb--)
		{
			std::cin >> power;
			lemmings blue(power, lemmings_race::blue);
			blue_lemmings.insert(std::move(blue));
		}

		if (c++ > 0)
		{
			std::cout << std::endl;
		}

		deadly_war war(move(blue_lemmings), move(green_lemmings), b);
		while (war.next_round())
		{
		}
	}

	return 0;
}
