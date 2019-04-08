#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>

namespace uva469
{
	class FloodFill
	{
	public:
		explicit FloodFill(std::vector<std::string>& graph);

		int GetArea(const int row, const int column)
		{
			return Fill(row - 1, column - 1, 'W', '*');
		}

	private:
		int Fill(int row, int column, char expected_colour, char fill_colour);
		bool IsOutside(const int row, const int column) const
		{
			return row < 0 || row >= num_rows_ || column < 0 || column >= num_columns_;
		}

		const int num_rows_;
		const int num_columns_;
		std::vector<std::string> graph_;
		std::unordered_map<std::string, int> cache_;
		static std::vector<std::pair<int, int>> directions_;
	};

	std::vector<std::pair<int, int>> FloodFill::directions_;

	FloodFill::FloodFill(std::vector<std::string>& graph)
		:num_rows_(static_cast<int>(graph.size())), num_columns_(
			static_cast<int>(graph.front().size())), graph_(graph)
	{
		if (directions_.empty())
		{
			directions_ = { {-1, -1} , {-1, 0}, {-1, 1}, {0, -1},
				{0, 1}, {1, -1}, {1, 0}, {1, 1} };
		}
	}

	int FloodFill::Fill(const int row, const int column,
		const char expected_colour, const char fill_colour)
	{
		if (IsOutside(row, column) || graph_[row][column] != expected_colour)
		{
			return 0;
		}

		graph_[row][column] = fill_colour;
		auto count = 1;
		for (const auto& direction : directions_)
		{
			count += Fill(row + direction.first, column + direction.second,
				expected_colour, fill_colour);
		}
		return count;
	}
}

int main(int argc, char* argv[])
{
	int t;
	int row;
	int column;
	auto prefix = "";
	std::string line;

	std::cin >> t;
	std::getline(std::cin, line);
	std::getline(std::cin, line);
	while (t--)
	{
		std::vector<std::string> graph;
		while (std::getline(std::cin, line), line.front() == 'L' || line.front() == 'W')
		{
			graph.emplace_back(line);
		}

		std::cout << prefix;
		do
		{
			uva469::FloodFill filler(graph);

			std::istringstream tokenizer(line);
			tokenizer >> row >> column;
			std::cout << filler.GetArea(row, column) << std::endl;
		} while (std::getline(std::cin, line), !line.empty());
		prefix = "\n";
	}
	return 0;
}
