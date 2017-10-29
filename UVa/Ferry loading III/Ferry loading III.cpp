#include <stdio.h>
#include <queue>
#include <cassert>

using big_int = unsigned long long;

enum class river_bank { k_left, k_right };
struct Car
{
	int id;
	int arrival_time;
	big_int unboard_time;
};

bool operator<(Car const &lhs, Car const &rhs) noexcept
{
	return rhs.id < lhs.id;
}

class RiverBank
{
public:
	void add_car (const Car &car) noexcept { cars_.push(car); }
	void remove_front_car() noexcept;
	bool has_cars() const noexcept { return !cars_.empty(); }
	Car &front_car() noexcept;
	bool has_lesser_wait(const RiverBank* other) noexcept;

private:
	std::queue<Car> cars_;
};

inline void RiverBank::remove_front_car() noexcept
{
	assert(has_cars());
	cars_.pop();
}

Car &RiverBank::front_car() noexcept
{
	assert(has_cars());
	return cars_.front();
}

inline bool RiverBank::has_lesser_wait(const RiverBank *other) noexcept
{
	if (has_cars() && other->has_cars())
	{
		return front_car().arrival_time <= other->cars_.front().arrival_time;
	}

	if (has_cars() && !other->has_cars())
	{
		return true;
	}

	if (!has_cars() && other->has_cars())
	{
		return false;
	}

	return true;
}

class Ferry
{
public:
	Ferry(const int capacity, const int transport_time)
		: clock(0), current_bank(river_bank::k_left), capacity_(capacity),
		transport_time_(transport_time)
	{
	}

	void move_to_left() noexcept;
	void move_to_right() noexcept;
	bool is_vacant() const noexcept { return cars_.size() < capacity_; }
	void unload_cars(std::priority_queue<Car> &ferry_log) noexcept;
	void load_cars(RiverBank* rb) noexcept;
	bool is_empty() const noexcept { return cars_.empty(); }
	void add_car(const Car &car) noexcept { cars_.push(car); }

	big_int clock;
	river_bank current_bank;

private:
	std::queue<Car> cars_;
	int capacity_;
	int transport_time_;
};

inline void Ferry::move_to_left() noexcept
{
	clock += transport_time_;
	current_bank = river_bank::k_left;
}

inline void Ferry::move_to_right() noexcept
{
	clock += transport_time_;
	current_bank = river_bank::k_right;
}

void Ferry::unload_cars(std::priority_queue<Car>& ferry_log) noexcept
{
	while (!is_empty())
	{
		auto& car = cars_.front();
		car.unboard_time = clock;
		ferry_log.push(car);
		cars_.pop();
	}
}

void Ferry::load_cars(RiverBank *rb) noexcept
{
	while (is_vacant() && rb->has_cars() && rb->front_car().arrival_time <= clock)
	{
		add_car(rb->front_car());
		rb->remove_front_car();
	}

	assert(cars_.size() <= capacity_);
}

class RiverFerry
{
public:
	RiverFerry(Ferry* ferry, RiverBank* left_bank, RiverBank* right_bank)
		: ferry_(ferry),
		left_bank_(left_bank),
		right_bank_(right_bank)
	{
	}

	void begin_transport() noexcept;
	void print_log() noexcept;

private:
	Ferry *ferry_;
	RiverBank *left_bank_;
	RiverBank *right_bank_;
	std::priority_queue<Car> ferry_log_;
};

void RiverFerry::begin_transport() noexcept
{
	while (left_bank_->has_cars() || right_bank_->has_cars() || !ferry_->is_empty())
	{
		ferry_->unload_cars(ferry_log_);
		switch (ferry_->current_bank)
		{
		case river_bank::k_left:
			ferry_->load_cars(left_bank_);
			if (ferry_->is_empty())
			{
				if (!left_bank_->has_cars() && !right_bank_->has_cars())
				{
					return;
				}

				if (left_bank_->has_lesser_wait(right_bank_))
				{
					ferry_->clock = left_bank_->front_car().arrival_time;
				}
				else
				{
					if (right_bank_->front_car().arrival_time > ferry_->clock)
					{
						ferry_->clock += right_bank_->front_car().arrival_time - ferry_->clock;
					}

					ferry_->move_to_right();
				}
			}
			else
			{
				ferry_->move_to_right();
			}
			break;

		case river_bank::k_right:
			ferry_->load_cars(right_bank_);
			if (ferry_->is_empty())
			{
				if (!left_bank_->has_cars() && !right_bank_->has_cars())
				{
					return;
				}

				if (right_bank_->has_lesser_wait(left_bank_))
				{
					ferry_->clock = right_bank_->front_car().arrival_time;
				}
				else
				{
					if (left_bank_->front_car().arrival_time > ferry_->clock)
					{
						ferry_->clock += left_bank_->front_car().arrival_time - ferry_->clock;
					}

					ferry_->move_to_left();
				}
			}
			else
			{
				ferry_->move_to_left();
			}
			break;
		}
	}
}

void RiverFerry::print_log() noexcept
{
	while (!ferry_log_.empty())
	{
		auto &entry = ferry_log_.top();
		printf("%llu\n", entry.unboard_time);
		ferry_log_.pop();
	}
}

int main(int argc, char* argv[])
{
	big_int c, t_c = 0;
	int n, m, t, m_i;
	char bank[10];
	scanf("%llu", &c);
	while (c--)
	{
		++t_c;
		if (t_c > 1)
		{
			printf("\n");
		}

		scanf("%d%d%d", &n, &t, &m);
		Ferry ferry(n, t);
		RiverBank left_bank;
		RiverBank right_bank;
		for (auto i = 0; i < m; ++i)
		{
			scanf("%d %s", &m_i, bank);
			const Car car = { i, m_i };
			switch (bank[0])
			{
			case 'l':
				left_bank.add_car(car);
				break;

			case 'r':
				right_bank.add_car(car);
				break;
			default:
				assert(false);
			}
		}

		RiverFerry river_ferry(&ferry, &left_bank, &right_bank);
		river_ferry.begin_transport();
		river_ferry.print_log();
	}

	return 0;
}
