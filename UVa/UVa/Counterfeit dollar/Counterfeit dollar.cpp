#include <stdio.h>
#include <ios>
#include <string.h>
#include <vector>
#include <unordered_set>
#include <cassert>

#define LEFT_LIM 10
#define RIGHT_LIM 10
#define RES_LIM 10

typedef unsigned long long big_int;
char left[LEFT_LIM];
char right[RIGHT_LIM];
char res[RES_LIM];

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::vector<std::pair<std::unordered_set<char>, std::unordered_set<char>>> weighings;
	std::unordered_set<char> non_cft;
	big_int n;

	scanf("%lld", &n);
	while (n--)
	{
		weighings.clear();
		non_cft.clear();
		for (auto m = 0; m < 3; ++m)
		{
			scanf("%s%s%s", left, right, res);

			if (res[0] == 'e')
			{
				for (auto i = 0; i < strlen(left); ++i)
				{
					non_cft.insert(left[i]);
				}

				for (auto i = 0; i < strlen(right); ++i)
				{
					non_cft.insert(right[i]);
				}
			}
			else if (res[0] == 'd')
			{
				std::unordered_set<char> left_set;
				for (auto i = 0; i < strlen(left); ++i)
				{
					left_set.insert(left[i]);
				}

				std::unordered_set<char> right_set;
				for (auto i = 0; i < strlen(right); ++i)
				{
					right_set.insert(right[i]);
				}

				weighings.push_back(make_pair(left_set, right_set));
			}
			else if (res[0] == 'u')
			{
				std::unordered_set<char> left_set;
				for (auto i = 0; i < strlen(left); ++i)
				{
					left_set.insert(left[i]);
				}

				std::unordered_set<char> right_set;
				for (auto i = 0; i < strlen(right); ++i)
				{
					right_set.insert(right[i]);
				}

				weighings.push_back(make_pair(right_set, left_set));
			}
			else { assert(false); }
		}

		auto cft = false;
		for (auto i = 0; i < weighings.size() && !cft; ++i)
		{
			for (const auto c : weighings[i].first)
			{
				if (non_cft.find(c) != non_cft.end())
				{
					cft = false;
					continue;
				}

				cft = true;
				for (auto j = 0; j < weighings.size(); ++j)
				{
					if (i == j) { continue; }
					if (weighings[j].first.find(c) == weighings[j].first.end() &&
						weighings[j].second.find(c) == weighings[j].second.end() ||
						weighings[j].second.find(c) != weighings[j].second.end())
					{
						cft = false;
						break;
					}
				}

				if (cft)
				{
					printf("%c is the counterfeit coin and it is light.\n", c);
					break;
				}
			}

			if (cft) { break; }
			for (const auto c : weighings[i].second)
			{
				if (non_cft.find(c) != non_cft.end())
				{
					cft = false;
					continue;
				}

				cft = true;
				for (auto j = 0; j < weighings.size(); ++j)
				{
					if (i == j) { continue; }
					if (weighings[j].first.find(c) == weighings[j].first.end() &&
						weighings[j].second.find(c) == weighings[j].second.end() ||
						weighings[j].first.find(c) != weighings[j].first.end())
					{
						cft = false;
						break;
					}
				}

				if (cft)
				{
					printf("%c is the counterfeit coin and it is heavy.\n", c);
					break;
				}
			}
		}
	}

	return 0;
}
