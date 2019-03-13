#include <string>
#include <unordered_set>
#include <iostream>
#include <ios>

class Reducer
{
public:
	bool IsReducible(const std::string& s);

private:
	std::unordered_set<std::string> memo_;
};

bool Reducer::IsReducible(const std::string& s)
{
	if (s.empty())
	{
		return true;
	}
	if (memo_.find(s) != memo_.end())
	{
		return false;
	}

	for (std::size_t i = 0ul, len = s.length(); i < len - 1; ++i)
	{
		if (s[i] != s[i + 1])
		{
			continue;
		}

		const auto i_start = i;
		auto i_end = i;
		while (i_end < len && s[i] == s[i_end])
		{
			++i_end;
		}

		std::string reduced_head(s.begin(), s.begin() + i_start);
		std::string reduced_tail(s.begin() + i_end, s.end());
		const auto reduced = reduced_head + reduced_tail;

		if (IsReducible(reduced))
		{
			return true;
		}
		memo_.insert(reduced);
		i = i_end - 1;
	}
	memo_.insert(s);
	return false;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	std::size_t t;
	std::string s;
	Reducer reducer;

	std::cin >> t;
	while (t--)
	{
		std::cin >> s;
		std::cout << reducer.IsReducible(s) << std::endl;
	}
	return 0;
}
