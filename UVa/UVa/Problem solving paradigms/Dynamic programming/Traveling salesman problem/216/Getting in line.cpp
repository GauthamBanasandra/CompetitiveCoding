#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <iomanip>

using Pos = std::pair<int, int>;
using MemoVisit = std::pair<std::size_t, int>;
using Matrix = std::vector<std::vector<double>>;

void Print(const Matrix &matrix);
const auto infinity = std::numeric_limits<double>::max();

class Graph
{
public:
	Graph(const std::vector<Pos> &pos);
	void ConnectAndPrint();

private:
	double Connect(std::size_t i_pos, int visited);
	void Reconstruct();

	Matrix distance_;
	const std::vector<Pos> &pos_;
	std::vector<std::vector<double>> memo_;
	std::vector<std::vector<MemoVisit>> memo_visit_;
};

Graph::Graph(const std::vector<Pos>& pos) :pos_(pos)
{
	const auto len = pos_.size();
	memo_.resize(len, std::vector<double>(static_cast<std::size_t>(1 << len), -1));
	memo_visit_.resize(len, std::vector<MemoVisit>(static_cast<std::size_t>(1 << len), { 0, 0 }));

	distance_.resize(len, std::vector<double>(len));
	for (std::size_t i = 0; i < len; ++i)
	{
		const auto&[pi_x, pi_y] = pos_[i];
		for (auto j = i + 1; j < len; ++j)
		{
			const auto&[pj_x, pj_y] = pos_[j];
			distance_[i][j] = distance_[j][i] = std::sqrt(static_cast<double>((pi_x - pj_x)*(pi_x - pj_x) + (pi_y - pj_y)*(pi_y - pj_y)));
		}
	}
}

void Graph::ConnectAndPrint()
{
	const auto len = distance_.size();
	const auto min_distance = Connect(0, 1) + 16 * (len - 1);
	Reconstruct();
	std::cout << "Number of feet of cable required is " << min_distance << "." << std::endl;
}

double Graph::Connect(const std::size_t i_pos, const int visited)
{
	const auto len = static_cast<int>(distance_.size());
	if (visited == (1 << len) - 1)
	{
		return 0;
	}

	auto& memo = memo_[i_pos][visited];
	if (memo != -1)
	{
		return memo;
	}

	auto min_distance = infinity;
	std::size_t min_index = 0;
	for (std::size_t i = 0; i < static_cast<std::size_t>(len); ++i)
	{
		if (i == i_pos || visited & 1 << static_cast<int>(i))
		{
			continue;
		}

		if (const auto distance = distance_[i_pos][i] + Connect(i, visited | 1 << i); distance < min_distance)
		{
			min_distance = distance;
			min_index = i;
		}
	}
	memo_visit_[i_pos][visited] = { min_index, visited | 1 << min_index };
	return memo = min_distance;
}

void Graph::Reconstruct()
{
	const auto len = distance_.size();
	std::size_t index = 0;
	auto visited = 1;
	while (visited != (1 << len) - 1)
	{
		const auto&[x1, y1] = pos_[index];
		const auto& next = memo_visit_[index][visited];
		const auto&[x2, y2] = pos_[next.first];

		std::cout << "Cable requirement to connect ";
		std::cout << "(" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ") is ";
		std::cout << distance_[index][next.first] + 16 << " feet." << std::endl;
		index = next.first;
		visited = next.second;
	}
}

int main(int argc, char* argv[])
{
	std::size_t t = 0;
	std::size_t num_pos;
	std::vector<Pos> pos{
		/*{5 ,19},
		{55 ,28},
		{38 ,101},
		{28 ,62},
		{111 ,84},
		{43 ,116},*/

		{11, 27},
		{84, 99},
		{142, 81},
		{88, 30},
		{95, 38}
	};
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	while (std::cin >> num_pos, num_pos)
	{
		pos.resize(num_pos);
		for (std::size_t i = 0; i < num_pos; ++i)
		{
			std::cin >> pos[i].first >> pos[i].second;
		}

		Graph graph(pos);
		std::cout << "**********************************************************" << std::endl;
		std::cout << "Network #" << ++t << std::endl;
		graph.ConnectAndPrint();
	}	
	return 0;
}
