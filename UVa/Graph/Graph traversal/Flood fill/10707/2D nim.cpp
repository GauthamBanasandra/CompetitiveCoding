// WA

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

struct Pos
{
	Pos() = default;
	Pos(const int x, const int y) :x(x), y(y) {}

	std::string GetHash() const
	{
		return std::to_string(x) + " " + std::to_string(y);
	}

	int x{ 0 };
	int y{ 0 };
};

class Filler
{
public:
	Filler(const std::vector<Pos>& pieces, int num_rows, int num_columns);

	void GetCluster(Pos pos, std::unordered_set<int>& cluster_out);

private:
	bool IsOutside(const Pos& pos) const
	{
		return pos.x < 0 || pos.x >= num_rows_ || pos.y < 0 || pos.y >= num_columns_;
	}

	const int num_rows_;
	const int num_columns_;
	const std::vector<Pos>& pieces_;
	std::unordered_map<std::string, int> piece_index_;
	std::unordered_set<std::string> visited_;
	static std::vector<std::pair<int, int>> directions_;
};

std::vector<std::pair<int, int>> Filler::directions_;

Filler::Filler(const std::vector<Pos>& pieces, const int num_rows,
	const int num_columns) :num_rows_(num_rows), num_columns_(num_columns), pieces_(pieces)
{
	for (auto i = 0, len = static_cast<int>(pieces_.size()); i < len; ++i)
	{
		piece_index_[pieces_[i].GetHash()] = i;
	}

	if (directions_.empty())
	{
		directions_ = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	}
}

void Filler::GetCluster(Pos pos, std::unordered_set<int>& cluster_out)
{
	if (IsOutside(pos) ||
		visited_.find(pos.GetHash()) != visited_.end() ||
		piece_index_.find(pos.GetHash()) == piece_index_.end())
	{
		return;
	}

	visited_.insert(pos.GetHash());
	cluster_out.insert(piece_index_[pos.GetHash()]);
	for (const auto& direction : directions_)
	{
		GetCluster({ pos.x + direction.first, pos.y + direction.second }, cluster_out);
	}
}

class Validator
{
public:
	static bool ValidateBoards(const std::vector<Pos>& board1,
		const std::vector<Pos>& board2, const std::pair<int, int>& dimensions);

private:
	static bool ValidateClusters(const std::unordered_set<int>& cluster1,
		const std::unordered_set<int>& cluster2);
};

bool Validator::ValidateBoards(const std::vector<Pos> & board1,
	const std::vector<Pos> & board2, const std::pair<int, int> & dimensions)
{
	Filler filler1(board1, dimensions.first, dimensions.second);
	Filler filler2(board2, dimensions.first, dimensions.second);


	for (std::size_t i = 0, len = board1.size(); i < len; ++i)
	{
		std::unordered_set<int> cluster_board1;
		filler1.GetCluster(board1[i], cluster_board1);
		std::unordered_set<int> cluster_board2;
		filler2.GetCluster(board2[i], cluster_board2);

		if (!ValidateClusters(cluster_board1, cluster_board2))
		{
			return false;
		}
	}
	return true;
}

bool Validator::ValidateClusters(
	const std::unordered_set<int> & cluster1,
	const std::unordered_set<int> & cluster2)
{
	if (cluster1.size() != cluster2.size())
	{
		return false;
	}

	for (const auto piece : cluster1)
	{
		if (cluster2.find(piece) == cluster2.end())
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	std::pair<int, int> dimensions{ 8, 5 };
	std::vector<Pos> board1{
{0, 0},
{1, 0},
{2, 0},
{5, 0},
{7, 0},
{1, 1},
{2, 1},
{5, 1},
{3, 3},
{5, 2},
{4, 4},
	};

	std::vector<Pos> board2{
{0, 4},
{0, 3},
{0, 2},
{1, 1},
{1, 4},
{1, 3},
{3, 3},
{5, 2},
{6, 2},
{7, 2},
{7, 4},
	};

	Validator validator;
	std::cout <<
		(validator.ValidateBoards(board1, board2, dimensions) ? "YES" : "NO") << std::endl;
	return 0;
}
