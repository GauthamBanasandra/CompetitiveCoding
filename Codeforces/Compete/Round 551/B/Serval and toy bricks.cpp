#include <vector>
#include <algorithm>
#include <iostream>

namespace round_551
{
	using Matrix = std::vector<std::vector<int>>;

	Matrix GetObject(const std::vector<int>& front_view,
		const std::vector<int>& left_view, const Matrix& top_view)
	{
		Matrix object;
		object.resize(left_view.size());

		for (auto& row : object)
		{
			row.assign(front_view.begin(), front_view.end());
		}

		for (auto i = 0, len = static_cast<int>(left_view.size()); i < len; ++i)
		{
			for (auto& block : object[i])
			{
				block = std::min(block, left_view[i]);
			}
		}

		for (auto i = 0, num_row = static_cast<int>(top_view.size()); i < num_row; ++i)
		{
			for (auto j = 0, num_column = static_cast<int>(
				top_view[i].size()); j < num_column; ++j)
			{
				object[i][j] *= top_view[i][j];
			}
		}
		return object;
	}
}

int main(int argc, char* argv[])
{
	int n;
	int m;
	int h;
	std::vector<int> front_view;
	std::vector<int> left_view;
	round_551::Matrix top_view;

	std::cin >> n >> m >> h;
	front_view.resize(m);
	left_view.resize(n);
	top_view.resize(n, std::vector<int>(m));

	for (auto i = 0; i < m; ++i)
	{
		std::cin >> front_view[i];
	}

	for (auto i = 0; i < n; ++i)
	{
		std::cin >> left_view[i];
	}

	for (auto i = 0; i < n; ++i)
	{
		for (auto j = 0; j < m; ++j)
		{
			std::cin >> top_view[i][j];
		}
	}

	const auto object = round_551::GetObject(front_view, left_view, top_view);
	for (const auto& row : object)
	{
		auto separator = "";
		for (const auto& height : row)
		{
			std::cout << separator << height;
			separator = " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
