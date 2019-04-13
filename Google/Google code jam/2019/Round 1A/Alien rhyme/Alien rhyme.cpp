// WA

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

class Match
{
public:
	explicit Match(const std::vector<std::string>& words);

	int Choose();

private:
	void Choose(int i_next);
	std::string BestMatch(int i_word, int j_word) const;
	std::string GetHash(int i, int j) const;

	int max_count_{ 0 };
	int count_{ 0 };
	const std::vector<std::string>& words_;
	std::vector<int> is_not_available_;
	std::unordered_map<std::string, std::string> acc_;
};

Match::Match(const std::vector<std::string>& words) : words_(
	words)
{
	is_not_available_.resize(words_.size());
}

int Match::Choose()
{
	for (int i = 0; i < words_.size(); ++i)
	{
		Choose(i);
	}
	return max_count_;
}

void Match::Choose(const int i_next)
{
	if (i_next == static_cast<int>(words_.size()))
	{
		max_count_ = std::max(max_count_, count_);
		return;
	}

	const int len = words_.size();
	for (auto i = 0; i < len; ++i)
	{
		if (is_not_available_[i] == 1)
		{
			continue;
		}

		is_not_available_[i] = 1;
		for (auto j = 0; j < len; ++j)
		{
			if (is_not_available_[j] == 1)
			{
				continue;
			}

			auto match = BestMatch(i, j);
			if (match.empty())
			{
				continue;
			}

			const auto hash = GetHash(i, j);
			acc_[match] = hash;
			is_not_available_[j] = 1;
			++count_;
			Choose(i + 1);
			--count_;
			is_not_available_[j] = 0;
			acc_.erase(match);
		}
		is_not_available_[i] = 0;
	}
}

std::string Match::BestMatch(const int i_word, const int j_word) const
{
	std::string acc;
	if (words_[i_word].back() != words_[j_word].back())
	{
		return acc;
	}

	int ip = words_[i_word].size();
	int jp = words_[j_word].size();
	const auto i_last = ip;
	const auto j_last = jp;

	for (--ip, --jp; ip >= 0 && jp >= 0 && words_[i_word][ip] == words_[j_word][jp]; --ip, --jp)
	{
		acc.push_back(words_[i_word][ip]);
	}

	for (std::size_t i = 0; i < acc.size(); ++i)
	{
		std::string sub_acc(acc.begin() + i, acc.end());
		if (acc_.find(sub_acc) == acc_.end())
		{
			return sub_acc;
		}
	}
	return "";
}

std::string Match::GetHash(int i, int j) const
{
	return std::to_string(i) + " " + std::to_string(j);
}

int main(int argc, char* argv[])
{
	std::vector<std::string> words = {
"CODEJAM",
"JAM",
"HAM",
"NALAM",
"HUM",
"NOLOM",
	};

	std::cout << Match(words).Choose() << std::endl;
	return 0;
}
