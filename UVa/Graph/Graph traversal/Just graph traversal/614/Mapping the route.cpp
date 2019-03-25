// WIP

#include <vector>
#include <string>
#include <iostream>

struct Direction
{
	enum
	{
		kWest = 1,
		kNorth = 2,
		kEast = 3,
		kSouth = 4
	};
};

class Simulator
{
public:
	explicit Simulator(const std::vector<std::string> &walls, int max_x, int max_y);

private:
	bool IsOutside(const int x, const int y) const { return x < 0 || x > max_x_ || y < 0 || y >  max_y_; }

	const int max_x_;
	const int max_y_;
	std::vector<std::vector<int>> walls_;
};

Simulator::Simulator(const std::vector<std::string>& walls, const int max_x, const int max_y) :max_x_(max_x), max_y_(max_y)
{
	walls_.resize(max_x_, std::vector<int>(max_y_));
	for (auto i = 0; i < max_x_; ++i)
	{
		for (auto j = 0; j < max_y_; ++j)
		{
			switch (walls[i][j])
			{
			case '1':
				break;

			case '2':
				break;

			case '3':
				break;
			}
		}
	}
}
