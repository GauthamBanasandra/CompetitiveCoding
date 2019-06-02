#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

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

namespace uva_908
{
	int GetMinSpanningTreeCost(const std::size_t num_nodes,
		std::vector<std::tuple<int, std::size_t, std::size_t>>& edge_list)
	{
		std::sort(edge_list.begin(), edge_list.end(),
			[](const std::tuple<int, std::size_t, std::size_t>& a,
				const std::tuple<int, std::size_t, std::size_t>& b)->bool
			{
				return std::get<0>(a) < std::get<0>(b);
			});

		ds::ufds set(num_nodes + 1);
		auto total_cost = 0;
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
}

int main(int argc, char* argv[])
{
	std::size_t t = 0;
	std::size_t n, m, k, u, v;
	int cost;
	std::vector<std::tuple<int, std::size_t, std::size_t>> edge_list;

	while (std::cin >> n, !std::cin.eof())
	{
		auto total_cost = 0;
		for (std::size_t i = 0; i < n - 1; ++i)
		{
			std::cin >> u >> v >> cost;
			total_cost += cost;
		}

		std::cin >> k;
		edge_list.resize(k);
		for (std::size_t i = 0; i < k; ++i)
		{
			std::cin >> u >> v >> cost;
			edge_list[i] = std::make_tuple(cost, u, v);
		}

		std::cin >> m;
		edge_list.resize(k + m);
		for (std::size_t i = 0; i < m; ++i)
		{
			std::cin >> u >> v >> cost;
			edge_list[k + i] = std::make_tuple(cost, u, v);
		}

		if (t > 0)
		{
			std::cout << std::endl;
		}
		++t;
		std::cout << total_cost << std::endl;
		std::cout << uva_908::GetMinSpanningTreeCost(n, edge_list) << std::endl;
	}
	return 0;
}
