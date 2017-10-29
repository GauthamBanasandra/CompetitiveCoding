#include <stdio.h>
#include <queue>
#include <cassert>

using big_int = unsigned long long;

enum class river_bank { k_left, k_right };
struct Car
{
	int id;
	big_int length;
};

class RiverBank
{
public:
	void add_car(const Car &car) { cars_.push(car); }
	void remove_front_car();
	bool has_cars() const { return !cars_.empty(); }
	Car &front_car();

private:
	std::queue<Car> cars_;
};

inline void RiverBank::remove_front_car()
{
	assert(has_cars());
	cars_.pop();
}

inline Car &RiverBank::front_car()
{
	assert(has_cars());
	return cars_.front();
}

class Ferry
{
public:
	explicit Ferry(const big_int length)
		: current_bank(river_bank::k_left), n_cross(0), free_space_(length), length_(length)
	{
	}

	void move_to_left();
	void move_to_right();
	void unload_cars();
	void load_cars(RiverBank* rb);
	bool has_cars() const { return !cars_.empty(); }
	void add_car(const Car &car);
	bool can_fit(const Car& car) const { return car.length <= free_space_; }

	river_bank current_bank;
	big_int n_cross;

private:
	std::queue<Car> cars_;
	big_int free_space_;
	const big_int length_;
};

inline void Ferry::move_to_left()
{
	++n_cross;
	current_bank = river_bank::k_left;
}

inline void Ferry::move_to_right()
{
	++n_cross;
	current_bank = river_bank::k_right;
}

void Ferry::unload_cars()
{
	while (has_cars())
	{
		cars_.pop();
	}

	free_space_ = length_;
}

void Ferry::load_cars(RiverBank *rb)
{
	while (rb->has_cars() && can_fit(rb->front_car()))
	{
		add_car(rb->front_car());
		rb->remove_front_car();
	}
}

inline void Ferry::add_car(const Car& car)
{
	assert(can_fit(car));
	cars_.push(car);
	free_space_ -= car.length;
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
	void print_log() const { printf("%llu\n", ferry_->n_cross); }

private:
	Ferry *ferry_;
	RiverBank *left_bank_;
	RiverBank *right_bank_;
};

void RiverFerry::begin_transport() const
{
	while (left_bank_->has_cars() || right_bank_->has_cars() || ferry_->has_cars())
	{
		ferry_->unload_cars();
		if (!left_bank_->has_cars() && !right_bank_->has_cars())
		{
			return;
		}

		switch (ferry_->current_bank)
		{
		case river_bank::k_left:
			ferry_->load_cars(left_bank_);
			ferry_->move_to_right();
			break;

		case river_bank::k_right:
			ferry_->load_cars(right_bank_);
			ferry_->move_to_left();
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	big_int c;
	big_int l, m, l_i;
	char bank[10];
	scanf("%llu", &c);
	while (c--)
	{
		scanf("%llu%llu", &l, &m);
		l *= 100;
		Ferry ferry(l);
		RiverBank left_bank;
		RiverBank right_bank;
		for (auto i = 0; i < m; ++i)
		{
			scanf("%llu %s", &l_i, bank);
			assert(l_i <= l);
			const Car car = { i, l_i };
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
