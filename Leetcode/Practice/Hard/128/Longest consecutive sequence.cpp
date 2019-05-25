#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

class Sequence
{
public:
	explicit Sequence(const std::vector<int>& numbers) : numbers_(numbers) {}

	int GetLongestSeqLen() const;

private:
	static std::vector<int> GetFrequency(
		const std::unordered_map<int, int>& num_label, int num_label_len);
	static int StitchLabels(
		std::unordered_map<int, int>& instructions, std::vector<int>& frequency);

	const std::vector<int>& numbers_;
};

int Sequence::GetLongestSeqLen() const
{
	std::unordered_map<int, int> num_label;
	// The labels that need to be stitched together
	std::unordered_map<int, int> instructions;
	auto label = 0;

	for (const auto number : numbers_)
	{
		if (num_label.find(number) != num_label.end())
		{
			continue;
		}

		const auto prev_it = num_label.find(number - 1);
		const auto next_it = num_label.find(number + 1);
		if (prev_it != num_label.end() && next_it != num_label.end())
		{
			instructions[prev_it->second] = next_it->second;
			num_label[number] = prev_it->second;
		}
		else if (prev_it != num_label.end() && next_it == num_label.end())
		{
			num_label[number] = prev_it->second;
		}
		else if (prev_it == num_label.end() && next_it != num_label.end())
		{
			num_label[number] = next_it->second;
		}
		else
		{
			num_label[number] = ++label;
		}
	}

	auto frequency = GetFrequency(num_label, label + 1);
	return StitchLabels(instructions, frequency);
}

std::vector<int> Sequence::GetFrequency(const std::unordered_map<int, int>& num_label,
	const int num_label_len)
{
	std::vector<int> frequency(num_label_len);
	for (const auto& item : num_label)
	{
		++frequency[item.second];
	}
	return frequency;
}

int Sequence::StitchLabels(std::unordered_map<int, int>& instructions,
	std::vector<int>& frequency)
{
	for (auto label = 0, len = static_cast<int>(frequency.size()); label < len; ++label)
	{
		auto find_it = instructions.find(label);
		if (find_it == instructions.end())
		{
			continue;
		}

		// We loop over and keep adding as long as the chain is maintained
		while (find_it != instructions.end())
		{
			auto next = find_it->second;
			frequency[label] += frequency[next];
			instructions.erase(find_it->first);
			find_it = instructions.find(next);
		}
	}
	return *std::max_element(frequency.begin(), frequency.end());
}

class Solution
{
public:
	static int longestConsecutive(std::vector<int>& nums);
};

int Solution::longestConsecutive(std::vector<int>& nums)
{
	return Sequence(nums).GetLongestSeqLen();
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers{ 100, 4, 200, 1, 3, 2 };
	std::cout << Solution::longestConsecutive(numbers) << std::endl;
	return 0;
}
