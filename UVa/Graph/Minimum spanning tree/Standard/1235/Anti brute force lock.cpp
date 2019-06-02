#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <ios>

namespace ds
{
	class ufds
	{
	public:
		explicit ufds(std::size_t size);
		std::size_t find_set(std::size_t i);
		bool is_same_set(std::size_t i, std::size_t j);
		void union_set(std::size_t i, std::size_t j);

		std::size_t size;
		std::vector<std::size_t> parent_index;
		std::vector<std::size_t> rank;
	};

	inline ufds::ufds(const std::size_t size) : size(size)
	{
		rank.assign(size, 0);

		for (std::size_t i = 0; i < size; ++i)
		{
			parent_index.emplace_back(i);
		}
	}

	inline std::size_t ufds::find_set(const std::size_t i)
	{
		if (parent_index[i] == i)
		{
			return i;
		}

		parent_index[i] = find_set(parent_index[i]);
		return parent_index[i];
	}

	inline bool ufds::is_same_set(const std::size_t i, const std::size_t j)
	{
		return find_set(i) == find_set(j);
	}

	inline void ufds::union_set(const std::size_t i, const std::size_t j)
	{
		if (!is_same_set(i, j))
		{
			const auto parent_i = find_set(i);
			const auto parent_j = find_set(j);
			if (rank[parent_i] > rank[parent_j])
			{
				parent_index[parent_j] = parent_i;
			}
			else
			{
				parent_index[parent_i] = parent_j;
				if (rank[parent_i] == rank[parent_j])
				{
					++rank[parent_j];
				}
			}
		}
	}
}

namespace uva_1235
{
	const auto infinity = std::numeric_limits<int>::max();

	class Hacker
	{
	public:
		explicit Hacker(const std::vector<std::string>& pins) : pins_(pins) {}

		int GetMinRolls() const;

	private:
		std::vector<std::tuple<int, std::size_t, std::size_t>> GetEdgeList() const;
		int GetInitialDistance() const;
		static int GetDistance(const std::string& s1, const std::string& s2);

		const std::vector<std::string>& pins_;
	};

	int Hacker::GetMinRolls() const
	{
		auto edge_list = GetEdgeList();
		std::sort(edge_list.begin(), edge_list.end(),
			[](const std::tuple<int, std::size_t, std::size_t>& a,
				const std::tuple<int, std::size_t, std::size_t>& b)->bool
			{
				return std::get<0>(a) < std::get<0>(b);
			});

		const auto len = pins_.size();
		std::vector<int> visited(len);
		auto total_cost = GetInitialDistance();
		ds::ufds set(len);

		for (const auto& edge : edge_list)
		{
			auto& [cost, u, v] = edge;
			if (!set.is_same_set(u, v))
			{
				total_cost += cost;
				set.union_set(u, v);
			}
		}
		return total_cost;
	}

	std::vector<std::tuple<int, std::size_t, std::size_t>>
		Hacker::GetEdgeList() const
	{
		const auto len = pins_.size();
		std::vector<std::tuple<int, std::size_t, std::size_t>> edge_list;
		edge_list.reserve(len * (len - 1) / 2);

		for (std::size_t i = 0; i < len; ++i)
		{
			for (std::size_t j = 0; j < len; ++j)
			{
				if (i != j)
				{
					edge_list.emplace_back(GetDistance(pins_[i], pins_[j]), i, j);
				}
			}
		}
		return edge_list;
	}

	int Hacker::GetInitialDistance() const
	{
		const std::string initial = "0000";
		auto min_distance = infinity;
		for (const auto& pin : pins_)
		{
			min_distance = std::min(min_distance, GetDistance(initial, pin));
		}
		return min_distance;
	}

	int Hacker::GetDistance(const std::string& s1, const std::string& s2)
	{
		const auto len = s1.size();
		auto distance = 0;
		for (std::size_t i = 0; i < len; ++i)
		{
			const auto d = s1[i] - s2[i];
			distance += std::min(std::abs(d), 10 - std::abs(d));
		}
		return distance;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t t;
	std::size_t num_pins;
	std::vector<std::string> pins;

	std::cin >> t;
	while (t--)
	{
		std::cin >> num_pins;
		pins.resize(num_pins);
		for (std::size_t i = 0; i < num_pins; ++i)
		{
			std::cin >> pins[i];
		}

		std::cout << uva_1235::Hacker(pins).GetMinRolls() << std::endl;
	}
	return 0;
}
