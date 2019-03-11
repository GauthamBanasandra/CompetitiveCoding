// WIP

#include <vector>
#include <iostream>

class Selector
{
public:
	Selector(std::size_t n, int k);

	bool Select();

private:
	bool Select(bool& found, std::size_t i_letter, int num_a, int rem);

	const std::size_t n_;
	const int k_;
	std::vector<std::vector<std::vector<short>>> memo_;
};

Selector::Selector(const std::size_t n, const int k) :n_(n), k_(k)
{
	memo_.resize(n_,
		std::vector<std::vector<short>>(n_ + 1,
			std::vector<short>(n*(n - 1) / 2 + 1, -1)));
}

bool Selector::Select()
{
	auto found = false;
	return Select(found, 0, 0, k_);
}

bool Selector::Select(bool& found, const std::size_t i_letter, const int num_a, const int rem)
{
	if (found)
	{
		return true;
	}

	if (rem < 0)
	{
		return false;
	}
	if (i_letter >= n_)
	{
		return rem == 0;
	}

	auto &memo = memo_[i_letter][num_a][rem];
	if (memo != -1)
	{
		return memo == 1;
	}

	const auto a = Select(found, i_letter + 1, num_a + 1, rem);
	const auto b = Select(found, i_letter + 1, num_a, rem - num_a);
	return memo = a || b ? 1 : 0;
}

int main(int argc, char* argv[])
{
	Selector selector(10, 12);
	std::cout << selector.Select() << std::endl;
	return 0;
}
