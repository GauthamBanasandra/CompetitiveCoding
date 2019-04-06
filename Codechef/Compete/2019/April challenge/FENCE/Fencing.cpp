// TLE

#include <unordered_set>
#include <vector>
#include <iostream>

namespace april_challenge_2019
{
	using ll = long long;

	struct Pos
	{
		Pos() = default;
		Pos(const ll x, const ll y) :x(x), y(y) {}

		bool operator==(const Pos& other) const { return x == other.x && y == other.y; }
		std::size_t operator()(const Pos& pos) const { return x * 1'000'000'000 + y; }

		ll x{ 0 };
		ll y{ 0 };
	};

	class Traversal
	{
	public:
		Traversal(ll n, ll m, const std::unordered_set<Pos, Pos>& plants_pos);

		ll GetFences();

	private:
		ll Next(Pos pos);
		bool IsOutside(const Pos& pos) const
		{
			return pos.x < 1 || pos.x > num_rows_ || pos.y < 1 || pos.y > num_columns_;
		}

		const ll num_rows_;
		const ll num_columns_;
		const std::unordered_set<Pos, Pos>& plants_pos_;
		std::unordered_set<Pos, Pos> visited_;

		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> Traversal::directions_;

	Traversal::Traversal(const ll n, const ll m, const std::unordered_set<Pos, Pos>& plants_pos) :
		num_rows_(n), num_columns_(m), plants_pos_(plants_pos)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		}
	}

	ll Traversal::GetFences()
	{
		ll count = 0;
		for (const auto& pos : plants_pos_)
		{
			if (visited_.find(pos) == visited_.end())
			{
				count += Next(pos);
			}
		}
		return count;
	}

	ll Traversal::Next(const Pos pos)
	{
		if (IsOutside(pos) || plants_pos_.find(pos) == plants_pos_.end())
		{
			return 1;
		}
		if (visited_.find(pos) != visited_.end())
		{
			return 0;
		}
		visited_.insert(pos);

		ll count = 0;
		for (const auto& direction : directions_)
		{
			count += Next({ pos.x + direction.first, pos.y + direction.second });
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	int t;
	april_challenge_2019::ll n;
	april_challenge_2019::ll m;
	april_challenge_2019::ll x;
	april_challenge_2019::ll y;
	std::size_t k;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n >> m >> k;
		std::unordered_set<april_challenge_2019::Pos, april_challenge_2019::Pos> plants_pos;
		for (std::size_t i = 0; i < k; ++i)
		{
			std::cin >> x >> y;
			plants_pos.emplace(x, y);
		}
		april_challenge_2019::Traversal traversal(n, m, plants_pos);
		std::cout << traversal.GetFences() << std::endl;
	}
	return 0;
}
