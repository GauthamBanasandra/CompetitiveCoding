#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

namespace april_challenge_2019
{
	using ll = long long;

	class Traversal
	{
	public:
		Traversal(ll x, const std::vector<std::pair<int, int>>& edge_list,
			std::vector<int>& nodes_value);

		ll GetMaxProfit() { return DFS(1); }

	private:
		ll DFS(int node);

		const ll x_;
		const std::vector<int>& nodes_value_;
		std::vector<int> visited_;
		std::vector<std::vector<int>> adj_list_;
	};

	Traversal::Traversal(const ll x, const std::vector<std::pair<int, int>>& edge_list,
		std::vector<int>& nodes_value) :x_(x), nodes_value_(nodes_value)
	{
		const auto len = nodes_value_.size();
		visited_.resize(len);
		adj_list_.resize(len);

		for (const auto& edge : edge_list)
		{
			adj_list_[edge.first].emplace_back(edge.second);
			adj_list_[edge.second].emplace_back(edge.first);
		}
	}

	ll Traversal::DFS(const int node)
	{
		visited_[node] = 1;

		ll max_profit = nodes_value_[node];
		for (const auto adj_node : adj_list_[node])
		{
			if (visited_[adj_node] == 1)
			{
				continue;
			}
			max_profit += DFS(adj_node);
		}
		return std::max(max_profit, -x_);
	}
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	april_challenge_2019::ll x;
	std::vector<std::pair<int, int>> edge_list;
	std::vector<int> nodes_value;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n >> x;
		edge_list.resize(n - 1);
		nodes_value.resize(n + 1);

		for (auto i = 1; i <= n; ++i)
		{
			std::cin >> nodes_value[i];
		}

		for (auto i = 0; i < n - 1; ++i)
		{
			std::cin >> edge_list[i].first >> edge_list[i].second;
		}

		april_challenge_2019::Traversal traversal(x, edge_list, nodes_value);
		std::cout << traversal.GetMaxProfit() << std::endl;
	}
	return 0;
}
