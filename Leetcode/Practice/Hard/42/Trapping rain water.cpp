#include <vector>

int GetTrappedWaterQty(std::vector<int>& heights)
{
	if (heights.empty())
	{
		return 0;
	}

	auto total_water = 0;
	auto water = 0;
	auto i_wall = 0;
	auto wall_height = 0;
	const auto len = static_cast<int>(heights.size());

	// Proceed from left to right
	for (auto i = 0; i < len; ++i)
	{
		// As long as there's a pit, collect the water
		if (wall_height > heights[i])
		{
			water += wall_height - heights[i];
		}
		else
		{
			// If we hit a wall whose height is greater than wall_height,
			// then this water can definitely be collected, store in total_water
			total_water += water;
			water = 0;
			i_wall = i;
			wall_height = heights[i];
		}
	}

	water = 0;
	wall_height = 0;
	// Proceed from right to left
	// We need to do this because we may not have hit a wall taller than wall_height
	// In that case, we wouldn't have collected water in total_water
	// So we just run the same algorithm above, but in the reverse order of the heights
	// till we hit the last tallest wall (i_wall)
	for (auto i = len - 1; i >= i_wall; --i)
	{
		if (wall_height > heights[i])
		{
			water += wall_height - heights[i];
		}
		else
		{
			total_water += water;
			water = 0;
			wall_height = heights[i];
		}
	}
	return total_water;
}

class Solution {
public:
	static int trap(std::vector<int>& height);
};

int Solution::trap(std::vector<int>& height)
{
	return GetTrappedWaterQty(height);
}

int main(int argc, char* argv[])
{
	return 0;
}
