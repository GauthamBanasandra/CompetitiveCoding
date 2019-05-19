// WA

#include <vector>
#include <queue>
#include <cmath>
#include <iostream>

int GetLastStoneWeight(const std::vector<int>& weights)
{
	std::priority_queue<int> order(weights.begin(), weights.end());

	while (order.size() > 1)
	{
		const auto heaviest = order.top();
		order.pop();
		const auto second_heaviest = order.top();
		order.pop();

		const auto mashed_weight = std::abs(heaviest - second_heaviest);
		if (mashed_weight != 0)
		{
			order.push(mashed_weight);
		}
	}
	return order.empty() ? 0 : order.top();
}

class Solution
{
public:
	static int lastStoneWeightII(std::vector<int>& stones);
};

int Solution::lastStoneWeightII(std::vector<int>& stones)
{
	return GetLastStoneWeight(stones);
}

int main(int argc, char* argv[])
{
	std::vector<int> stones{ 2,7,4,1,8,1 };
	std::cout << Solution::lastStoneWeightII(stones) << std::endl;
	return 0;
}
