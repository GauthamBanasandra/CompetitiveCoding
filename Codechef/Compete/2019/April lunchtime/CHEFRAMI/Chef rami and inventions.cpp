// WA

#include <queue>
#include <iostream>

std::pair<long, int> FindIndex(int i, std::priority_queue<std::pair<long, int>,
	std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>>& numbers)
{
	std::priority_queue<std::pair<long, int>,
		std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> temp;

	std::pair<long, int> p{ -1, -1 };

	while (!numbers.empty())
	{
		const auto top = numbers.top();
		numbers.pop();

		if (top.second == i)
		{
			p = top;
			break;
		}
	}

	while (!temp.empty())
	{
		const auto top = temp.top();
		temp.pop();
		numbers.push(top);
	}
	return p;
}

long GetMinCost(std::priority_queue<std::pair<long, int>,
	std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>>& numbers, long x, int n)
{
	auto max_cost = n * x;

	while (!numbers.empty())
	{
		const auto min = numbers.top();
		numbers.pop();

		if (min.first >= x)
		{
			continue;
		}

		auto right_neighbor = FindIndex(min.second + 1, numbers);
		auto left_neighbor = FindIndex(min.second - 1, numbers);
		if (right_neighbor.second != -1 && left_neighbor.second != -1)
		{
			max_cost -= x;
			max_cost += min.first;
			if (min.first + left_neighbor.first < min.first + right_neighbor.first)
			{
				left_neighbor.first += min.first;
			}
			else
			{
				right_neighbor.first += min.first;
			}
			numbers.emplace(left_neighbor);
			numbers.emplace(right_neighbor);
		}
		else if (left_neighbor.second == -1 && right_neighbor.second != -1)
		{
			max_cost -= x;
			max_cost += min.first;
			right_neighbor.first += min.first;
			numbers.emplace(right_neighbor);
		}
		else if (left_neighbor.second != -1 && right_neighbor.second == -1)
		{
			max_cost -= x;
			max_cost += min.first;
			left_neighbor.first += min.first;
			numbers.emplace(left_neighbor);
		}
	}
	return max_cost;
}

int main(int argc, char* argv[])
{
	int t;
	int n;
	long x;
	long value;


	std::cin >> t;
	while (t--)
	{
		std::priority_queue<std::pair<long, int>,
			std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> numbers;
		std::cin >> n >> x;
		for (auto i = 1; i <= n; ++i)
		{
			std::cin >> value;
			numbers.emplace(value, i);
		}

		std::cout << GetMinCost(numbers, x, n);
	}
	return 0;
}
