// WIP

#include <vector>
#include <iostream>

class Counter
{
public:
	Counter(std::size_t l, int s);

	long Count() { return Count(0, 0, rem_); }

private:
	long Count(std::size_t i_letter, std::size_t prev_char, int rem);

	const std::size_t l_;
	const int rem_;
	std::vector<std::vector<std::vector<long>>> memo_;
};

Counter::Counter(const std::size_t l, const int s) :l_(l), rem_(s)
{
	memo_.resize(l_,
		std::vector<std::vector<long>>(27,
			std::vector<long>(rem_ + 1, -1)));
}

long Counter::Count(const std::size_t i_letter, const std::size_t prev_char, const int rem)
{
	if (rem < 0 || prev_char > 26)
	{
		return 0;
	}

	if (i_letter >= l_)
	{
		if (rem == 0)
		{
			return 1;
		}
		return 0;
	}

	auto &memo = memo_[i_letter][prev_char][rem];
	if (memo != -1)
	{
		return memo;
	}

	long count = 0;
	for (auto i = prev_char + 1; i <= 26; ++i)
	{
		count += Count(i_letter + 1, i, rem - static_cast<int>(i));
	}
	return memo = count;
}

int main(int argc, char* argv[])
{
	std::size_t t = 0;
	std::size_t l;
	int s;

	while (std::cin >> l >> s, l || s)
	{
		Counter counter(l, s);
		std::cout << "Case " << ++t << ": " << counter.Count() << std::endl;
	}
	return 0;
}
