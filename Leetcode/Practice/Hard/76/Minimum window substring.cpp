// WA

#include <string>
#include <unordered_map>
#include <limits>
#include <iostream>

const auto infinity = std::numeric_limits<int>::max();

class Frequency
{
public:
	explicit Frequency(const std::string& target);

	bool Add(char c);
	bool Delete(char c);
	bool IsValid(const char c) const { return codex_.find(c) != codex_.end(); }

private:
	std::unordered_map<char, int> frequency_;
	std::unordered_map<char, int> codex_;
	int target_len_;
	int current_len_{ 0 };
};

Frequency::Frequency(const std::string& target)
{
	for (const auto c : target)
	{
		frequency_[c] = 0;
		++codex_[c];
	}
	target_len_ = static_cast<int>(codex_.size());
}

bool Frequency::Add(const char c)
{
	++frequency_[c];
	if (frequency_[c] == codex_[c])
	{
		++current_len_;
	}
	return current_len_ == target_len_;
}

bool Frequency::Delete(const char c)
{
	if (frequency_[c] == codex_[c])
	{
		return false;
	}

	--frequency_[c];
	return true;
}

std::string GetMinWindow(const std::string& s, const std::string& target)
{
	if (target.size()>s.size())
	{
		return "";
	}
	Frequency frequency(target);
	std::pair<int, char> start{ -1, '\0' };
	std::pair<int, char> end{ -1, '\0' };
	auto min_window = infinity;

	for (auto i = 0, len = static_cast<int>(s.size()); i < len; ++i)
	{
		if (!frequency.IsValid(s[i]))
		{
			continue;
		}
		if (start.first == -1)
		{
			start = { i, s[i] };
		}
		if (!frequency.Add(s[i]))
		{
			continue;
		}
		if (i - start.first + 1 < min_window)
		{
			min_window = i - start.first + 1;
			end = { i, s[i] };
		}
		if (s[i] != start.second)
		{
			continue;
		}

		for (auto j = start.first; j < i; ++j)
		{
			if (!frequency.IsValid(s[j]))
			{
				continue;
			}
			const auto is_possible = frequency.Delete(s[j]);
			start = { j, s[j] };
			if (!is_possible)
			{
				break;
			}
		}
		if (i - start.first + 1 < min_window)
		{
			min_window = i - start.first + 1;
			end = { i, s[i] };
		}
	}

	const auto i = static_cast<int>(s.length()) - 1;
	for (auto j = start.first; j < i; ++j)
	{
		if (!frequency.IsValid(s[j]))
		{
			continue;
		}
		const auto is_possible = frequency.Delete(s[j]);
		start = { j, s[j] };
		if (!is_possible)
		{
			break;
		}
	}
	if (i - start.first + 1 < min_window)
	{
		min_window = i - start.first + 1;
		end = { i, s[i] };
	}

	if (start.first == -1 || min_window == infinity)
	{
		return "";
	}
	std::string window_str(s.begin() + start.first, s.begin() + start.first + min_window);
	return window_str;
}

class Solution {
public:
	static std::string minWindow(std::string s,
		std::string t);
};

std::string Solution::minWindow(std::string s,
	std::string t)
{
	return GetMinWindow(s, t);
}

int main(int argc, char* argv[])
{
	std::cout << Solution::minWindow("a", "aa") << std::endl;
	return 0;
}
