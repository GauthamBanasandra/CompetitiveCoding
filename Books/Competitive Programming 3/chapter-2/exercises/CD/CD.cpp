#include <stdio.h>
#include <unordered_set>

using big_int = unsigned long long;

int main(int argc, char* argv[])
{
	big_int n, m, id;
	std::unordered_set<big_int> jack;
	while (scanf("%llu%llu\n", &n, &m), n || m)
	{
		jack.clear();
		big_int count = 0;
		while (n--)
		{
			scanf("%llu\n", &id);
			jack.insert(id);
		}

		while (m--)
		{
			scanf("%llu\n", &id);
			if (jack.find(id) != jack.end())
			{
				++count;
			}
		}

		printf("%llu\n", count);
	}

	return 0;
}
