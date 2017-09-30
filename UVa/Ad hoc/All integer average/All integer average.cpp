#include <stdio.h>
#include <math.h>
#include <ios>

using big_int = long long;

big_int Gcd(big_int m, big_int n)
{
	big_int r;
	while (n)
	{
		r = m%n;
		m = n;
		n = r;
	}

	return m;
}
int CountDigits(big_int num)
{
	auto digits = 0;
	while (num)
	{
		++digits;
		num /= 10;
	}

	return digits;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	auto tc = 0;
	big_int c;
	while (scanf("%lld", &c), c)
	{
		printf("Case %d:\n", ++tc);

		big_int b = 0, _b;
		for (auto i = 0; i < c; ++i)
		{
			scanf("%lld", &_b);
			b += _b;
		}

		const auto is_neg = b < 0;
		b = abs(b);
		if (!(b % c))
		{
			printf("%s%lld\n", is_neg ? "- " : "", b / c);
		}
		else
		{
			const auto gcd = Gcd(b, c);
			b /= gcd;
			c /= gcd;
			if (b < c)
			{
				const auto c_digits = CountDigits(c);
				const auto padding = (is_neg ? 2 : 0) + c_digits;
				printf("%*lld\n", padding, b);
				if (is_neg)
				{
					printf("- ");
				}

				for (auto i = 0; i < c_digits; ++i)
				{
					printf("-");
				}

				printf("\n%*lld\n", padding, c);
			}
			else if (b > c)
			{
				const auto a = b / c;
				b %= c;
				const auto a_digits = CountDigits(a);
				const auto c_digits = CountDigits(c);
				const auto padding = (is_neg ? 2 : 0) + a_digits + c_digits;
				printf("%*lld\n", padding, b);
				printf("%s%lld", is_neg ? "- " : "", a);

				for (auto i = 0; i < c_digits; ++i)
				{
					printf("-");
				}

				printf("\n%*lld\n", padding, c);
			}
		}
	}

	return 0;
}
