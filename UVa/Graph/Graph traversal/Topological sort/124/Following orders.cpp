// WIP

#include <vector>
#include <queue>
#include <iostream>

class Possibilities
{
public:
	explicit Possibilities(std::size_t num_nodes);

	void AddPossibility(const std::vector<char>& nodes);
	std::vector<std::vector<char>> GetAll() const;

private:
	const std::size_t num_nodes_;
	std::size_t i_data_{ 0 };
	std::vector<std::vector<char>> data_;
};

class TopologicalSort
{
public:
	TopologicalSort(const std::vector<char>& nodes,
		const std::vector<std::pair<char, char>>& edge_list);

	std::vector<std::vector<char>> GetAllOrderings();

private:
	const std::size_t num_nodes_;
	const std::vector<char>& nodes_;
	std::vector<int> in_degree_;
	std::vector<std::vector<char>> adj_list_;
};

Possibilities::Possibilities(const std::size_t num_nodes) :num_nodes_(num_nodes)
{
	data_.resize(num_nodes_);
}

void Possibilities::AddPossibility(const std::vector<char>& nodes)
{
	const auto len = nodes.size();
	for (auto i = i_data_; i < i_data_ + len; ++i)
	{
		data_[i] = nodes;
	}
	i_data_ += len;
}

std::vector<std::vector<char>> Possibilities::GetAll() const
{
	std::vector<std::vector<char>> possibilities;
	return possibilities;
}

TopologicalSort::TopologicalSort(
	const std::vector<char>& nodes,
	const std::vector<std::pair<char, char>>& edge_list)
	: num_nodes_(nodes.size()), nodes_(nodes)
{
	adj_list_.resize('z' + 1);
	in_degree_.resize('z' + 1);


	for (const auto& edge : edge_list)
	{
		adj_list_[edge.first].emplace_back(edge.second);
		++in_degree_[edge.second];
	}
}

std::vector<std::vector<char>> TopologicalSort::GetAllOrderings()
{
	Possibilities possibilities(num_nodes_);
	std::queue<char> order;
	const auto add_order = [&order](const std::vector<char> & nodes)->void
	{
		for (const auto node : nodes)
		{
			order.push(node);
		}
	};

	std::vector<char> independent_nodes;
	for (auto i = 0; i < static_cast<int>(num_nodes_); ++i)
	{
		if (in_degree_[nodes_[i]] == 0)
		{
			independent_nodes.emplace_back(nodes_[i]);
		}
	}
	possibilities.AddPossibility(independent_nodes);
	add_order(independent_nodes);

	while (!order.empty())
	{
		const auto node = order.front();
		order.pop();

		independent_nodes.clear();
		for (const auto adj_node : adj_list_[node])
		{
			--in_degree_[adj_node];
			if (in_degree_[adj_node] == 0)
			{
				independent_nodes.emplace_back(adj_node);
			}
		}
		possibilities.AddPossibility(independent_nodes);
		add_order(independent_nodes);
	}
	return possibilities.GetAll();
}

int main(int argc, char* argv[])
{
	std::vector<char> nodes{ 'v', 'w', 'x', 'y', 'z' };
	std::vector<std::pair<char, char>> edge_list{
		{'v', 'y'},
	{'x', 'v'},
	{'z', 'v'},
	{'w', 'v'}
	};

	TopologicalSort sorter(nodes, edge_list);
	sorter.GetAllOrderings();
	return 0;
}
