#include <stdio.h>
#include <unordered_set>
#include <string>
#include <unordered_map>

void Print(const std::string &p1, const std::string &p2, const std::unordered_set<std::string> &child_types) noexcept
{
	printf("%s %s:\t", p1.c_str(), p2.c_str());
	for (auto child_type : child_types)
	{
		printf("%s ", child_type.c_str());
	}
	printf("\n");
}

void PrintPpc(const std::unordered_map<std::string, std::unordered_set<std::string>> &ppc)
{
	for (auto pair : ppc)
	{
		printf("Parents:\t%s\n", pair.first.c_str());
		for (auto child_type : pair.second)
		{
			printf("%s ", child_type.c_str());
		}

		printf("\n");
	}
}

void PrintPcp(const std::unordered_map<std::string, std::unordered_set<std::string>> &pcp)
{
	for (auto pair : pcp)
	{
		printf("Parent-child:\t%s\n", pair.first.c_str());
		for (auto parent_type : pair.second)
		{
			printf("%s ", parent_type.c_str());
		}

		printf("\n");
	}
}