// WIP

#include <vector>
#include <string>
#include <iostream>
#include <cassert>

template<class T>
using Matrix = std::vector<std::vector<T>>;

struct Direction
{
	enum Value
	{
		kWest = 1,
		kNorth = 2,
		kEast = 3,
		kSouth = 4
	};
};

class Pos
{
public:
	Pos(const int x, const int y, Matrix<int> &path, Matrix<Pos> &backtrack) :x_(x), y_(y), path_(path), backtrack_(backtrack) {}

	Pos GetPos(Direction::Value direction) const;
	void MoveTo(const Pos &to);
	Pos Backtrack();

	Pos& operator=(const Pos& other);
	int GetX()const { return x_; }
	int GetY()const { return y_; }

private:
	int x_;
	int y_;
	Matrix<int> &path_;
	Matrix<Pos> &backtrack_;
};

Pos Pos::GetPos(const Direction::Value direction) const
{
	switch (direction) {
	case Direction::kWest:
		return { x_, y_ - 1, path_, backtrack_ };
	case Direction::kNorth:
		return { x_ - 1, y_, path_, backtrack_ };
	case Direction::kEast:
		return { x_, y_ + 1, path_, backtrack_ };
	case Direction::kSouth:
		return { x_ + 1, y_, path_, backtrack_ };
	}
	assert(false);
	return { -1, -1, path_, backtrack_ };
}

void Pos::MoveTo(const Pos& to)
{
	backtrack_[to.x_][to.y_] = *this;
	x_ = to.x_;
	y_ = to.y_;
}

Pos Pos::Backtrack()
{
	path_[x_][y_] = -1;
	const auto previous = backtrack_[x_][y_];
	x_ = previous.x_;
	y_ = previous.y_;
	return *this;
}

Pos& Pos::operator=(const Pos& other)
{
	this->x_ = other.x_;
	this->y_ = other.y_;
	this->backtrack_ = other.backtrack_;
	this->path_ = other.path_;
	return *this;
}

class Simulator
{
public:
	explicit Simulator(const Matrix<short> &walls, int max_x, int max_y);

private:
	bool IsOutside(const int x, const int y) const { return x < 0 || x > max_x_ || y < 0 || y >  max_y_; }
	bool IsOutside(const Pos &pos)const { return IsOutside(pos.GetX(), pos.GetY()); }
	bool IsWall(const Pos &pos, const Direction::Value direction) const { return (walls_[pos.GetX()][pos.GetY()] & 1 << direction) == 1; }
	bool IsValid(const Pos &pos, Direction::Value direction) const;
	bool IsVisited(const Pos &pos) const;

	const int max_x_;
	const int max_y_;
	Matrix<int> walls_;
	Matrix<int> path_;
};

Simulator::Simulator(const Matrix<short>& walls, const int max_x, const int max_y) :max_x_(max_x), max_y_(max_y)
{
	walls_.resize(max_x_, std::vector<int>(max_y_));
	path_.resize(max_x_, std::vector<int>(max_y_));
	for (auto i = 0; i < max_x_; ++i)
	{
		for (auto j = 0; j < max_y_; ++j)
		{
			switch (walls[i][j])
			{
			case 0:
				break;

			case 1:
				walls_[i][j] |= 1 << Direction::kEast;
				if (!IsOutside(i, j + 1))
				{
					walls_[i][j + 1] |= 1 << Direction::kWest;
				}
				break;

			case 2:
				walls_[i][j] |= 1 << Direction::kSouth;
				if (!IsOutside(i + 1, j))
				{
					walls_[i + 1][j] |= 1 << Direction::kNorth;
				}
				break;

			case 3:
				walls_[i][j] |= 1 << Direction::kEast;
				if (!IsOutside(i, j + 1))
				{
					walls_[i][j + 1] |= 1 << Direction::kWest;
				}

				walls_[i][j] |= 1 << Direction::kSouth;
				if (!IsOutside(i + 1, j))
				{
					walls_[i + 1][j] |= 1 << Direction::kNorth;
				}
				break;

			default:
				assert(false);
			}
		}
	}
}

bool Simulator::IsValid(const Pos& pos, const Direction::Value direction) const
{
	const auto next = pos.GetPos(direction);
	if (IsOutside(next))
	{
		return false;
	}
	if (IsWall(pos, direction))
	{
		return false;
	}
	if (IsVisited(next))
	{
		return false;
	}
	return true;
}

bool Simulator::IsVisited(const Pos& pos) const
{
	assert(!IsOutside(pos));
	return path_[pos.GetX()][pos.GetY()] != 0;
}

int main(int argc, char* argv[])
{
	Matrix<short> walls{
		{1, 1, 0},
		{0, 0, 0}
	};

	Simulator simulator(walls, 2, 3);
	return 0;
}
