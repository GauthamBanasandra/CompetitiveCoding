#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>
#include <ios>

using ll = long long;

class FrequencyTable
{
public:
	FrequencyTable() :max_(0) {}
	explicit FrequencyTable(const std::list<ll> &numbers);

	void Increment(ll value);
	void Decrement(ll value);
	ll GetMax() const { return max_; }

private:
	ll max_;
	std::unordered_map<ll, std::size_t> table_;
};

class Bits
{
public:
	Bits(const std::vector<ll> &bits, const ll k);

	void Rotate();
	ll Query() const { return std::min(k_, frequency_table_.GetMax()); }
	void Print() const;

private:
	std::list<ll> bits_;
	FrequencyTable frequency_table_;
	ll k_;
};

FrequencyTable::FrequencyTable(const std::list<ll>& numbers) : max_(0)
{
	for (const auto number : numbers)
	{
		if (number == 0)
		{
			continue;
		}
		++table_[number];
		max_ = std::max(max_, number);
	}
}

void FrequencyTable::Increment(const ll value)
{
	if (value == 0)
	{
		return;
	}

	++table_[value];
	max_ = std::max(max_, value);
}

void FrequencyTable::Decrement(const ll value)
{
	if (value == 0)
	{
		return;
	}

	const auto find_it = table_.find(value);
	assert(find_it != table_.end());

	--find_it->second;
	if (find_it->second == 0)
	{
		table_.erase(find_it);
		if (value == max_)
		{
			max_ = 0;
		}
	}
}

Bits::Bits(const std::vector<ll>& bits, const ll k) : k_(k)
{
	for (auto bit : bits)
	{
		if (bit == 0)
		{
			bits_.emplace_back(bit);
		}
		else
		{
			if (bits_.empty() || bits_.back() == 0)
			{
				bits_.emplace_back(0);
			}
			++bits_.back();
		}
	}
	frequency_table_ = FrequencyTable(bits_);
}

void Bits::Rotate()
{
	assert(!bits_.empty());

	if (bits_.size() == 1)
	{
		return;
	}

	const ll last_bits = bits_.back();
	if (last_bits == 0)
	{
		bits_.pop_back();
		bits_.emplace_front(last_bits);
		return;
	}

	if (bits_.front() == 0)
	{
		bits_.emplace_front(0);
	}

	frequency_table_.Decrement(bits_.front());
	frequency_table_.Decrement(bits_.back());

	++bits_.front();
	--bits_.back();

	frequency_table_.Increment(bits_.front());
	frequency_table_.Increment(bits_.back());

	if (bits_.back() == 0)
	{
		bits_.pop_back();
	}
}

void Bits::Print() const
{
	std::cout << "Max : " << Query() << std::endl;
	for (auto bit : bits_)
	{
		if (bit == 0)
		{
			std::cout << 0 << " ";
		}
		for (ll i = 0; i < bit; ++i)
		{
			std::cout << 1 << " ";
		}
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	ll k;
	std::size_t n, q;
	std::string query;
	std::vector<ll> bits;

	std::cin >> n >> q >> k;
	bits.resize(n);
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> bits[i];
	}
	Bits sequence(bits, k);

	std::cin >> query;
	for (const auto c : query)
	{
		switch (c)
		{
		case '?':
			std::cout << sequence.Query() << std::endl;
			break;

		case  '!':
			sequence.Rotate();
			break;

		default:
			assert(false);
		}
	}
	return 0;
}
