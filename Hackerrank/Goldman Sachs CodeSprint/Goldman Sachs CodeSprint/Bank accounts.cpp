#include <stdio.h>
#include <ios>

void BankAccounts()
{
	std::ios::sync_with_stdio(false);

	int test_cases, n;
	double k, x, p, upfront, fee, t_fee;
	scanf("%d", &test_cases);
	while (test_cases--)
	{
		scanf("%d%lf%lf%lf", &n, &k, &x, &upfront);
		fee = 0;
		while (n--)
		{
			scanf("%lf", &p);
			t_fee = x*p / 100.0;
			fee += k > t_fee ? k : t_fee;
		}

		printf("%s\n", fee <= upfront ? "fee" : "upfront");
	}
}