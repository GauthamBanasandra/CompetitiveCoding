#include <vector>
#include <string>
#include <iostream>
#include <ios>

namespace uva352
{
	class FloodFill
	{
	public:
		FloodFill(int num_rows, int num_columns, std::vector<std::string>& graph);

		int CountComponents() const;

	private:
		int Fill(int row, int column, char expected_colour, char fill_colour) const;
		bool IsOutside(const int row, const int column) const
		{
			return row < 0 || row >= num_rows_ || column < 0 || column >= num_columns_;
		}

		const int num_rows_;
		const int num_columns_;
		std::vector<std::string>& graph_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> FloodFill::directions_;

	FloodFill::FloodFill(const int num_rows, const int num_columns,
		std::vector<std::string>& graph) :num_rows_(num_rows),
		num_columns_(num_columns), graph_(graph)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, -1} , {-1, 0}, {-1, 1}, {0, -1},
				{0, 1}, {1, -1}, {1, 0}, {1, 1} };
		}
	}

	int FloodFill::CountComponents() const
	{
		auto count = 0;
		for (auto i = 0; i < num_rows_; ++i)
		{
			for (auto j = 0; j < num_columns_; ++j)
			{
				count += Fill(i, j, '1', 'x');
			}
		}
		return count;
	}

	int FloodFill::Fill(const int row, const int column,
		const char expected_colour, const char fill_colour) const
	{
		if (IsOutside(row, column) || graph_[row][column] != expected_colour)
		{
			return 0;
		}

		graph_[row][column] = fill_colour;
		for (const auto& direction : directions_)
		{
			Fill(row + direction.first, column + direction.second,
				expected_colour, fill_colour);
		}
		return 1;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n;
	auto t = 0;
	std::vector<std::string> graph;

	while (std::cin >> n, !std::cin.eof())
	{
		graph.resize(n);
		for (auto i = 0; i < n; ++i)
		{
			std::cin >> graph[i];
		}

		uva352::FloodFill filler(n, n, graph);
		std::cout << "Image number " << ++t << " contains " <<
			filler.CountComponents() << " war eagles." << std::endl;
	}
	return 0;
}
