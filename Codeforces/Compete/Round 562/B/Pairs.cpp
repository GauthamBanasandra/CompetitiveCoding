#include <vector>
#include <unordered_map>
#include <iostream>

long GetMax(const std::unordered_map<long, long>& f)
{
	auto max_value = -1;
	auto max_element = -1;
	for (const auto& item : f)
	{
		if (item.second > max_value)
		{
			max_value = item.second;
			max_element = item.first;
		}
	}
	return max_element;
}

bool IsPossible(const std::vector<std::pair<long, long>>& pairs)
{
	std::unordered_map<long, long> f;
	for (const auto number : pairs)
	{
		++f[number.first];
		if (number.first != number.second)
		{
			++f[number.second];
		}
	}

	const auto x = GetMax(f);
	f.erase(x);
	const auto y = GetMax(f);
	for (const auto& pair : pairs)
	{
		if (!(pair.first == x || pair.first == y ||
			pair.second == x || pair.second == y))
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	long n, m;
	std::cin >> n >> m;
	std::vector<std::pair<long, long>> pairs(m);
	for (long i = 0; i < m; ++i)
	{
		std::cin >> pairs[i].first >> pairs[i].second;
	}

	std::cout << (IsPossible(pairs) ? "YES" : "NO") << std::endl;
	return 0;
}
