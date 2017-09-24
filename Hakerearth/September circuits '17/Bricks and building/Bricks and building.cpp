#include <stdio.h>
#include <ios>
#include <unordered_map>

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

	std::unordered_map<int, int> res;
	int q, k;
	scanf("%d", &q);
	while (q--)
	{
		int c = 0;
		scanf("%d", &k);
		if (res.find(k) == res.end())
		{
			for (const auto pair : f)
			{
				if (!(pair.first % k))
				{
					c += pair.second;
				}
			}
			res[k] = c;
		}

		printf("%d\n", res[k]);
	}

	return 0;
}
