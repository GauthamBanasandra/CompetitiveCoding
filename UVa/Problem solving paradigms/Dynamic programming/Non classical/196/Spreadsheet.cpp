#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <regex>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <ios>

namespace uva196
{
	struct Cell
	{
		Cell() = default;
		Cell(std::string data) :data(std::move(data)) {}

		std::string data;
		bool is_solved{ false };
		long value{ 0l };
	};

	struct Pos
	{
		Pos(const std::size_t row, const std::size_t col) :row(row), col(col) {}

		std::size_t row{ 0ul };
		std::size_t col{ 0ul };
	};

	using Matrix = std::vector<std::vector<Cell>>;

	class SpreadSheet
	{
	public:
		explicit SpreadSheet(Matrix &sheet);
		void Solve() const;
		void Print() const;

	private:
		long Solve(const Pos &pos) const;
		static std::vector<Pos> GetDependencies(const Cell& cell);

		Matrix &sheet_;
		static std::regex rgx_;
		static std::unordered_map<std::string, std::size_t> col_index_;
	};

	std::unordered_map<std::string, std::size_t> SpreadSheet::col_index_;
	std::regex SpreadSheet::rgx_;

	SpreadSheet::SpreadSheet(Matrix& sheet) : sheet_(sheet)
	{
		if (!col_index_.empty())
		{
			return;
		}

		rgx_ = R"(([A-Z]+)(\d+))";

		std::string col_name(1, ' ');
		std::size_t index = 0ul;
		for (auto i = 'A'; i <= 'Z'; ++i)
		{
			col_name[0] = i;
			col_index_[col_name] = index++;
		}

		col_name.resize(2);
		for (auto i = 'A'; i <= 'Z'; ++i)
		{
			col_name[0] = i;
			for (auto j = 'A'; j <= 'Z'; ++j)
			{
				col_name[1] = j;
				col_index_[col_name] = index++;
			}
		}

		col_name.resize(3);
		for (auto i = 'A'; i <= 'Z'; ++i)
		{
			col_name[0] = i;
			for (auto j = 'A'; j <= 'Z'; ++j)
			{
				col_name[1] = j;
				for (auto k = 'A'; k <= 'Z'; ++k)
				{
					col_name[2] = k;
					col_index_[col_name] = index++;

				}
			}
		}
	}

	void SpreadSheet::Solve() const
	{
		for (std::size_t i = 0, row_len = sheet_.size(); i < row_len; ++i)
		{
			for (std::size_t j = 0, col_len = sheet_[i].size(); j < col_len; ++j)
			{
				auto &cell = sheet_[i][j];
				cell.value = Solve({ i, j });
				cell.is_solved = true;
			}
		}
	}

	void SpreadSheet::Print() const
	{
		for (const auto& row : sheet_)
		{
			std::cout << row.front().value;
			for (std::size_t i = 1ul, col_len = row.size(); i < col_len; ++i)
			{
				std::cout << " " << row[i].value;
			}
			std::cout << std::endl;
		}
	}

	long SpreadSheet::Solve(const Pos& pos) const
	{
		auto &cell = sheet_[pos.row][pos.col];
		if (cell.is_solved)
		{
			return cell.value;
		}

		const auto first_char = cell.data.front();
		if (first_char == '-' || first_char == '+' || isdigit(first_char))
		{
			cell.value = std::stol(cell.data);
			cell.is_solved = true;
			return cell.value;
		}
		assert(first_char == '=');

		const auto &dependencies = GetDependencies(cell);
		for (const auto &dependency : dependencies)
		{
			cell.value += Solve(dependency);
		}
		cell.is_solved = true;
		return cell.value;
	}

	std::vector<Pos> SpreadSheet::GetDependencies(const Cell& cell)
	{
		std::vector<Pos> dependencies;
		if (cell.data.front() != '=')
		{
			return dependencies;
		}

		for (auto it = std::sregex_iterator(cell.data.begin(), cell.data.end(), rgx_),
			end = std::sregex_iterator(); it != end; ++it)
		{
			auto match = *it;
			auto find_it = col_index_.find(match.str(1));
			assert(find_it != col_index_.end());
			dependencies.emplace_back(static_cast<std::size_t>(std::stoi(match.str(2))) - 1, find_it->second);
		}
		return dependencies;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t num_row = 0ul, num_col = 0ul, num_sheets = 0ul;
	uva196::Matrix sheet_input;
	std::string cell;

	std::cin >> num_sheets;
	while (num_sheets-- > 0)
	{
		std::cin >> num_col >> num_row;
		sheet_input.resize(num_row);
		for (std::size_t i = 0ul; i < num_row; ++i)
		{
			sheet_input[i].resize(num_col);
			for (std::size_t j = 0ul; j < num_col; ++j)
			{
				std::cin >> cell;
				sheet_input[i][j] = cell;
			}
		}

		uva196::SpreadSheet sheet(sheet_input);
		sheet.Solve();
		sheet.Print();
	}
	return 0;
}
