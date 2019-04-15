#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

namespace april_challenge_2019
{
	using ll = long long;

	struct Pos
	{
		Pos() = default;
		Pos(const ll x, const ll y) :x(x), y(y) {}

		std::string GetHash() const { return std::to_string(x) + " " + std::to_string(y); }

		ll x{ 0 };
		ll y{ 0 };
	};

	class Traversal
	{
	public:
		Traversal(ll n, ll m, const std::vector<Pos>& plants_pos);

		ll GetFences();

	private:
		ll Next(Pos pos);
		bool IsOutside(const Pos& pos) const
		{
			return pos.x < 1 || pos.x > num_rows_ || pos.y < 1 || pos.y > num_columns_;
		}

		const ll num_rows_;
		const ll num_columns_;
		const std::vector<Pos>& plants_pos_;
		std::unordered_set<std::string> visited_;
		std::unordered_set<std::string> plants_pos_set_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> Traversal::directions_;

	Traversal::Traversal(const ll n, const ll m, const std::vector<Pos>& plants_pos) :
		num_rows_(n), num_columns_(m), plants_pos_(plants_pos)
	{
		for (const auto& pos : plants_pos_)
		{
			plants_pos_set_.insert(pos.GetHash());
		}
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
			if (visited_.find(pos.GetHash()) == visited_.end())
			{
				count += Next(pos);
			}
		}
		return count;
	}

	ll Traversal::Next(const Pos pos)
	{
		if (IsOutside(pos) || plants_pos_set_.find(pos.GetHash()) == plants_pos_set_.end())
		{
			return 1;
		}
		if (visited_.find(pos.GetHash()) != visited_.end())
		{
			return 0;
		}
		visited_.insert(pos.GetHash());

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
	std::size_t k;
	std::vector<april_challenge_2019::Pos> plants_pos;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n >> m >> k;
		plants_pos.resize(k);
		for (std::size_t i = 0; i < k; ++i)
		{
			std::cin >> plants_pos[i].x >> plants_pos[i].y;
		}
		april_challenge_2019::Traversal traversal(n, m, plants_pos);
		std::cout << traversal.GetFences() << std::endl;
	}
	return 0;
}
