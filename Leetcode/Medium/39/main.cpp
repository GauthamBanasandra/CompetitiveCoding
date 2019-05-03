#include <vector>

class Solution {
public:
	std::vector<std::vector<int>> combinationSum(
		std::vector<int>& candidates, int target);
};

int main(int argc, char* argv[])
{
	std::vector<int> candidates{ 2, 3, 6, 7 };
	Solution().combinationSum(candidates, 5);
	return 0;
}
