#include <vector>
#include <iostream>

int NearBinSearch_(const std::vector<int> &a, int k)
{
	int l = 0;
	int r = a.size() - 1;
	int m = l + (r - l) / 2;
	while (l <= r)
	{
		m = l + (r - l) / 2;

		if (a[m] == k)
		{
			return m;
		}

		if (a[m] < k)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}
	}

	return m;
}

int main_(int argc, char* argv[])
{
	std::vector<int> a = { 0, 1, 2, 5 };
	std::cout << NearBinSearch_(a, 3) << std::endl;
	return 0;
}
