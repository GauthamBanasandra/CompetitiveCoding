#include <stdio.h>
#include <algorithm>
#include <string>

#define MAX_LINE_SIZE 60

char line[MAX_LINE_SIZE];

int main(int argc, char* argv[])
{
	while (scanf("%s", line), line[0] != '#')
	{
		std::string line_str = line;
		const auto is_last = next_permutation(line_str.begin(), line_str.end());
		printf("%s\n", is_last ? line_str.c_str() : "No Successor");
	}

	return 0;
}
