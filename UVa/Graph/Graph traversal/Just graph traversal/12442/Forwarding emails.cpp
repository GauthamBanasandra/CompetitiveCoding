#include <vector>
#include <iostream>

class Traversal
{
public:
	explicit Traversal(int num_nodes);

	int GetMaxForwardIndex();

private:
	int DFS(int u);

	const int num_nodes_;
	std::vector<int> adj_list_;
	std::vector<short> visited_;
	std::vector<int> visit_cache_;
};

Traversal::Traversal(const int num_nodes) :num_nodes_(num_nodes)
{
	visited_.resize(num_nodes_ + 1);
	adj_list_.resize(num_nodes_ + 1);
	visit_cache_.resize(num_nodes_ + 1, -1);

	int node;
	int adj_node;
	for (auto i = 0l; i < num_nodes_; ++i)
	{
		std::cin >> node >> adj_node;
		adj_list_[node] = adj_node;
	}
}

int Traversal::GetMaxForwardIndex()
{
	auto max_visit = 0;
	auto i_max = 0;
	for (auto i = 1; i <= num_nodes_; ++i)
	{
		if (visit_cache_[i] == -1)
		{
			DFS(i);
		}
		if (visit_cache_[i] > max_visit)
		{
			max_visit = visit_cache_[i];
			i_max = i;
		}
	}
	return i_max;
}

int Traversal::DFS(const int u)
{
	const auto v = adj_list_[u];
	auto num_visited_nodes = 0;

	visited_[u] = 1;
	if (visited_[v] == 0)
	{
		num_visited_nodes = DFS(v) + 1;
	}
	visited_[u] = 0;
	visit_cache_[u] = num_visited_nodes;
	return num_visited_nodes;
}

int main(int argc, char* argv[])
{
	int t;
	int num_nodes;

	std::cin >> t;
	for (auto i = 1; i <= t; ++i)
	{
		std::cin >> num_nodes;
		Traversal traversal(num_nodes);
		std::cout << "Case " << i << ": " << traversal.GetMaxForwardIndex() << std::endl;
	}
	return 0;
}
