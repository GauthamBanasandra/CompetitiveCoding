#include <vector>
#include <iostream>

namespace uva10446
{
	class Counter
	{
	public:
		Counter(int64_t n, int64_t back);
		int64_t CountTrib();

	private:
		int64_t trib(int n, unsigned int back);

		const int64_t n_;
		const int64_t back_;
		int64_t counter_;
		std::vector<std::vector<int64_t>> memo_;
	};

	Counter::Counter(const int64_t n, const int64_t back) :n_(n), back_(back), counter_(0)
	{
		memo_.resize(n_ + 1, std::vector<int64_t>(back_ + 1, -1));
	}

	int64_t Counter::CountTrib()
	{
		trib(n_, back_);
		return counter_;
	}


	int64_t Counter::trib(const int n, const unsigned back)
	{
		if (n != back)
		{
			++counter_;
		}

		if (n <= 0) return 0;
		if (n == 1) return 1;
		auto &memo = memo_[n][back];
		if (memo != -1)
		{
			counter_ += memo;
			return memo;
		}


		int64_t sum = 0;
		for (auto i = 1; i <= back; i++)
		{
			sum += trib(n - i, back) + 1;
		}
		return memo = sum;
	}
}

int main(int argc, char* argv[])
{
	uva10446::Counter counter(6, 6);
	std::cout << counter.CountTrib() << std::endl;
	return 0;
}
