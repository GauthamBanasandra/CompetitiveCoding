#include <tuple>
#include <vector>
#include <string>

namespace TopcoderAB
{
	using Pos = std::tuple<std::size_t, int, int>;

	struct Metadata
	{
		Pos pos{ 0, -1, -1 };
		char data{ '\0' };
	};

	class Selector
	{
	public:
		Selector(std::size_t n, int k);

		std::string Select();

	private:
		bool Select(bool& found, std::size_t i_letter, int num_a, int rem);

		std::string Reconstruct() const;

		const std::size_t n_;
		const int k_;
		std::vector<std::vector<std::vector<short>>> memo_;
		std::vector<std::vector<std::vector<Metadata>>> memo_selection_;
	};

	Selector::Selector(const std::size_t n, const int k) :n_(n), k_(k)
	{
		memo_.resize(n_,
			std::vector<std::vector<short>>(n_ + 1,
				std::vector<short>(n*(n - 1) / 2 + 1, -1)));

		memo_selection_.resize(n_,
			std::vector<std::vector<Metadata>>(n_ + 1,
				std::vector<Metadata>(n*(n - 1) / 2 + 1)));
	}

	std::string Selector::Select()
	{
		auto found = false;
		if (Select(found, 0, 0, k_))
		{
			return Reconstruct();
		}
		return "";
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
			return (memo == 1);
		}

		const auto a = Select(found, i_letter + 1, num_a + 1, rem);
		if (a)
		{
			memo_selection_[i_letter][num_a][rem].pos = Pos{ i_letter + 1, num_a + 1, rem };
			memo_selection_[i_letter][num_a][rem].data = 'A';
			return (memo = true);
		}
		const auto b = Select(found, i_letter + 1, num_a, rem - num_a);
		if (b)
		{
			memo_selection_[i_letter][num_a][rem].pos = Pos{ i_letter + 1, num_a, rem - num_a };
			memo_selection_[i_letter][num_a][rem].data = 'B';
			return (memo = true);
		}
		return false;
	}

	std::string Selector::Reconstruct() const
	{
		std::string data(n_, '\0');
		std::size_t i_letter = 0;
		auto num_a = 0;
		auto rem = k_;

		while (i_letter < n_)
		{
			const auto next = memo_selection_[i_letter][num_a][rem];
			data[i_letter] = next.data;
			std::tie(i_letter, num_a, rem) = next.pos;
		}
		return data;
	}
}

class AB
{
public:
	static std::string createString(int n, int k);
};

std::string AB::createString(const int n, const int k)
{
	TopcoderAB::Selector selector(static_cast<std::size_t>(n), k);
	return selector.Select();
}
