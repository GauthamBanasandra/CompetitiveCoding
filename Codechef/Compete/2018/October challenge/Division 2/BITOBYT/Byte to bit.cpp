//
// Created by Gautham on 18-10-2018.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <ios>

using ll = long long;

enum class CitizenType { kBit, kNibble, KByte };

class ByteLand
{
public:
	explicit ByteLand(std::size_t max_time);
	const std::vector<long long>& GetByteLandState(std::size_t n) const;

private:
	void Print() const;

	std::vector<std::vector<ll>> citizens_;
};

ByteLand::ByteLand(const std::size_t max_time)
{
	citizens_.resize(static_cast<std::size_t>(max_time) + 1);
	citizens_[0].resize(3);
	citizens_[0][0] = 1;
	auto type = CitizenType::kBit;

	for (std::size_t i = 1, i_citizen = 0, i_switch = 2; i <= max_time; ++i)
	{
		auto population = citizens_[i - 1][i_citizen];
		if (i > i_switch)
		{
			switch (type)
			{
			case CitizenType::kBit:
				i_citizen = 1;
				i_switch += 8;
				type = CitizenType::kNibble;
				break;

			case CitizenType::kNibble:
				i_citizen = 2;
				i_switch += 16;
				type = CitizenType::KByte;
				break;

			case CitizenType::KByte:
				i_citizen = 0;
				i_switch += 2;
				population *= 2;
				type = CitizenType::kBit;
				break;

			default:
				assert(false);
			}
		}

		citizens_[i].resize(3);
		citizens_[i][i_citizen] = population;
	}
}

const std::vector<ll>& ByteLand::GetByteLandState(const std::size_t n) const
{
	return citizens_[n];
}

void ByteLand::Print() const
{
	for (std::size_t i = 0, num_citizens = citizens_.size(); i < num_citizens; ++i)
	{
		std::cout << i << " : " << citizens_[i][0] << " " << citizens_[i][1] << " " << citizens_[i][2] << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	ByteLand byte_land(1600);

	int t;
	std::size_t n;
	std::cin >> t;

	while (t--)
	{
		std::cin >> n;
		auto state = byte_land.GetByteLandState(n);
		std::cout << state[0] << " " << state[1] << " " << state[2] << std::endl;
	}
	return 0;
}
