// WA

#include <iostream>
#include <string>
#include <cassert>

struct Days
{
	enum
	{
		kOffset,
		kSunday,
		kMonday,
		kTuesday,
		kWednesday,
		kThursday,
		kFriday,
		kSaturday
	};

	static int GetDayIndex(const std::string &day);
};

int Days::GetDayIndex(const std::string& day)
{
	if (day == "sunday")
	{
		return kSunday;
	}
	if (day == "monday")
	{
		return kMonday;
	}
	if (day == "tuesday")
	{
		return kTuesday;
	}
	if (day == "wednesday")
	{
		return kWednesday;
	}
	if (day == "thursday")
	{
		return kThursday;
	}
	if (day == "friday")
	{
		return kFriday;
	}
	if (day == "saturday")
	{
		return kSaturday;
	}

	assert(false);
	return kOffset;
}

std::string GetDuration(const std::string &start_str, const std::string &end_str, const int l, const int r)
{
	const auto start = Days::GetDayIndex(start_str);
	const auto end = Days::GetDayIndex(end_str);

	auto duration = end - start + 1;
	duration = duration < 0 ? duration + 7 : duration;

	if (duration < l || duration > r)
	{
		return "impossible";
	}

	if (duration + 7 <= r)
	{
		return "many";
	}
	return std::to_string(duration);
}

int main(int argc, char* argv[])
{
	int t, l, r;
	std::string start, end;

	std::cin >> t;
	while (t-- > 0)
	{
		std::cin >> start >> end >> l >> r;
		std::cout << GetDuration(start, end, l, r) << std::endl;
	}
	return 0;
}
