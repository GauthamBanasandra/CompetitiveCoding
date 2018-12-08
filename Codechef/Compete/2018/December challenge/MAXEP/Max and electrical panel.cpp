#include <iostream>
#include <cassert>

class Interactor
{
public:
	Interactor(const long n, const long cost) :n_(n), cost_(cost), coins_(1000) {}

	void Interact();

private:
	static long Read();
	void Fix();
	long Guess(long y);
	static void Conclude(long y);

	const long n_;
	const long cost_;
	long coins_;
};

long Interactor::Read()
{
	long n;
	std::cin >> n;
	return n;
}

void Interactor::Fix()
{
	coins_ -= cost_;
	std::cout << 2 << std::endl;
}

long Interactor::Guess(const long y)
{
	--coins_;
	std::cout << 1 << " " << y << std::endl;

	long state;
	std::cin >> state;
	return state;
}

void Interactor::Conclude(const long y)
{
	std::cout << 3 << " " << y << std::endl;
}

void Interactor::Interact()
{
	long l = 1;
	auto h = n_;

	while (h - l > 1)
	{
		if (coins_ < 1)
		{
			return;
		}

		const auto m = l + (h - l) / 2;
		switch (Guess(m))
		{
		case 0:
			l = m;
			break;

		case 1:
			if (coins_ < cost_)
			{
				return;
			}
			Fix();
			h = m;
			break;

		default:
			assert(false);
		}
	}

	if (coins_ < 1)
	{
		return;
	}

	if (Guess(l) == 0)
	{
		Conclude(h);
	}
	else
	{
		Conclude(l);
	}
}

int main(int argc, char* argv[])
{
	long n, c;
	std::cin >> n >> c;
	Interactor interactor(n, c);
	interactor.Interact();
	return 0;
}
