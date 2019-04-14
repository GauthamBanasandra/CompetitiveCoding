// WIP

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <cassert>

class Selector
{
public:
	explicit Selector(const std::string& data);

private:
	bool Select(int i_letter, std::stack<int>& verifier);

	std::vector<int> data_;
	std::vector<std::vector<int>> memo_;
};

Selector::Selector(const std::string& data)
{
	data_.reserve(data.size());
	for (const char bracket : data)
	{
		if (bracket == '(')
		{
			data_.emplace_back(1);
		}
		else if (bracket == ')')
		{
			data_.emplace_back(0);
		}
		else if (bracket == '?')
		{
			data_.emplace_back(2);
		}
		else
		{
			assert(false);
		}
	}
	memo_.resize(data_.size(), std::vector<int>(3, -1));
}

bool Selector::Select(const int i_letter, std::stack<int> & verifier)
{
	if (i_letter >= static_cast<int>(data_.size()))
	{
		return verifier.empty();
	}

	auto& memo = memo_[i_letter][data_[i_letter]];
	if (memo != -1)
	{
		return memo != 0;
	}

	if (data_[i_letter] == 1)
	{
		verifier.push(1);
		return Select(i_letter + 1, verifier);
	}
	if (data_[i_letter] == 0)
	{
		if (verifier.empty() || ((verifier.top() == 1) && (verifier.size() == 1)))
		{
			memo = 0;
			return false;
		}
		verifier.pop();
		return Select(i_letter + 1, verifier);
	}

	assert(data_[i_letter] == 2);
	verifier.push(1);
	if (Select(i_letter + 1, verifier))
	{
		memo = 1;
		return true;
	}


	return false;
}

int main(int argc, char* argv[])
{
	return 0;
}
