#include <stdio.h>
#include <ios>
#include <unordered_map>

#define MAX_PLAYERS 1000100
#define MAX_DIE_ROLL 1000100
#define MAX_SQUARES 100

int player_pos[MAX_SQUARES];

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	unsigned long long test_cases, a, b, c;
	int x, y, die_roll;
	std::unordered_map<int, int> transplace;

	scanf("%llu", &test_cases);
	while (test_cases--)
	{
		scanf("%llu%llu%llu", &a, &b, &c);
		transplace.clear();
		for (unsigned long long i = 0; i < a; ++i)
		{
			player_pos[i] = 1;
		}

		while (b--)
		{
			scanf("%d%d", &x, &y);
			transplace[x] = y;
		}

		auto win = false;
		unsigned long long player_now = 0;
		while (c--)
		{
			scanf("%d", &die_roll);
			if (win)
			{
				continue;
			}

			player_pos[player_now] += die_roll;
			const auto find_transplace = transplace.find(player_pos[player_now]);
			if (!(find_transplace == transplace.end()))
			{
				player_pos[player_now] = find_transplace->second;
			}

			if (player_pos[player_now] >= MAX_SQUARES)
			{
				win = true;
				player_pos[player_now] = MAX_SQUARES;
			}

			++player_now;
			if (player_now >= a)
			{
				player_now = 0;
			}
		}

		for (unsigned long long i = 0; i < a; ++i)
		{
			printf("Position of player %llu is %d.\n", i + 1, player_pos[i]);
		}
	}

	return 0;
}
