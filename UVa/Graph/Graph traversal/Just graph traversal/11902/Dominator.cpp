#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <ios>

namespace uva11902
{
	class AdjList
	{
	public:
		explicit AdjList(int num_nodes);

		const std::vector<int>& operator[](const int i)const { return graph_[i]; }

		const int num_nodes;

	private:
		void Read();

		std::vector<std::vector<int>> graph_;
	};

	AdjList::AdjList(const int num_nodes) :num_nodes(num_nodes)
	{
		graph_.resize(num_nodes);
		Read();
	}

	void AdjList::Read()
	{
		short value = 0;
		for (auto i = 0; i < num_nodes; ++i)
		{
			graph_[i].reserve(num_nodes);
			for (auto j = 0; j < num_nodes; ++j)
			{
				std::cin >> value;
				if (value == 0)
				{
					continue;
				}
				graph_[i].emplace_back(j);
			}
		}
	}

	class BFS
	{
	public:
		BFS(const AdjList &adj_list) :adj_list_(adj_list) {}

		std::string FindDominators() const;

	private:
		std::string ToString(const std::vector<std::string> &visited) const;
		std::string NodesReachableFromOrigin() const;
		void Visit(int i_dominator, std::string &visited) const;
		void MarkDominators(const std::string& reachable, std::string &visited) const;

		const AdjList &adj_list_;
	};

	std::string BFS::FindDominators() const
	{
		// This constitutes the list of nodes that are reachable from origin
		// This is obtained prior to marking any node as dominator
		// Essentially, these are the nodes that we're interested in
		// As per the problem statement, the nodes that don't belong to the
		// component that are reachable from origin(0) don't have a dominator
		const auto reachable = NodesReachableFromOrigin();

		std::vector<std::string> visited(adj_list_.num_nodes,
			std::string(adj_list_.num_nodes, 'N'));

		for (auto i = 0; i < adj_list_.num_nodes; ++i)
		{
			Visit(i, visited[i]);
			MarkDominators(reachable, visited[i]);
		}
		return ToString(visited);
	}

	std::string BFS::ToString(const std::vector<std::string>& visited) const
	{
		std::ostringstream out;
		std::string separator(2 * adj_list_.num_nodes - 1, '-');
		separator = "+" + separator + "+";
		out << separator << std::endl;

		for (const auto& row : visited)
		{
			for (const auto c : row)
			{
				out << '|' << c;
			}
			out << '|' << std::endl;
			out << separator << std::endl;
		}
		return out.str();
	}

	std::string BFS::NodesReachableFromOrigin() const
	{
		std::string visited(adj_list_.num_nodes, 'N');
		std::queue<int> nodes;

		visited[0] = 'Y';
		nodes.push(0);

		while (!nodes.empty())
		{
			const auto node = nodes.front();
			nodes.pop();

			for (const auto adj_node : adj_list_[node])
			{
				if (visited[adj_node] == 'Y')
				{
					continue;
				}

				visited[adj_node] = 'Y';
				nodes.push(adj_node);
			}
		}
		return visited;
	}

	void BFS::Visit(const int i_dominator, std::string& visited) const
	{
		std::queue<int> nodes;
		nodes.push(0);

		while (!nodes.empty())
		{
			const auto node = nodes.front();
			nodes.pop();
			if (i_dominator == node)
			{
				continue;
			}
			visited[node] = 'Y';

			for (const auto adj_node : adj_list_[node])
			{
				if (i_dominator == adj_node || visited[adj_node] == 'Y')
				{
					continue;
				}

				visited[adj_node] = 'Y';
				nodes.push(adj_node);
			}
		}
	}

	void BFS::MarkDominators(const std::string& reachable, std::string& visited) const
	{
		for (auto i = 0; i < adj_list_.num_nodes; ++i)
		{			
			if (reachable[i] == 'N')
			{
				visited[i] = 'N';
				continue;
			}

			visited[i] = visited[i] == 'Y' ? 'N' : 'Y';
		}
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n;
	int t;
	std::cin >> t;

	for (auto i = 1; i <= t; ++i)
	{
		std::cout << "Case " << i << ':' << std::endl;
		std::cin >> n;
		uva11902::AdjList adj_list(n);
		uva11902::BFS bfs(adj_list);
		std::cout << bfs.FindDominators();
	}
	return 0;
}
