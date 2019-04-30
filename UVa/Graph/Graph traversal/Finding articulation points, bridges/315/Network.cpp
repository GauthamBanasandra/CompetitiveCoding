#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <ios>

namespace uva315
{
	const auto unvisited = -1;

	class GraphCheck
	{
	public:
		GraphCheck(const std::vector<std::vector<int>>& adj_list, int num_nodes);

		int CountArticulationPoints();

	private:
		void Count(int node);

		const int num_nodes_;
		const std::vector<std::vector<int>>& adj_list_;
		std::vector<int> parent_;
		std::vector<int> is_articulation_point_;
		std::vector<int> visit_order_;
		std::vector<int> lowest_reachable_;

		int current_root_{ 0 };
		int num_root_children_{ 0 };
		int order_{ 0 };
	};

	GraphCheck::GraphCheck(const std::vector<std::vector<int>>& adj_list,
		const int num_nodes) :num_nodes_(num_nodes), adj_list_(adj_list)
	{
		parent_.resize(num_nodes_);
		is_articulation_point_.resize(num_nodes_);
		visit_order_.resize(num_nodes_, unvisited);
		lowest_reachable_.resize(num_nodes_);
	}

	int GraphCheck::CountArticulationPoints()
	{
		for (auto i = 1; i < num_nodes_; ++i)
		{
			if (visit_order_[i] != unvisited)
			{
				continue;
			}

			current_root_ = i;
			num_root_children_ = 0;
			Count(i);
			is_articulation_point_[current_root_] = num_root_children_ > 1;
		}
		return std::count_if(is_articulation_point_.begin(),
			is_articulation_point_.end(), [](const int item)->bool
			{
				return item == 1;
			});
	}

	void GraphCheck::Count(const int node)
	{
		visit_order_[node] = lowest_reachable_[node] = ++order_;
		for (const auto adj_node : adj_list_[node])
		{
			if (visit_order_[adj_node] == unvisited)
			{
				parent_[adj_node] = node;
				if (node == current_root_)
				{
					++num_root_children_;
				}

				Count(adj_node);

				if (lowest_reachable_[adj_node] >= visit_order_[node])
				{
					is_articulation_point_[node] = 1;
				}
				lowest_reachable_[node] = std::min(
					lowest_reachable_[node], lowest_reachable_[adj_node]);
			}
			else if (parent_[node] != adj_node)
			{
				lowest_reachable_[node] = std::min(
					lowest_reachable_[node], visit_order_[adj_node]);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int num_nodes;
	int node;
	int adj_node;
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
		std::istringstream num_nodes_tokenizer(line);
		num_nodes_tokenizer >> num_nodes;
		if (num_nodes == 0)
		{
			break;
		}

		std::vector<std::vector<int>> adj_list(num_nodes + 1);

		while (true)
		{
			std::getline(std::cin, line);
			std::istringstream nodes_tokenizer(line);
			nodes_tokenizer >> node;
			if (node == 0)
			{
				break;
			}

			while (nodes_tokenizer >> adj_node)
			{
				adj_list[node].emplace_back(adj_node);
				adj_list[adj_node].emplace_back(node);
			}
		}

		uva315::GraphCheck check(adj_list, num_nodes + 1);
		std::cout << check.CountArticulationPoints() << std::endl;
	}
	return 0;
}
