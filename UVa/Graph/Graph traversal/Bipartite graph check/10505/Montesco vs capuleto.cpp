// WIP

#include <vector>
#include <queue>
#include <iostream>

class BipartiteCheck
{
public:
	BipartiteCheck(const int num_nodes, const std::vector<std::vector<int>>& adj_list)
		:num_nodes_(num_nodes + 1), adj_list_(adj_list) {}

	int CountFriends() const;

private:


	const int num_nodes_;
	const std::vector<std::vector<int>>& adj_list_;
};

int main(int argc, char* argv[])
{
	return 0;
}
