// WA

#include <vector>
#include <unordered_map>
#include <iostream>

std::vector<int> Rearrange(const std::vector<int>& barcodes)
{
	std::unordered_map<int, int> f;
	for (const auto barcode : barcodes)
	{
		++f[barcode];
	}

	std::vector<int> rearranged(barcodes.size());
	std::size_t i = 0;
	while (!f.empty())
	{
		std::vector<int> clear;
		for (auto& item : f)
		{
			rearranged[i] = item.first;
			--item.second;
			++i;
			if (item.second == 0)
			{
				clear.emplace_back(item.first);
			}
		}

		for (const auto key : clear)
		{
			f.erase(key);
		}
	}
	return rearranged;
}

class Solution
{
public:
	static std::vector<int> rearrangeBarcodes(
		std::vector<int>& barcodes);
};

std::vector<int> Solution::rearrangeBarcodes(
	std::vector<int>& barcodes)
{
	return Rearrange(barcodes);
}

int main(int argc, char* argv[])
{
	return 0;
}
