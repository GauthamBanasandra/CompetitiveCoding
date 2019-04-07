// WA

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cassert>

using ll = long long;

class Traversal
{
public:
	Traversal(ll x, const std::vector<std::pair<ll, ll>>& edge_list,
		std::vector<ll>& nodes_value);

	ll GetMaxProfit() const { return DFS(1); }

private:
	ll DFS(ll node) const;

	const ll x_;
	const std::vector<ll>& nodes_value_;
	std::unordered_map<ll, std::vector<ll>> adj_list_;
};

Traversal::Traversal(const ll x, const std::vector<std::pair<ll, ll>>& edge_list,
	std::vector<ll>& nodes_value) :x_(x), nodes_value_(nodes_value)
{
	for (const auto& edge : edge_list)
	{
		adj_list_[edge.first].emplace_back(edge.second);
	}
}

ll Traversal::DFS(const ll node) const
{
	auto max_profit = nodes_value_[node];
	const auto find_it = adj_list_.find(node);
	if (find_it != adj_list_.end())
	{
		for (const auto adj_node : find_it->second)
		{
			max_profit += DFS(adj_node);
		}
	}
	return std::max(max_profit, -x_);
}

int main(ll argc, char* argv[])
{
	ll t;
	std::size_t n;
	ll x;
	std::vector<std::pair<ll, ll>> edge_list;
	std::vector<ll> nodes_value;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n >> x;
		edge_list.resize(n - 1);
		nodes_value.resize(n + 1);

		for (std::size_t i = 1; i <= n; ++i)
		{
			std::cin >> nodes_value[i];
		}

		for (std::size_t i = 0; i < n - 1; ++i)
		{
			std::cin >> edge_list[i].first >> edge_list[i].second;
		}

		Traversal traversal(x, edge_list, nodes_value);
		std::cout << traversal.GetMaxProfit() << std::endl;
	}
	return 0;
}
