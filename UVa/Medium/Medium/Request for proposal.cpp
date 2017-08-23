#include <ios>
#include <map>
#include <vector>

#define MAX_STRLEN 85

void ReadWord(char* word);

void RequestForProposal()
{
	std::ios::sync_with_stdio(false);

	int n, r, rfp = 0;
	unsigned long long p;
	long double d;
	char word[MAX_STRLEN];
	while (scanf("%d%llu\n", &n, &p), (n || p))
	{
		if (rfp > 0)
		{
			printf("\n");
		}

		int max_req = -1;
		std::map<int, std::vector<std::string>> req_count_name;
		std::map<int, std::pair<std::string, long double>> req_count_cost;
		// Skip the words.
		for (int i = 0; i < n; ++i)
		{
			ReadWord(word);
		}

		// For each proposal -
		for (int i = 0; i < p; ++i)
		{
			// Proposal name.
			ReadWord(word);

			// Cost and met requirements.
			scanf("%lf%d\n", &d, &r);

			req_count_name[r].push_back(word);

			auto name_cost = std::pair<std::string, long double>(word, d);
			auto found = req_count_cost.find(r);
			if (found == req_count_cost.end())
			{
				req_count_cost[r] = name_cost;
			}
			else if (d < found->second.second)
			{
				req_count_cost[r] = name_cost;
			}

			if (r > max_req)
			{
				max_req = r;
			}

			// Consume the words.
			for (int j = 0; j < r; ++j)
			{
				ReadWord(word);
			}
		}

		printf("RFP #%d\n", ++rfp);
		if (req_count_name[max_req].size() == 1)
		{
			printf("%s\n", req_count_name[max_req][0].c_str());
		}
		else
		{
			printf("%s\n", req_count_cost[max_req].first.c_str());
		}
	}
}

void ReadWord(char* word)
{
	char ch;
	int i = 0;
	while ((ch=getchar())!='\n')
	{
		word[i++] = ch;
	}

	word[i] = '\0';
}