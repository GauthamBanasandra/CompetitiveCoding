#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <ios>

class Bits
{
public:
	explicit Bits(const std::vector<std::size_t>& numbers);
	bool Find();

private:
	bool IsInverseExist(const std::vector<std::size_t> &indices) const;

	std::unordered_map<std::size_t, std::vector<std::size_t>> reverse_index_;
};

Bits::Bits(const std::vector<std::size_t>& numbers)
{
	for (std::size_t i = 0, len = numbers.size(); i < len; ++i)
	{
		auto number = numbers[i];
		if (reverse_index_.find(number) == reverse_index_.end())
		{
			reverse_index_[number].reserve(len);
		}
		reverse_index_[number].emplace_back(i + 1);
	}
}

bool Bits::Find()
{
	for (const auto& reverse_index : reverse_index_)
	{
		auto& indices = reverse_index.second;
		if (indices.size() < 2)
		{
			continue;
		}

		if (IsInverseExist(indices))
		{
			return true;
		}
	}
	return false;
}

bool Bits::IsInverseExist(const std::vector<std::size_t>& indices) const
{
	std::size_t i_index = 0;
	const auto len = indices.size();
	assert(len > 1);

	for (auto index : indices)
	{
		if (reverse_index_.find(index) != reverse_index_.end())
		{
			break;
		}
		++i_index;
	}

	++i_index;
	while (i_index < len)
	{
		if (reverse_index_.find(indices[i_index]) != reverse_index_.end())
		{
			return true;
		}
		++i_index;
	}
	return false;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	std::size_t n;
	std::vector<std::size_t> numbers;

	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		numbers.resize(n);
		for (std::size_t i = 0; i < n; ++i)
		{
			std::cin >> numbers[i];
		}

		std::cout << (Bits(numbers).Find() ? "Truly Happy" : "Poor Chef") << std::endl;
	}
	return 0;
}
