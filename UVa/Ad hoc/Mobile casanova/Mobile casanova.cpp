#include <stdio.h>
#include <string>
#include <ios>

using big_int = unsigned long long;

int DiffIdx(const std::string &m, const std::string &n)
{
	for (auto i = 0; i < m.length(); ++i)
	{
		if (m[i] != n[i])
		{
			return i;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	big_int n, _s, s, c, tc = 0;
	while (scanf("%llu", &n), n)
	{
		printf("Case %llu:\n", ++tc);
		scanf("%llu", &s);
		_s = s;
		while (n > 0)
		{
			auto is_con = false, c_init = false;
			while (--n)
			{
				scanf("%llu", &c);
				c_init = true;
				if (c - s == 1)
				{
					s = c;
					is_con = true;
					continue;
				}

				break;
			}

			if (is_con)
			{
				const auto _s_str = std::to_string(_s);
				const auto s_str = std::to_string(s);
				printf("0%llu-%s\n", _s, s_str.substr(DiffIdx(s_str, _s_str)).c_str());
			}
			else
			{
				printf("0%llu\n", s);
			}

			if (c_init)
			{
				_s = s = c;
			}
		}

		printf("\n");
	}

	return 0;
}
