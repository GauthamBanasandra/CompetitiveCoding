#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <ios>

namespace uva10465
{
	class Counter
	{
	public:
		Counter(int n, int m, std::size_t t);

		std::string Count();

	private:
		const std::size_t t_;
		const int n_;
		const int m_;
		std::vector<int> memo_;
	};

	Counter::Counter(const int n, const int m, const std::size_t t) :t_(t), n_(n), m_(m)
	{
		memo_.resize(std::max(static_cast<int>(t_), std::max(n_, m_)) + 1);
	}

	std::string Counter::Count()
	{
		memo_[n_] = memo_[m_] = 1;
		for (std::size_t i = 0; i <= t_; ++i)
		{
			const auto count = memo_[i];
			if (count == 0)
			{
				continue;
			}

			if (i + n_ <= t_)
			{
				memo_[i + n_] = count + 1;
			}
			if (i + m_ <= t_)
			{
				memo_[i + m_] = count + 1;
			}
		}

		std::stringstream result;
		if (memo_[t_] != 0)
		{
			result << memo_[t_];
		}
		else
		{
			auto t = t_;
			while (t != 0 && memo_[t] == 0)
			{
				--t;
			}
			result << memo_[t] << " " << t_ - t;
		}
		return result.str();
	}
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n, m;
	std::size_t t;

	while (std::cin >> n >> m >> t, !std::cin.eof())
	{
		uva10465::Counter counter(n, m, t);
		std::cout << counter.Count() << std::endl;
	}
	return 0;
}
