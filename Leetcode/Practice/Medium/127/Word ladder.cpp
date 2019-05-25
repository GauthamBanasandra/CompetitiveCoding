#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <iostream>

const auto unvisited = -1;

class Graph
{
public:
	Graph(const std::string& start_word, const std::string& end_word,
		const std::vector<std::string>& words) :num_nodes_(static_cast<int>(words.size())),
		start_word_(start_word), end_word_(end_word), words_(words) {}

	int GetShortestTransformationLen();

private:
	void ConstructAdjList();
	static bool IsDistance1(const std::string& a, const std::string& b);
	int BFS() const;

	const int num_nodes_;
	std::size_t i_end_word_{ 0 };
	const std::string& start_word_;
	const std::string& end_word_;
	std::vector<std::vector<int>> adj_list_;
	const std::vector<std::string>& words_;
};

int Graph::GetShortestTransformationLen()
{
	const auto find_it = std::find(words_.begin(), words_.end(), end_word_);
	if (find_it == words_.end())
	{
		return 0;
	}
	i_end_word_ = std::distance(words_.begin(), find_it);

	ConstructAdjList();
	const auto distance = BFS();
	return distance == unvisited ? 0 : distance + 1;
}

void Graph::ConstructAdjList()
{
	adj_list_.resize(num_nodes_);
	for (auto i = 0; i < num_nodes_; ++i)
	{
		for (auto j = i + 1; j < num_nodes_; ++j)
		{
			if (IsDistance1(words_[i], words_[j]))
			{
				adj_list_[i].emplace_back(j);
				adj_list_[j].emplace_back(i);
			}
		}
	}
}

bool Graph::IsDistance1(const std::string& a, const std::string& b)
{
	auto tolerate = true;
	for (auto i = 0, len = static_cast<int>(a.size()); i < len; ++i)
	{
		if (a[i] == b[i])
		{
			continue;
		}

		if (tolerate)
		{
			tolerate = false;
			continue;
		}
		return false;
	}
	return true;
}

int Graph::BFS() const
{
	std::vector<int> visited(num_nodes_, unvisited);
	std::queue<int> order;
	order.push(0);
	visited[0] = 0;

	while (!order.empty())
	{
		const auto node = order.front();
		order.pop();

		for (const auto adj_node : adj_list_[node])
		{
			if (visited[adj_node] == unvisited)
			{
				visited[adj_node] = visited[node] + 1;
				order.push(adj_node);
			}
			else
			{
				visited[adj_node] = std::min(visited[adj_node], visited[node] + 1);
			}
		}
	}
	return visited[i_end_word_];
}

class Solution
{
public:
	static int ladderLength(std::string beginWord,
		std::string endWord,
		std::vector<std::string>&
		wordList);
};

int Solution::ladderLength(std::string beginWord,
	std::string endWord,
	std::vector<std::string>&
	wordList)
{
	std::vector<std::string> words{ beginWord };
	words.resize(wordList.size() + 1);
	std::copy(wordList.begin(), wordList.end(), words.begin() + 1);
	return Graph(beginWord, endWord, words).GetShortestTransformationLen();
}

int main(int argc, char* argv[])
{
	std::vector<std::string> words{ "hot","dot","dog","lot","log","cog", "hat" };
	std::cout << Solution::ladderLength("hit", "hat", words) << std::endl;
	return 0;
}
