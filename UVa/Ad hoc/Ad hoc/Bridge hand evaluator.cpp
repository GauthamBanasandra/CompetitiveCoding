#include <ios>
#include <unordered_map>

#define MAX_CARD_CHAR 2
#define MAX_STOP_SIZE 85
#define SUITS_SIZE 4

char card[MAX_CARD_CHAR];
bool stopped[MAX_STOP_SIZE];
char suit_order[SUITS_SIZE] = { 'S', 'H', 'D', 'C' };

void BridgeHandEvaluator()
{
	std::ios::sync_with_stdio(false);

	std::unordered_map<char, unsigned long long>suit_f;
	std::unordered_map<char, unsigned long long>rank_f;
	std::unordered_map<char, std::unordered_map<char, unsigned long long>>suit_rank_f;
	std::unordered_map<char, std::unordered_map<char, unsigned long long>>rank_suit_f;

	for (char suit : suit_order)
	{
		suit_f[suit] = 0;
	}

	char ch;
	long long suit_bid_pts = 0, no_trump_pts = 0;
	while ((ch = getchar()) != EOF)
	{
		switch (ch)
		{
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'T':
			card[0] = ch;
			break;
		case 'J':
			card[0] = ch;
			no_trump_pts += 1;
			break;
		case 'Q':
			card[0] = ch;
			no_trump_pts += 2;
			break;
		case 'K':
			card[0] = ch;
			no_trump_pts += 3;
			break;
		case 'A':
			card[0] = ch;
			no_trump_pts += 4;
			break;

		case 'S':
		case 'H':
		case 'D':
		case 'C':
			card[1] = ch;
			++suit_f[ch];
			++rank_f[card[0]];
			++suit_rank_f[ch][card[0]];
			++rank_suit_f[card[0]][ch];
			break;

		case ' ':
			break;

		case '\n':
			for (auto pair : rank_suit_f['K'])
			{
				if (suit_f[pair.first] <= 1)
				{
					--no_trump_pts;
				}
			}

			for (auto pair : rank_suit_f['Q'])
			{
				if (suit_f[pair.first] <= 2)
				{
					--no_trump_pts;
				}
			}

			for (auto pair : rank_suit_f['J'])
			{
				if (suit_f[pair.first] <= 3)
				{
					--no_trump_pts;
				}
			}

			suit_bid_pts = no_trump_pts;

			bool all_stopped = true;
			for (auto pair : suit_f)
			{
				switch (pair.second)
				{
				case 2:
					++suit_bid_pts;
					break;
				case 0:
				case 1:
					suit_bid_pts += 2;
					break;
				}

				if (all_stopped && !(suit_rank_f[pair.first]['A'] ||
					suit_rank_f[pair.first]['K'] && suit_f[pair.first] > 1 ||
					suit_rank_f[pair.first]['Q'] && suit_f[pair.first] > 2))
				{
					all_stopped = false;
				}
			}

			if (no_trump_pts >= 16 && all_stopped)
			{
				printf("BID NO-TRUMP\n");
			}
			else if (suit_bid_pts >= 14)
			{
				unsigned long long max = 0;
				int max_idx = -1;
				for (int i = 0; i < SUITS_SIZE; ++i)
				{
					if (suit_f[suit_order[i]] > max)
					{
						max = suit_f[suit_order[i]];
						max_idx = i;
					}
				}

				printf("BID %c\n", suit_order[max_idx]);
			}
			else
			{
				printf("PASS\n");
			}


			for (char suit : suit_order)
			{
				stopped[suit] = false;
			}

			for (char suit : suit_order)
			{
				suit_f[suit] = 0;
			}

			suit_bid_pts = 0, no_trump_pts = 0;
			rank_f.clear();
			suit_rank_f.clear();
			rank_suit_f.clear();
			break;
		}
	}
}
