#include <stdio.h>
#include <queue>
#include <cassert>

using big_int = unsigned long long;

enum class river_bank { k_left, k_right };

class RiverBank
{
public:
	void add_car(const int time) { cars_.push(time); }
	void remove_front_car();
	bool has_cars()const { return !cars_.empty(); }
	int front_car();
	bool has_lesser_wait(const RiverBank* other);

private:
	std::queue<int> cars_;
};

inline void RiverBank::remove_front_car()
{
	assert(has_cars());
	cars_.pop();
}

int RiverBank::front_car()
{
	assert(has_cars());
	return cars_.front();
}

inline bool RiverBank::has_lesser_wait(const RiverBank *other)
{
	if (has_cars() && other->has_cars())
	{
		return front_car() <= other->cars_.front();
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
		: clock(0), current_bank(river_bank::k_left), car_count_(0), capacity_(capacity),
		transport_time_(transport_time)
	{
	}

	void move_to_left();
	void move_to_right();
	bool is_vacant() const { return car_count_ < capacity_; }
	void unload_cars();
	void load_cars(RiverBank* rb);
	bool is_empty() const { return car_count_ == 0; }

	big_int clock;
	river_bank current_bank;

private:
	int car_count_;
	int capacity_;
	int transport_time_;
};

inline void Ferry::move_to_left()
{
	clock += transport_time_;
	current_bank = river_bank::k_left;
}

inline void Ferry::move_to_right()
{
	clock += transport_time_;
	current_bank = river_bank::k_right;
}

void Ferry::unload_cars()
{
	while (car_count_-- > 0)
	{
		printf("%llu\n", clock);
	}

	car_count_ = 0;
}

void Ferry::load_cars(RiverBank *rb)
{
	while (is_vacant() && rb->has_cars() && rb->front_car() <= clock)
	{
		++car_count_;
		rb->remove_front_car();
	}

	assert(car_count_ <= capacity_);
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

	void begin_transport() const;

private:
	Ferry *ferry_;
	RiverBank *left_bank_;
	RiverBank *right_bank_;
};

void RiverFerry::begin_transport() const
{
	while (left_bank_->has_cars() || right_bank_->has_cars() || !ferry_->is_empty())
	{
		ferry_->unload_cars();
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
					ferry_->clock = left_bank_->front_car();
				}
				else
				{
					ferry_->clock += right_bank_->front_car() - ferry_->clock;
					assert(ferry_->clock >= 0);
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
					ferry_->clock = right_bank_->front_car();
				}
				else
				{
					ferry_->clock += left_bank_->front_car() - ferry_->clock;
					assert(ferry_->clock >= 0);
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
		while (m--)
		{
			scanf("%d %s", &m_i, bank);
			switch (bank[0])
			{
			case 'l':
				left_bank.add_car(m_i);
				break;
			case 'r':
				right_bank.add_car(m_i);
				break;
			default:
				assert(false);
			}
		}

		RiverFerry river_ferry(&ferry, &left_bank, &right_bank);
		river_ferry.begin_transport();
	}

	return 0;
}
