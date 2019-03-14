#include <iostream>
#include <math.h>

int main()
{
	int n = 0,
		is = 240,
		j = 299,
		il = 0,
		stma_sum = 0,
		ltma_sum = 0;
	int p[1000],
		stma[701],
		ltma[701];

	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> p[i];
	}

	for (int i = is; i <= j; ++i)
	{
		stma_sum += p[i];
	}

	for (int i = il; i <= j; ++i)
	{
		ltma_sum += p[i];
	}

	stma[0] = stma_sum / 60;
	ltma[0] = ltma_sum / 300;
	++j;
	for (int i = 1; j < n; ++i, ++j, ++is, ++il)
	{
		stma[i] = (stma_sum - p[is] + p[j]) / 60;
		ltma[i] = (ltma_sum - p[il] + p[j]) / 300;
	}

	for (int i = 1; i < n - 300 + 1; ++i)
	{
		if ((stma[i - 1] > ltma[i - 1] && stma[i] <= ltma[i]) ||
			(stma[i - 1] < ltma[i - 1] && stma[i] >= ltma[i]) ||
			(stma[i - 1] == ltma[i - 1] && stma[i] != ltma[i]))
		{
			std::cout << (i + 301) << " " << roundf(stma[i] * 100) / 100 << " " << roundf(ltma[i] * 100) / 100 << std::endl;
		}
	}

	return 0;
}