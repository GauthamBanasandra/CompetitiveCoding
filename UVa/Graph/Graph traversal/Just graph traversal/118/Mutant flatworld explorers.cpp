#include <vector>
#include <unordered_set>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include <ios>

namespace uva118
{
	struct Direction
	{
		enum Type { kNorth, kEast, kSouth, kWest };

		static Type LeftOf(const Type direction) { return static_cast<Type>(direction - 1 < kNorth ? kWest : direction - 1); }
		static Type RightOf(const Type direction) { return  static_cast<Type>(direction + 1 > kWest ? kNorth : direction + 1); }
		static char ToChar(Type direction);
		static Type FromChar(char direction);
	};

	char Direction::ToChar(const Type direction)
	{
		switch (direction)
		{
		case kNorth:
			return 'N';

		case kEast:
			return 'E';

		case kSouth:
			return 'S';

		case kWest:
			return 'W';
		}
		assert(false);
		return '\0';
	}

	Direction::Type Direction::FromChar(const char direction)
	{
		switch (direction)
		{
		case 'N':
			return kNorth;

		case 'E':
			return kEast;

		case 'S':
			return kSouth;

		case 'W':
			return kWest;

		default:
			assert(false);
		}
		return kNorth;
	}

	struct Pos
	{
		Pos() = default;
		Pos(const int x, const int y, const char direction) :x(x), y(y), direction(Direction::FromChar(direction)) {}

		std::string ToString() const;
		void TurnLeft() { direction = Direction::LeftOf(direction); }
		void TurnRight() { direction = Direction::RightOf(direction); }
		void MoveForward();

		bool operator==(const Pos &other) const { return x == other.x && y == other.y; }
		std::size_t operator()(const Pos &pos) const { return pos.x * 100000 + pos.y; }

		int x{ 0 };
		int y{ 0 };
		Direction::Type direction{ Direction::Type::kNorth };
	};

	std::string Pos::ToString() const
	{
		std::ostringstream out;
		out << x << ' ' << y << ' ' << Direction::ToChar(direction);
		return out.str();
	}

	inline void Pos::MoveForward()
	{
		direction == Direction::kNorth || direction == Direction::kEast ?
			++(direction == Direction::kNorth ? y : x) :
			--(direction == Direction::kSouth ? y : x);
	}

	class Flatworld
	{
	public:
		Flatworld(const int max_x, const int max_y) :max_x_(max_x), max_y_(max_y) {}

		std::string GetFinalPos(const Pos& initial, const std::string& instructions);

	private:
		bool IsOutside(const Pos &pos) const { return pos.x < 0 || pos.x > max_x_ || pos.y < 0 || pos.y > max_y_; }
		static Pos Execute(char instruction, const Pos& current);
		bool IsScented(const Pos& pos)const { return scented_.find(pos) != scented_.end(); }

		const int max_x_;
		const int max_y_;
		std::unordered_set<Pos, Pos> scented_;
	};

	std::string Flatworld::GetFinalPos(const Pos& initial, const std::string& instructions)
	{
		auto current = initial;
		for (const auto instruction : instructions)
		{
			const auto next = Execute(instruction, current);
			if (IsOutside(next))
			{
				if (IsScented(current))
				{
					continue;
				}
				scented_.insert(current);
				return current.ToString() + " LOST";
			}
			current = next;
		}
		return current.ToString();
	}

	Pos Flatworld::Execute(const char instruction, const Pos& current)
	{
		auto next = current;
		switch (instruction)
		{
		case 'L':
			next.TurnLeft();
			break;

		case 'R':
			next.TurnRight();
			break;

		case 'F':
			next.MoveForward();
			break;

		default:
			assert(false);
		}
		return next;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int max_x;
	int max_y;
	int initial_x;
	int initial_y;
	char initial_direction;
	std::string instructions;

	std::cin >> max_x >> max_y;
	uva118::Flatworld flatworld(max_x, max_y);

	while (std::cin >> initial_x >> initial_y >> initial_direction, !std::cin.eof())
	{
		std::cin >> instructions;
		std::cout << flatworld.GetFinalPos({ initial_x, initial_y, initial_direction }, instructions) << std::endl;
	}
	return 0;
}
