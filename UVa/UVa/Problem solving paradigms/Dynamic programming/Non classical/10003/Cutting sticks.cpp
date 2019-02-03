#include <vector>
#include <list>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cassert>

const auto infinity = std::numeric_limits<std::size_t>::max();

struct Stick
{
	Stick() = default;
	Stick(const std::size_t start, const std::size_t end) :start(start), end(end), length(end - start) {}

	bool operator==(const Stick &other) const
	{
		return start == other.start && end == other.end && length == other.length;
	}

	std::size_t start{ 0ul };
	std::size_t end{ 0ul };
	std::size_t length{ 0ul };
};

class Cutter
{
public:
	Cutter(const std::vector<std::size_t> &cuts) :cuts_(cuts) {}

	std::size_t Cut(Stick stick) const;

private:
	static Stick GetStick(const std::list<Stick> &sticks, std::size_t cut);
	static std::pair<Stick, Stick> CutStick(std::list<Stick> &sticks, std::size_t cut);
	static void MergeSticks(std::list<Stick> &sticks, const std::pair<Stick, Stick> &fragments);
	std::size_t CutNext(std::list<Stick> &sticks, std::size_t cuts) const;

	const std::vector<std::size_t> &cuts_;
};

std::size_t Cutter::Cut(const Stick stick) const
{
	std::list<Stick> sticks{ stick };
	return CutNext(sticks, 0ul);
}

Stick Cutter::GetStick(const std::list<Stick>& sticks, const std::size_t cut)
{
	Stick stick;
	auto found = false;
	for (const auto& s : sticks)
	{
		if (s.start <= cut && cut <= s.end)
		{
			stick = s;
			found = true;
			break;
		}
	}
	assert(found);
	return stick;
}

std::pair<Stick, Stick> Cutter::CutStick(std::list<Stick>& sticks, const std::size_t cut)
{
	const auto stick = GetStick(sticks, cut);
	sticks.remove(stick);

	std::pair<Stick, Stick> fragments{ {stick.start, cut}, {cut, stick.end} };
	sticks.emplace_back(fragments.first);
	sticks.emplace_back(fragments.second);
	return fragments;
}

void Cutter::MergeSticks(std::list<Stick>& sticks, const std::pair<Stick, Stick>& fragments)
{
	sticks.remove(fragments.first);
	sticks.remove(fragments.second);
	sticks.emplace_back(fragments.first.start, fragments.second.end);
}

std::size_t Cutter::CutNext(std::list<Stick>& sticks, const std::size_t cuts) const
{
	const auto len = cuts_.size();
	if (cuts == (1 << len) - 1)
	{
		return 0;
	}

	auto min_cost = infinity;
	for (std::size_t i = 0ul; i < len; ++i)
	{
		if (cuts & 1 << i)
		{
			continue;
		}

		const auto stick = GetStick(sticks, cuts_[i]);
		auto fragments = CutStick(sticks, cuts_[i]);
		auto cost = CutNext(sticks, cuts | 1 << i) + stick.length;
		min_cost = std::min(min_cost, cost);
		MergeSticks(sticks, fragments);
	}
	return min_cost;
}

int main(int argc, char* argv[])
{
	std::vector<std::size_t> cuts{ 4,5,7,8 };
	Cutter cutter(cuts);
	std::cout << cutter.Cut({ 0, 10 }) << std::endl;
	return 0;
}
