#include <vector>
#include <iostream>

class Counter
{
public:
	Counter(std::size_t num_subjects, int marks_total, int marks_pass);

	int Count();

private:
	int Count(std::size_t i_subject, int rem);

	const int rem_;
	const std::size_t num_subjects_;
	std::vector<std::vector<int>> memo_;
};

Counter::Counter(const std::size_t num_subjects, const int marks_total, const int marks_pass) :rem_(marks_total - num_subjects * marks_pass), num_subjects_(num_subjects)
{
	if (rem_ < 0)
	{
		return;
	}

	memo_.resize(num_subjects_, std::vector<int>(rem_ + 1, -1));
}

int Counter::Count()
{
	return Count(0, rem_);
}

int Counter::Count(const std::size_t i_subject, const int rem)
{
	if (i_subject >= num_subjects_ || rem < 0)
	{
		return 0;
	}

	if (rem == 0)
	{
		return 1;
	}

	auto &memo = memo_[i_subject][rem];
	if (memo != -1)
	{
		return memo;
	}

	const auto exclude = Count(i_subject + 1, rem);
	const auto include = Count(i_subject, rem - 1);
	return memo = exclude + include;
}

int main(int argc, char* argv[])
{
	std::size_t k, n;
	int t, p;

	std::cin >> k;
	while (k--)
	{
		std::cin >> n >> t >> p;
		Counter counter(n, t, p);
		std::cout << counter.Count() << std::endl;
	}
	return 0;
}
