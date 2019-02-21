// WIP

#include <vector>
#include <iostream>

class CollisionCounter
{
public:
	CollisionCounter(std::size_t word_len, int rem);

	int Count() { return Count(0, 0, rem_); }
private:
	int Count(std::size_t i_word, std::size_t start_c, int rem);

	const std::size_t word_len_;
	const int rem_;
	std::vector<std::vector<int>> memo_;
};

CollisionCounter::CollisionCounter(const std::size_t word_len, const int rem) :word_len_(word_len), rem_(rem)
{
	memo_.resize(word_len_, std::vector<int>(27, -1));
}

int CollisionCounter::Count(const std::size_t i_word, const std::size_t start_c, const int rem)
{
	if (i_word >= word_len_ || start_c > 26 || rem < 0)
	{
		return 0;
	}

	if (i_word == word_len_ - 1 && rem == 0)
	{
		return 1;
	}

	auto &memo = memo_[i_word][start_c];
	if (memo != -1)
	{
		return memo;
	}

	auto count = 0;
	for (auto c = start_c; c <= 26; ++c)
	{
		count += Count(i_word + 1, c + 1, rem - (c + 1));
	}
	return memo = count;
}

int main(int argc, char* argv[])
{
	std::size_t t = 0, l;
	int s;

	while (std::cin >> l >> s, !std::cin.eof())
	{
		CollisionCounter counter(l, s);
		std::cout << "Case " << ++t << ": " << counter.Count() << std::endl;
	}
	return 0;
}
