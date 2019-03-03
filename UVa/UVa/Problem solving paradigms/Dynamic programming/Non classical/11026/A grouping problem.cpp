// WIP

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <cassert>

using ll = long long;

void Print(const std::vector<int> &elements);

struct Cell
{
	Cell() = default;
	Cell(const ll product, const std::size_t index, const std::size_t i_primordial) :product(product), index(index), i_primordial(i_primordial) {}

	bool operator==(const Cell& other) const { return product == other.product; }
	bool operator<(const Cell& other) const { return index < other.index; }
	ll operator()(const Cell& cell) const { return cell.product; }

	ll product{ 0 };
	std::size_t index{ 0 };
	std::size_t i_primordial{ 0 };
};

class Group
{
public:
	Group(const std::vector<int> &numbers, std::size_t k, ll m);

	ll Score();

private:
	void Insert(std::size_t i, const Cell& cell);

	const ll m_;
	std::vector<std::unordered_set<Cell, Cell>> memo_;
	const std::vector<int> &numbers_;
};

Group::Group(const std::vector<int>& numbers, const std::size_t k, const ll m) :m_(m), numbers_(numbers)
{
	memo_.resize(k);
}

ll Group::Score()
{
	const auto numbers_len = numbers_.size();
	for (std::size_t i = 0; i < numbers_len; ++i)
	{
		Insert(0, { numbers_[i], i, i });
	}

	for (std::size_t i = 1, len = memo_.size(); i < len; ++i)
	{
		auto &row = memo_[i - 1];
		for (const auto& cell : row)
		{
			for (auto j = cell.index + 1; j < numbers_len; ++j)
			{
				const auto product = ((cell.product)* (numbers_[j]));
				Insert(i, { product, j, cell.i_primordial });
			}
		}
	}

	ll fitness_score = 0;
	for (const auto& cell : memo_.back())
	{
		fitness_score = (fitness_score + cell.product) % m_;
	}
	return fitness_score;
}

void Group::Insert(const std::size_t i, const Cell& cell)
{
	auto& row = memo_[i];
	const auto find_it = row.find(cell);
	if (find_it == row.end())
	{
		row.insert(cell);
		return;
	}

	if (cell < *find_it)
	{
		row.erase(find_it);
		row.insert(cell);
	}
}

ll AggregateScore(const std::vector<int> &numbers, const ll m)
{
	ll max_score = 0;
	for (std::size_t k = 1, len = numbers.size(); k <= len; ++k)
	{
		Group group(numbers, k, m);
		const auto score = group.Score();
		max_score = std::max(max_score, score);
	}
	return max_score;
}

int main(int argc, char* argv[])
{
	std::size_t n;
	int m;
	std::vector<int> numbers{ 1, 2, 3, 4 };

	while (std::cin >> n >> m, n || m)
	{
		numbers.resize(n);
		for (std::size_t i = 0; i < n; ++i)
		{
			std::cin >> numbers[i];
		}
		std::cout << AggregateScore(numbers, m) << std::endl;
	}
	return 0;
}
