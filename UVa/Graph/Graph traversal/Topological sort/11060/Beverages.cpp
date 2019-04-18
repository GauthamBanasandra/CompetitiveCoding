// WA

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <iostream>

class TopologicalSort
{
public:
	TopologicalSort(const std::vector<std::string>& beverages,
		const std::vector<std::pair<std::string, std::string>>& edge_list);

	std::vector<std::string> Sort();

private:
	void DFS(const std::string& node, std::vector<std::string>& order);

	const std::vector<std::string>& beverages_;
	std::unordered_set<std::string> visited_;
	std::unordered_map<std::string, int> bev_index_;
	std::unordered_map<std::string, std::vector<std::string>> adj_list_;
};

TopologicalSort::TopologicalSort(
	const std::vector<std::string>& beverages,
	const std::vector<std::pair<std::string, std::string>>&
	edge_list) :beverages_(beverages)
{
	for (const auto& edge : edge_list)
	{
		adj_list_[edge.first].emplace_back(edge.second);
	}

	for (auto i = 0, len = static_cast<int>(beverages.size()); i < len; ++i)
	{
		bev_index_[beverages[i]] = i + 1;
	}

	for (auto& adj_list : adj_list_)
	{
		std::sort(adj_list.second.begin(), adj_list.second.end(),
			[this](const std::string & b1, const std::string & b2)->bool
			{
				return bev_index_[b1] < bev_index_[b2];
			});
	}
}

std::vector<std::string> TopologicalSort::Sort()
{
	std::vector<std::string> order;
	for (const auto& beverage : beverages_)
	{
		if (visited_.find(beverage) == visited_.end())
		{
			DFS(beverage, order);
		}
	}
	std::reverse(order.begin(), order.end());
	return order;
}

void TopologicalSort::DFS(const std::string& node, std::vector<std::string>& order)
{
	visited_.insert(node);
	for (const auto& adj_node : adj_list_[node])
	{
		if (visited_.find(adj_node) == visited_.end())
		{
			DFS(adj_node, order);
		}
	}

	std::sort(order.begin(), order.begin() + adj_list_[node].size(),
		[this](const std::string & b1, const std::string & b2)->bool
		{
			return bev_index_[b1] < bev_index_[b2];
		});
	order.emplace_back(node);
}

int main(int argc, char* argv[])
{
	int n;
	int m;
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
		if (std::cin.eof())
		{
			break;
		}

		std::vector<std::string> beverages;
		std::vector<std::pair<std::string, std::string>> edge_list;

		std::istringstream n_tokenizer(line);
		n_tokenizer >> n;
		beverages.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::getline(std::cin, beverages[i]);
		}

		std::getline(std::cin, line);
		std::istringstream m_tokenizer(line);
		m_tokenizer >> m;
		edge_list.resize(m);
		for (auto i = 0; i < m; ++i)
		{
			std::getline(std::cin, line);
			std::istringstream edge_list_tokenizer(line);
			edge_list_tokenizer >> edge_list[i].first >> edge_list[i].second;
		}

		TopologicalSort sorter(beverages, edge_list);
		auto separator = "";
		for (const auto& beverage : sorter.Sort())
		{
			std::cout << separator << beverage;
			separator = " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
