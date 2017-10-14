#include <stdio.h>
#include <vector>
#include <bitset>

#define ROW_SIZE 3
#define COL_SIZE 3

using big_int = unsigned long long;

class Grid
{
public:
	Grid();
	void Read();
	void PrintGrid() const;
	int TransformF(Grid& h);
	int GetSum() const { return g_[0].to_ulong() + g_[1].to_ulong() + g_[2].to_ulong(); }
	void Reset() { g_.clear(); }
	~Grid();

private:
	std::vector<std::bitset<ROW_SIZE>> g_;
};

Grid::Grid()
{
}

void Grid::Read()
{
	char line[ROW_SIZE + 5];
	for (auto i = 0; i < COL_SIZE; i++)
	{
		scanf("%s", line);
		g_.push_back(std::bitset<ROW_SIZE>(line));
	}
}

void Grid::PrintGrid() const
{
	for (auto row : g_)
	{
		printf("%s\n", row.to_string().c_str());
	}
}

inline int Grid::TransformF(Grid& h)
{
	auto sum = 0;
	std::bitset<ROW_SIZE> row;

	row[0] = g_[0][1] + g_[1][0] & 1;
	row[1] = g_[0][0] + g_[0][2] + g_[1][1] & 1;
	row[2] = g_[0][1] + g_[1][2] & 1;
	h.g_.push_back(row);
	sum += row.to_ulong();

	row[0] = g_[0][0] + g_[2][0] + g_[1][1] & 1;
	row[1] = g_[0][1] + g_[1][2] + g_[2][1] + g_[1][0] & 1;
	row[2] = g_[0][2] + g_[1][1] + g_[2][2] & 1;
	h.g_.push_back(row);
	sum += row.to_ulong();

	row[0] = g_[1][0] + g_[2][1] & 1;
	row[1] = g_[2][0] + g_[1][1] + g_[2][2] & 1;
	row[2] = g_[1][2] + g_[2][1] & 1;
	h.g_.push_back(row);
	sum += row.to_ulong();

	return sum;
}

Grid::~Grid()
{
}
int main()
{
	big_int n;
	long i = 0;
	scanf("%llu\n\n", &n);
	while (n--)
	{
		Grid g, h;
		g.Read();

		i = 0;
		while (g.GetSum())
		{
			/*printf("i = %ld\n", i - 1);
			g.PrintGrid();*/

			++i;
			h.Reset();
			g.TransformF(h);
			g = h;
		}

		printf("%ld\n", i - 1);
	}

	return 0;
}