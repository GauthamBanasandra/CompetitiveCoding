#include <vector>

std::vector<std::vector<int>> GeneratePascalsTriangle(const int num_rows)
{
	std::vector<std::vector<int>> triangle(num_rows);

	for (auto i = 0; i < num_rows; ++i)
	{
		auto& row = triangle[i];
		row.resize(i + 1);

		row.front() = row.back() = 1;
		for (auto j = 1; j < i; ++j)
		{
			row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
		}
	}
	return triangle;
}

class Solution
{
public:
	static std::vector<std::vector<int>> generate(
		int numRows);
};

std::vector<std::vector<int>> Solution::generate(
	int numRows)
{
	return GeneratePascalsTriangle(numRows);
}

int main(int argc, char* argv[])
{
	return 0;
}
