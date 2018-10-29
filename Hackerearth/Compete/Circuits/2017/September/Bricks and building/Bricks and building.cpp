#include <stdio.h>
#include <ios>
#include <unordered_map>
#include <algorithm>
#include <vector>

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int n, h;
	std::unordered_map<int, int> f;

	scanf("%d", &n);
	for (auto i = 0; i < n; ++i)
	{
		scanf("%d", &h);
		++f[h];
	}

	std::vector<int> heights(f.size());
	int i = 0;
	for (const auto pair : f)
	{
		heights[i++] = pair.first;
	}

	sort(heights.begin(), heights.end());

	std::unordered_map<int, int> res;
	int q, k;
	scanf("%d", &q);
	while (q--)
	{
		int c = 0;
		scanf("%d", &k);
		if (res.find(k) == res.end())
		{
			int l = 0;
			int r = heights.size() - 1;
			int m = l + (r - l) / 2;
			int index = m;
			while (l <= r)
			{
				m = l + (r - l) / 2;

				if (heights[m] == k)
				{
					index = m;
					break;
				}

				if (heights[m] < k)
				{
					l = m + 1;
				}
				else
				{
					r = m - 1;
				}
			}

			index = m;

			for (auto i = index; i < static_cast<int>(heights.size()); ++i)
			{
				if (!(heights[i] % k))
				{
					c += f[heights[i]];
				}
			}

			res[k] = c;
		}

		printf("%d\n", res[k]);
	}

	return 0;
}
