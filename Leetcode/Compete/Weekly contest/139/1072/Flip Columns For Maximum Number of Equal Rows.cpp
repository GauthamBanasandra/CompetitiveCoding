// WA

#include <vector>
#include <numeric>
#include <cassert>

using Matrix = std::vector<std::vector<int>>;

class Equalizer
{
public:
	explicit Equalizer(Matrix& matrix) :num_rows_(matrix.size()),
		num_columns_(matrix.front().size()), matrix_(matrix) {}

	int Equalize() const;
private:
	std::vector<std::pair<int, int>> GetRowStatus() const;
	int CountEqualRows() const;

	const std::size_t num_rows_;
	const std::size_t num_columns_;
	Matrix& matrix_;
};

int Equalizer::Equalize() const
{
	auto row_status = GetRowStatus();
	for (std::size_t i = 0; i < num_columns_; ++i)
	{
		auto flip = 0;
		auto do_not_flip = 0;
		for (std::size_t j = 0; j < num_rows_; ++j)
		{
			if (matrix_[j][i] == 0 && row_status[j].first >= row_status[j].second ||
				matrix_[j][i] == 1 && row_status[j].first < row_status[j].second)
			{
				++do_not_flip;
			}
			else if (matrix_[j][i] == 0 && row_status[j].first < row_status[j].second ||
				matrix_[j][i] == 1 && row_status[j].first >= row_status[j].second)
			{
				++flip;
			}
			else
			{
				assert(false);
			}
		}

		if (flip > do_not_flip)
		{
			for (std::size_t j = 0; j < num_rows_; ++j)
			{
				if (matrix_[j][i] == 0)
				{
					matrix_[j][i] = 1;
					--row_status[j].first;
					++row_status[j].second;
				}
				else
				{
					matrix_[j][i] = 0;
					++row_status[j].first;
					--row_status[j].second;
				}
			}
		}
	}
	return CountEqualRows();
}

std::vector<std::pair<int, int>> Equalizer::GetRowStatus() const
{
	std::vector<std::pair<int, int>> status(num_rows_);
	for (std::size_t i = 0; i < num_rows_; ++i)
	{
		for (std::size_t j = 0; j < num_columns_; ++j)
		{
			if (matrix_[i][j] == 0)
			{
				++status[i].first;
			}
			else
			{
				++status[i].second;
			}
		}
	}
	return status;
}

int Equalizer::CountEqualRows() const
{
	auto num_equal_rows = 0;
	for (const auto& row : matrix_)
	{
		const std::size_t sum = std::accumulate(row.begin(),
			row.end(), 0);
		if (sum == 0 || sum == num_columns_)
		{
			++num_equal_rows;
		}
	}
	return num_equal_rows;
}

class Solution
{
public:
	static int maxEqualRowsAfterFlips(
		std::vector<std::vector<int>>& matrix);
};

int Solution::maxEqualRowsAfterFlips(
	std::vector<std::vector<int>>& matrix)
{
	return Equalizer(matrix).Equalize();
}

int main(int argc, char* argv[])
{
	return 0;
}
